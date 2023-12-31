/*
 * turtlegraphics.c - Cartridge handling, HES Turtle Graphics II cart.
 *
 * Written by
 *  groepaz <groepaz@gmx.net>
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
#include <stdlib.h>
#include <string.h>

#define CARTRIDGE_INCLUDE_SLOTMAIN_API
#include "c64cartsystem.h"
#undef CARTRIDGE_INCLUDE_SLOTMAIN_API
#include "cartio.h"
#include "cartridge.h"
#include "export.h"
#include "monitor.h"
#include "snapshot.h"
#include "turtlegraphics.h"
#include "types.h"
#include "util.h"
#include "crt.h"

/* Turtle Graphics II IO1 logic for the roml range $8000-$9fff
*
*  - RESET will enable bank 0
*  - Any read/write access to IO/1 will enable bank 1
*/

/* ---------------------------------------------------------------------*/

static uint8_t turtlegraphics_io1_read(uint16_t addr);
static uint8_t turtlegraphics_io1_peek(uint16_t addr);
static void turtlegraphics_io1_store(uint16_t addr, uint8_t value);
static int turtlegraphics_dump(void);

static io_source_t turtlegraphics_device = {
    CARTRIDGE_NAME_STRUCTURED_BASIC, /* name of the device */
    IO_DETACH_CART,                  /* use cartridge ID to detach the device when involved in a read-collision */
    IO_DETACH_NO_RESOURCE,           /* does not use a resource for detach */
    0xde00, 0xdeff, 0x01,            /* range for the device, regs:$de00, mirrors:$de01-$deff */
    0,                               /* read is never valid, regs are write only */
    turtlegraphics_io1_store,        /* store function */
    NULL,                            /* NO poke function */
    turtlegraphics_io1_read,         /* read function */
    turtlegraphics_io1_peek,         /* peek function */
    turtlegraphics_dump,             /* device state information dump function */
    CARTRIDGE_TURTLE_GRAPHICS_II,    /* cartridge ID */
    IO_PRIO_NORMAL,                  /* normal priority, device read needs to be checked for collisions */
    0,                               /* insertion order, gets filled in by the registration function */
    IO_MIRROR_NONE                   /* NO mirroring */
};

static io_source_list_t *turtlegraphics_list_item = NULL;

static const export_resource_t export_res = {
    CARTRIDGE_NAME_TURTLE_GRAPHICS_II, 1, 0, &turtlegraphics_device, NULL, CARTRIDGE_TURTLE_GRAPHICS_II
};

/* ---------------------------------------------------------------------*/

static int turtlegraphics_bank = 0;

static uint8_t turtlegraphics_io1_read(uint16_t addr)
{
    turtlegraphics_bank = 1;
    cart_config_changed_slotmain(0 | (1 << CMODE_BANK_SHIFT), 0 | (1 << CMODE_BANK_SHIFT), CMODE_READ);
    return 0;
}

static uint8_t turtlegraphics_io1_peek(uint16_t addr)
{
    return 0;
}

static void turtlegraphics_io1_store(uint16_t addr, uint8_t value)
{
    turtlegraphics_bank = 1;
    cart_config_changed_slotmain(0 | (1 << CMODE_BANK_SHIFT), 0 | (1 << CMODE_BANK_SHIFT), CMODE_READ);
}

static int turtlegraphics_dump(void)
{
    mon_out("bank: %d\n", turtlegraphics_bank);
    return 0;
}

/* ---------------------------------------------------------------------*/

void turtlegraphics_config_init(void)
{
    /* turn on normal config: bank 0 */
    cart_config_changed_slotmain(CMODE_8KGAME, CMODE_8KGAME, CMODE_READ);
    turtlegraphics_bank = 0;
}

void turtlegraphics_config_setup(uint8_t *rawcart)
{
    /* copy banks 0 and 1 */
    memcpy(roml_banks, rawcart, 0x4000);

    /* turn on normal config: bank 0 */
    cart_config_changed_slotmain(CMODE_8KGAME, CMODE_8KGAME, CMODE_READ);
    turtlegraphics_bank = 0;
}

/* ---------------------------------------------------------------------*/

static int turtlegraphics_common_attach(void)
{
    /* add export */
    if (export_add(&export_res) < 0) {
        return -1;
    }

    turtlegraphics_list_item = io_source_register(&turtlegraphics_device);

    return 0;
}

int turtlegraphics_bin_attach(const char *filename, uint8_t *rawcart)
{
    /* load file into cartridge address space */
    if (util_file_load(filename, rawcart, 0x4000, UTIL_FILE_LOAD_RAW) < 0) {
        return -1;
    }

    return turtlegraphics_common_attach();
}

int turtlegraphics_crt_attach(FILE *fd, uint8_t *rawcart)
{
    crt_chip_header_t chip;

    while (1) {
        if (crt_read_chip_header(&chip, fd)) {
            break;
        }

        if (chip.start != 0x8000 || chip.size != 0x2000 || chip.bank > 1) {
            return -1;
        }

        if (crt_read_chip(rawcart, chip.bank << 13, &chip, fd)) {
            return -1;
        }
    }

    return turtlegraphics_common_attach();
}

void turtlegraphics_detach(void)
{
    export_remove(&export_res);
    io_source_unregister(turtlegraphics_list_item);
    turtlegraphics_list_item = NULL;
}

/* ---------------------------------------------------------------------*/

/* CARTSTB snapshot module format:

   type  | name   | version | description
   --------------------------------------
   BYTE  | bank   |   0.1   | current bank
   BYTE  | active |   0.1   | cartridge active flag
   ARRAY | ROML   |   0.0+  | 16384 BYTES of ROML data
 */

static const char snap_module_name[] = "CARTSTB";
#define SNAP_MAJOR   0
#define SNAP_MINOR   1

int turtlegraphics_snapshot_write_module(snapshot_t *s)
{
    snapshot_module_t *m;

    m = snapshot_module_create(s, snap_module_name, SNAP_MAJOR, SNAP_MINOR);

    if (m == NULL) {
        return -1;
    }

    if (0
        || SMW_B(m, (uint8_t)turtlegraphics_bank) < 0
        || SMW_BA(m, roml_banks, 0x4000) < 0) {
        snapshot_module_close(m);
        return -1;
    }

    return snapshot_module_close(m);
}

int turtlegraphics_snapshot_read_module(snapshot_t *s)
{
    uint8_t vmajor, vminor;
    snapshot_module_t *m;

    m = snapshot_module_open(s, snap_module_name, &vmajor, &vminor);

    if (m == NULL) {
        return -1;
    }

    /* Do not accept versions higher than current */
    if (snapshot_version_is_bigger(vmajor, vminor, SNAP_MAJOR, SNAP_MINOR)) {
        snapshot_set_error(SNAPSHOT_MODULE_HIGHER_VERSION);
        goto fail;
    }

    if (0
        || SMR_B_INT(m, &turtlegraphics_bank) < 0) {
        goto fail;
    }

    if (SMR_BA(m, roml_banks, 0x4000) < 0) {
        goto fail;
    }

    snapshot_module_close(m);

    return turtlegraphics_common_attach();

fail:
    snapshot_module_close(m);
    return -1;
}
