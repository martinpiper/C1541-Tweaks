/*
 * viad.h - Drive VIA definitions.
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

#ifndef VICE_VIAD_H
#define VICE_VIAD_H

#include "types.h"

struct diskunit_context_s;
struct drive_s;

void via2d_setup_context(struct diskunit_context_s *ctxptr);

void via2d_init(struct diskunit_context_s *ctxptr);
void via2d_store(struct diskunit_context_s *ctxptr, uint16_t addr, uint8_t byte);
uint8_t via2d_read(struct diskunit_context_s *ctxptr, uint16_t addr);
uint8_t via2d_peek(struct diskunit_context_s *ctxptr, uint16_t addr);
int via2d_dump(struct diskunit_context_s *ctxptr, uint16_t addr);

void via2d_update_pcr(int pcrval, struct drive_s *dptr);

#endif
