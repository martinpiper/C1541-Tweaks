/*
 * vic20ieeevia.h - IEEE488 interface VIA emulation.
 *
 * Written by
 *  Andre Fachat <fachat@physik.tu-chemnitz.de>
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

#ifndef VICE_VIC20IEEEVIA_H
#define VICE_VIC20IEEEVIA_H

#include "types.h"

struct machine_context_s;
struct via_context_s;

int ieeevia1_dump(void);
void vic20ieeevia1_setup_context(struct machine_context_s *machine_context);
void ieeevia1_init(struct via_context_s *via_context);
void ieeevia1_store(uint16_t addr, uint8_t byte);
uint8_t ieeevia1_read(uint16_t addr);
uint8_t ieeevia1_peek(uint16_t addr);

int ieeevia2_dump(void);
void vic20ieeevia2_setup_context(struct machine_context_s *machine_context);
void ieeevia2_init(struct via_context_s *via_context);
void ieeevia2_store(uint16_t addr, uint8_t byte);
uint8_t ieeevia2_read(uint16_t addr);
uint8_t ieeevia2_peek(uint16_t addr);

void ieeevia2_set_tape_sense(int v);

#endif
