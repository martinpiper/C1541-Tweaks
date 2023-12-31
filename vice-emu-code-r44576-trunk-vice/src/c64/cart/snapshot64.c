/*
 * snapshot64.c - Cartridge handling, Snapshot64 cart.
 *
 * Written by
 *  Groepaz <groepaz@gmx.net>
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

#define CARTRIDGE_INCLUDE_SLOTMAIN_API
#include "c64cartsystem.h"
#undef CARTRIDGE_INCLUDE_SLOTMAIN_API
#include "c64mem.h"
#include "cartio.h"
#include "cartridge.h"
#include "export.h"
#include "snapshot.h"
#include "snapshot64.h"
#include "types.h"
#include "util.h"
#include "crt.h"

/*
    Snapshot 64 (LMS Technologies)

    FIXME: this implementation is purely based on guesswork

    - 4K ROM (2732)
      - mapped to 8000 and e000 (ultimax mode) ?
    - NE555, 7406, 7474
    - one button (freeze)

    io2 - df00 (r/w)
    - any read access seems to disable the cartridge

    (the snapshot64 software uses inc $df00 in a loop to switch)

    after reset NO menu is shown. when pressing freeze the screen goes blank, then

    return - starts the "code inspector"
       l - load and execute ml program
       j - jump to address
       d - dump memory (hex)
       e - return to basic
    f1 - analyze and save backup
    f3 - clear memory
    f5 - format disk
    f7 - restart

*/

/* #define SS64DEBUG */

#ifdef SS64DEBUG
#define DBG(x) printf x
#else
#define DBG(x)
#endif

static uint8_t romconfig = 0;

/* ---------------------------------------------------------------------*/

/* some prototypes are needed */
static uint8_t snapshot64_io2_read(uint16_t addr);
static uint8_t snapshot64_io2_peek(uint16_t addr);
static void snapshot64_io2_store(uint16_t addr, uint8_t value);

static io_source_t ss64_io2_device = {
    CARTRIDGE_NAME_SNAPSHOT64, /* name of the device */
    IO_DETACH_CART,            /* use cartridge ID to detach the device when involved in a read-collision */
    IO_DETACH_NO_RESOURCE,     /* does not use a resource for detach */
    0xdf00, 0xdfff, 0xff,      /* range for the device, address is ignored, reg:$df00, mirrors:$df01-$dfff */
    0,                         /* read is never valid */
    snapshot64_io2_store,      /* store function */
    NULL,                      /* NO poke function */
    snapshot64_io2_read,       /* read function */
    snapshot64_io2_peek,       /* peek function */
    NULL,                      /* TODO: device state information dump function */
    CARTRIDGE_SNAPSHOT64,      /* cartridge ID */
    IO_PRIO_NORMAL,            /* normal priority, device read needs to be checked for collisions */
    0,                         /* insertion order, gets filled in by the registration function */
    IO_MIRROR_NONE             /* NO mirroring */
};

static io_source_list_t *ss64_io2_list_item = NULL;

static const export_resource_t export_res = {
    CARTRIDGE_NAME_SNAPSHOT64, 1, 1, NULL, &ss64_io2_device, CARTRIDGE_SNAPSHOT64
};

/* ---------------------------------------------------------------------*/

static void enable_rom(int enable, int mode)
{
    romconfig = enable;
    if (enable == 0) {
        cart_config_changed_slotmain(CMODE_RAM, CMODE_RAM, mode);
    } else {
        cart_config_changed_slotmain(CMODE_ULTIMAX, CMODE_ULTIMAX, mode);
    }
}

uint8_t snapshot64_io2_read(uint16_t addr)
{
/*    DBG(("io2 rd %04x (%02x)\n", addr, romconfig)); */
    return 0;
}

uint8_t snapshot64_io2_peek(uint16_t addr)
{
    return romconfig;
}

void snapshot64_io2_store(uint16_t addr, uint8_t value)
{
/*    DBG(("io2 wr %04x %02x\n", addr, value)); */
    enable_rom(0, CMODE_WRITE);
}

/* ---------------------------------------------------------------------*/

uint8_t snapshot64_roml_read(uint16_t addr)
{
    return roml_banks[addr & 0x0fff];
}

uint8_t snapshot64_romh_read(uint16_t addr)
{
    return roml_banks[addr & 0x0fff];
}

/* ---------------------------------------------------------------------*/

void snapshot64_freeze(void)
{
    DBG(("SNAPSHOT64: freeze\n"));
    enable_rom(1, CMODE_READ | CMODE_RELEASE_FREEZE);
}

void snapshot64_config_init(void)
{
    DBG(("SNAPSHOT64: config_init\n"));
    enable_rom(0, CMODE_READ);
}

void snapshot64_config_setup(uint8_t *rawcart)
{
    DBG(("SNAPSHOT64: config setup\n"));
    memcpy(&roml_banks[0x0000], &rawcart[0x0000], 0x1000);
    enable_rom(0, CMODE_READ);
}

/* ---------------------------------------------------------------------*/

static int snapshot64_common_attach(void)
{
    if (export_add(&export_res) < 0) {
        return -1;
    }

    ss64_io2_list_item = io_source_register(&ss64_io2_device);
    return 0;
}

int snapshot64_bin_attach(const char *filename, uint8_t *rawcart)
{
    if (util_file_load(filename, rawcart, 0x1000, UTIL_FILE_LOAD_SKIP_ADDRESS) < 0) {
        return -1;
    }
    return snapshot64_common_attach();
}

int snapshot64_crt_attach(FILE *fd, uint8_t *rawcart)
{
    crt_chip_header_t chip;

    if (crt_read_chip_header(&chip, fd)) {
        return -1;
    }

    if (chip.bank > 0 || chip.size != 0x1000) {
        return -1;
    }

    if (crt_read_chip(rawcart, 0, &chip, fd)) {
        return -1;
    }

    return snapshot64_common_attach();
}

void snapshot64_detach(void)
{
    export_remove(&export_res);
    io_source_unregister(ss64_io2_list_item);
    ss64_io2_list_item = NULL;
}

/* ---------------------------------------------------------------------*/

/* CARTSNAP64 snapshot module format:

   type  | name       | description
   --------------------------------
   BYTE  | ROM config | ROM configuration
   ARRAY | ROML       | 4096 BYTES of ROML data
 */

static const char snap_module_name[] = "CARTSNAP64";
#define SNAP_MAJOR   0
#define SNAP_MINOR   0

int snapshot64_snapshot_write_module(snapshot_t *s)
{
    snapshot_module_t *m;

    m = snapshot_module_create(s, snap_module_name, SNAP_MAJOR, SNAP_MINOR);

    if (m == NULL) {
        return -1;
    }

    if (0
        || SMW_B(m, romconfig) < 0
        || SMW_BA(m, roml_banks, 0x1000) < 0) {
        snapshot_module_close(m);
        return -1;
    }

    return snapshot_module_close(m);
}

int snapshot64_snapshot_read_module(snapshot_t *s)
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
        || SMR_B(m, &romconfig) < 0
        || SMR_BA(m, roml_banks, 0x1000) < 0) {
        goto fail;
    }

    snapshot_module_close(m);

    return snapshot64_common_attach();

fail:
    snapshot_module_close(m);
    return -1;
}
