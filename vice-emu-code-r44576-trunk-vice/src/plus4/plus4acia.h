/*
 * plus4acia.h - Definitions for a 6551 ACIA interface
 *
 * Written by
 *  Andre Fachat <fachat@physik.tu-chemnitz.de>
 *  Andreas Boose <viceteam@t-online.de>
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

#ifndef VICE_PLUS4ACIA_H
#define VICE_PLUS4ACIA_H

#include "types.h"

struct snapshot_s;

void acia_init(void);
uint8_t acia_read(uint16_t a);
uint8_t acia_peek(uint16_t a);
void acia_store(uint16_t a, uint8_t b);
void acia_reset(void);

int acia_cmdline_options_init(void);
int acia_resources_init(void);

int acia_snapshot_read_module(struct snapshot_s *);
int acia_snapshot_write_module(struct snapshot_s *);

int acia_enabled(void);

#endif
