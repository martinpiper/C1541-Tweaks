/*
 * actionreplay.c - Cartridge handling, Action Replay cart.
 *
 * Written by
 *  Andreas Boose <viceteam@t-online.de>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#include "vice.h"

#include <stdio.h>
#include <string.h>

#include "actionreplay.h"
#define CARTRIDGE_INCLUDE_SLOTMAIN_API
#include "c64cartsystem.h"
#undef CARTRIDGE_INCLUDE_SLOTMAIN_API
#include "c64mem.h"
#include "cartio.h"
#include "cartridge.h"
#include "export.h"
#include "log.h"
#include "monitor.h"
#include "ram.h"
#include "snapshot.h"
#include "types.h"
#include "util.h"
#include "crt.h"
#include "vicii-phi1.h"

/*
    Action Replay 4.2, 5, 6 (Hardware stayed the same)

    32K rom, 4*8k pages
    8K ram

    io1 (writes)

    7    extra ROM bank selector (A15) (unused)
    6    1 = resets FREEZE-mode (turns back to normal mode)
    5    1 = enable RAM at ROML ($8000-$9FFF) &
            I/O2 ($DF00-$DFFF = $9F00-$9FFF)
    4    ROM bank selector high (A14)
    3    ROM bank selector low  (A13)
    2    1 = disable cartridge (turn off $DE00)
    1    1 = /EXROM high
    0    1 = /GAME low

    io2 (r/w)
        cart RAM (if enabled) or cart ROM
*/

#define CART_RAM_SIZE (8 * 1024)

static int ar_active;

/* ---------------------------------------------------------------------*/

/* some prototypes are needed */
static uint8_t actionreplay_io1_peek(uint16_t addr);
static uint8_t actionreplay_io1_read(uint16_t addr);
static void actionreplay_io1_store(uint16_t addr, uint8_t value);
static uint8_t actionreplay_io2_read(uint16_t addr);
static uint8_t actionreplay_io2_peek(uint16_t addr);
static void actionreplay_io2_store(uint16_t addr, uint8_t value);
static int actionreplay_dump(void);

static io_source_t action_replay_io1_device = {
    CARTRIDGE_NAME_ACTION_REPLAY, /* name of the device */
    IO_DETACH_CART,               /* use cartridge ID to detach the device when involved in a read-collision */
    IO_DETACH_NO_RESOURCE,        /* does not use a resource for detach */
    0xde00, 0xdeff, 0xff,         /* range for the device, address is ignored by the write functions, reg:$de00, mirrors:$de01-$deff */
    0,                            /* read is never valid */
    actionreplay_io1_store,       /* store function */
    NULL,                         /* NO poke function */
    actionreplay_io1_read,        /* read function */
    actionreplay_io1_peek,        /* peek function */
    actionreplay_dump,            /* device state information dump function */
    CARTRIDGE_ACTION_REPLAY,      /* cartridge ID */
    IO_PRIO_NORMAL,               /* normal priority, device read needs to be checked for collisions */
    0,                            /* insertion order, gets filled in by the registration function */
    IO_MIRROR_NONE                /* NO mirroring */
};

static io_source_t action_replay_io2_device = {
    CARTRIDGE_NAME_ACTION_REPLAY, /* name of the device */
    IO_DETACH_CART,               /* use cartridge ID to detach the device when involved in a read-collision */
    IO_DETACH_NO_RESOURCE,        /* does not use a resource for detach */
    0xdf00, 0xdfff, 0xff,         /* range for the device, address is ignored by the read/write functions, reg:$df00, mirrors:$df01-$dfff */
    0,                            /* validity of the read is determined by the cartridge at read time */
    actionreplay_io2_store,       /* store function */
    NULL,                         /* NO poke function */
    actionreplay_io2_read,        /* read function */
    actionreplay_io2_peek,        /* peek function */
    actionreplay_dump,            /* device state information dump function */
    CARTRIDGE_ACTION_REPLAY,      /* cartridge ID */
    IO_PRIO_NORMAL,               /* normal priority, device read needs to be checked for collisions */
    0,                            /* insertion order, gets filled in by the registration function */
    IO_MIRROR_NONE                /* NO mirroring */
};

static io_source_list_t *action_replay_io1_list_item = NULL;
static io_source_list_t *action_replay_io2_list_item = NULL;

static const export_resource_t export_res = {
    CARTRIDGE_NAME_ACTION_REPLAY, 1, 1, &action_replay_io1_device, &action_replay_io2_device, CARTRIDGE_ACTION_REPLAY
};

/* ---------------------------------------------------------------------*/

static uint8_t regvalue;

