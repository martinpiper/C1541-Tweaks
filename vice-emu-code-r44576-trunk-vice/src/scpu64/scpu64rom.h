/*
 * scpu64rom.h
 *
 * Written by
 *  Kajtar Zsolt <soci@c64.rulez.org>
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

#ifndef VICE_SCPU64ROM_H
#define VICE_SCPU64ROM_H

int scpu64rom_load_scpu64(const char *rom_name);
int scpu64rom_load_chargen(const char *rom_name);

extern uint8_t scpu64rom_scpu64_rom[];

/* filenames used for the chargen ROMs */
#define C64_CHARGEN_NAME        "chargen-901225-01.bin"
#define C64_CHARGEN_JAP_NAME    "chargen-906143-02.bin"

#endif
