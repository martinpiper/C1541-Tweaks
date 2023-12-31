/*
 * ioramcart.h - VIC20 RAM in I/O space emulation.
 *
 * Written by
 *  Marco van den Heuvel <blackystardust68@yahoo.com>
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

#ifndef VICE_VIC20_IORAMCART_H
#define VICE_VIC20_IORAMCART_H

#include "snapshot.h"

int ioramcart_resources_init(void);
int ioramcart_cmdline_options_init(void);

void ioramcart_io2_detach(void);
void ioramcart_io3_detach(void);

int ioramcart_io2_snapshot_write_module(snapshot_t *s);
int ioramcart_io2_snapshot_read_module(snapshot_t *s);
int ioramcart_io3_snapshot_write_module(snapshot_t *s);
int ioramcart_io3_snapshot_read_module(snapshot_t *s);

#endif