static void actionreplay_io1_store(uint16_t addr, uint8_t value)
{
    unsigned int mode = 0;

    if (ar_active) {
        regvalue = value;
        if (value & 0x40) {
            mode |= CMODE_RELEASE_FREEZE;
        }
        if (value & 0x20) {
            mode |= CMODE_EXPORT_RAM;
        }
        if (value & 4) {
            ar_active = 0;
        }

        /* mode 0x22 is broken in the original AR, we handle it here so we can
           emit a warning on access */
        if ((value & 0x23) == 0x22) {
            cart_config_changed_slotmain(CMODE_8KGAME,
                CMODE_8KGAME | (((value >> 3) & 3) << CMODE_BANK_SHIFT),
                (unsigned int)(mode | CMODE_WRITE));
        } else {
            cart_config_changed_slotmain((uint8_t)(value & 3),
                (uint8_t)((value & 3) | (((value >> 3) & 3) << CMODE_BANK_SHIFT)),
                (unsigned int)(mode | CMODE_WRITE));
        }

    }
}

static uint8_t actionreplay_io1_read(uint16_t addr)
{
    uint8_t value;
    /* the read is really never valid */
    action_replay_io1_device.io_source_valid = 0;
    if (!ar_active) {
        return 0;
    }
    /* since the r/w line is not decoded, a read still changes the register,
       to whatever was on the bus before */
    value = vicii_read_phi1();
    actionreplay_io1_store(addr, value);
    log_warning(LOG_DEFAULT, "AR5: reading IO1 area at 0xde%02x, this corrupts the register",
                addr & 0xffu);

    return value;
}

static uint8_t actionreplay_io1_peek(uint16_t addr)
{
    return regvalue;
}

static uint8_t actionreplay_io2_read(uint16_t addr)
{
    action_replay_io2_device.io_source_valid = 0;

    if (!ar_active) {
        return 0;
    }

    action_replay_io2_device.io_source_valid = 1;

    if (export_ram) {
        return export_ram0[0x1f00 + (addr & 0xff)];
    }

    addr |= 0xdf00;

    switch (roml_bank) {
        case 0:
            return roml_banks[addr & 0x1fff];
        case 1:
            return roml_banks[(addr & 0x1fff) + 0x2000];
        case 2:
            return roml_banks[(addr & 0x1fff) + 0x4000];
        case 3:
            return roml_banks[(addr & 0x1fff) + 0x6000];
    }

    action_replay_io2_device.io_source_valid = 0;

    return 0;
}

static uint8_t actionreplay_io2_peek(uint16_t addr)
{
    if (!ar_active) {
        return 0;
    }

    if (export_ram) {
        return export_ram0[0x1f00 + (addr & 0xff)];
    }

    addr |= 0xdf00;

    switch (roml_bank) {
        case 0:
            return roml_banks[addr & 0x1fff];
        case 1:
            return roml_banks[(addr & 0x1fff) + 0x2000];
        case 2:
            return roml_banks[(addr & 0x1fff) + 0x4000];
        case 3:
            return roml_banks[(addr & 0x1fff) + 0x6000];
    }

    return 0;
}

static void actionreplay_io2_store(uint16_t addr, uint8_t value)
{
    if (ar_active) {
        if (export_ram) {
            export_ram0[0x1f00 + (addr & 0xff)] = value;
        }
    }
}

static int actionreplay_dump(void)
{
    mon_out("EXROM line: %s, GAME line: %s, Mode: %s\n",
            (regvalue & 2) ? "high" : "low",
            (regvalue & 1) ? "low" : "high",
            cart_config_string((uint8_t)(regvalue & 3)));
    mon_out("ROM bank: %d, cart state: %s, reset freeze: %s\n",
            (regvalue & 0x18) >> 3,
            (regvalue & 4) ? "disabled" : "enabled",
            (regvalue & 0x40) ? "yes" : "no");
    /* FIXME: take system RAM and cart mode(s) into account here */
    mon_out("$8000-$9FFF: %s\n", (export_ram) ? "RAM" : "ROM");
    mon_out("$A000-$BFFF: %s\n", "ROM");
    mon_out("$DF00-$DFFF: %s\n", (export_ram) ? "RAM" : "ROM");
   return 0;
}

/* ---------------------------------------------------------------------*/

uint8_t actionreplay_roml_read(uint16_t addr)
{
    if ((regvalue & 0x23) == 0x22) {
        log_warning(LOG_DEFAULT,
            "AR5: reading ROML area at 0x%04x in mode $22, this causes bus contention,", addr);
        log_warning(LOG_DEFAULT,
            "     is unreliable, and may damage the hardware - do not do this!");
        /* in mode 0x22 both C64 and cartridge RAM is selected */
        return mem_read_without_ultimax(addr) | export_ram0[addr & 0x1fff];
    }

    if (export_ram) {
        return export_ram0[addr & 0x1fff];
    }
    return roml_banks[(addr & 0x1fff) + (roml_bank << 13)];
}

void actionreplay_roml_store(uint16_t addr, uint8_t value)
{
    if (export_ram) {
        export_ram0[addr & 0x1fff] = value;
    }
}

/* ---------------------------------------------------------------------*/

/* FIXME: this still needs to be tweaked to match the hardware */
static RAMINITPARAM ramparam = {
    .start_value = 255,
    .value_invert = 2,
    .value_offset = 1,

    .pattern_invert = 0x100,
    .pattern_invert_value = 255,

    .random_start = 0,
    .random_repeat = 0,
    .random_chance = 0,
};

void actionreplay_powerup(void)
{
    ram_init_with_pattern(export_ram0, CART_RAM_SIZE, &ramparam);
}

void actionreplay_freeze(void)
{
    ar_active = 1;
    cart_config_changed_slotmain(CMODE_ULTIMAX, CMODE_ULTIMAX, CMODE_READ | CMODE_EXPORT_RAM);
}

void actionreplay_config_init(void)
{
    ar_active = 1;
    regvalue = 0;
    cart_config_changed_slotmain(CMODE_8KGAME, CMODE_8KGAME, CMODE_READ);
}

void actionreplay_reset(void)
{
    ar_active = 1;
    regvalue = 0;
}

void actionreplay_config_setup(uint8_t *rawcart)
{
    memcpy(roml_banks, rawcart, 0x8000);
    memcpy(romh_banks, rawcart, 0x8000);
    cart_config_changed_slotmain(0, 0, CMODE_READ);
}

/* ---------------------------------------------------------------------*/

static int actionreplay_common_attach(void)
{
    if (export_add(&export_res) < 0) {
        return -1;
    }

    action_replay_io1_list_item = io_source_register(&action_replay_io1_device);
    action_replay_io2_list_item = io_source_register(&action_replay_io2_device);

    return 0;
}

int actionreplay_bin_attach(const char *filename, uint8_t *rawcart)
{
    if (util_file_load(filename, rawcart, 0x8000, UTIL_FILE_LOAD_SKIP_ADDRESS) < 0) {
        return -1;
    }

    return actionreplay_common_attach();
}

int actionreplay_crt_attach(FILE *fd, uint8_t *rawcart)
{
    crt_chip_header_t chip;
    int i;

    for (i = 0; i <= 3; i++) {
        if (crt_read_chip_header(&chip, fd)) {
            return -1;
        }

        if (chip.bank > 3 || chip.size != 0x2000) {
            return -1;
        }

        if (crt_read_chip(rawcart, chip.bank << 13, &chip, fd)) {
            return -1;
        }
    }

    return actionreplay_common_attach();
}

void actionreplay_detach(void)
{
    io_source_unregister(action_replay_io1_list_item);
    io_source_unregister(action_replay_io2_list_item);
    action_replay_io1_list_item = NULL;
    action_replay_io2_list_item = NULL;
    export_remove(&export_res);
}

/* ---------------------------------------------------------------------*/

/* CARTAR snapshot module format:

   type  | name   | description
   ----------------------------
   BYTE  | active | cartridge is active
   ARRAY | ROML   | 32768 BYTES of ROML data
   ARRAY | ROMH   | 32768 BYTES of ROMH data
   ARRAY | RAM    | 8192 BYES of RAM data
 */

static const char snap_module_name[] = "CARTAR";
#define SNAP_MAJOR   0
#define SNAP_MINOR   0

int actionreplay_snapshot_write_module(snapshot_t *s)
{
    snapshot_module_t *m;

    m = snapshot_module_create(s, snap_module_name, SNAP_MAJOR, SNAP_MINOR);

    if (m == NULL) {
        return -1;
    }

    if (0
        || (SMW_B(m, (uint8_t)ar_active) < 0)
        || (SMW_BA(m, roml_banks, 0x8000) < 0)
        || (SMW_BA(m, romh_banks, 0x8000) < 0)
        || (SMW_BA(m, export_ram0, 0x2000) < 0)) {
        snapshot_module_close(m);
        return -1;
    }

    snapshot_module_close(m);
    return 0;
}

int actionreplay_snapshot_read_module(snapshot_t *s)
{
    uint8_t vmajor, vminor;
    snapshot_module_t *m;

    m = snapshot_module_open(s, snap_module_name, &vmajor, &vminor);

    if (m == NULL) {
        return -1;
    }

    /* Do not accept higher versions than current */
    if (snapshot_version_is_bigger(vmajor, vminor, SNAP_MAJOR, SNAP_MINOR)) {
        snapshot_set_error(SNAPSHOT_MODULE_HIGHER_VERSION);
        goto fail;
    }

    if (0
        || (SMR_B_INT(m, &ar_active) < 0)
        || (SMR_BA(m, roml_banks, 0x8000) < 0)
        || (SMR_BA(m, romh_banks, 0x8000) < 0)
        || (SMR_BA(m, export_ram0, 0x2000) < 0)) {
        goto fail;
    }

    snapshot_module_close(m);

    return actionreplay_common_attach();

fail:
    snapshot_module_close(m);
    return -1;
}
