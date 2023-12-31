/*
 * ted-mem.h - Memory interface for the TED emulation.
 *
 * Written by
 *  Andreas Boose <viceteam@t-online.de>
 *  Ettore Perazzoli <ettore@comm2000.it>
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

#ifndef VICE_TED_MEM_H
#define VICE_TED_MEM_H

#include "types.h"

void ted_store(uint16_t addr, uint8_t value);
uint8_t ted_read(uint16_t addr);
uint8_t ted_peek(uint16_t addr);
uint8_t colorram_read(uint16_t addr);
void colorram_store(uint16_t addr, uint8_t value);
void ted_mem_vbank_store(uint16_t addr, uint8_t value);
void ted_mem_vbank_store_32k(uint16_t addr, uint8_t value);
void ted_mem_vbank_store_16k(uint16_t addr, uint8_t value);

#if 0
void ted_mem_vbank_39xx_store(uint16_t addr, uint8_t value);
void ted_mem_vbank_3fxx_store(uint16_t addr, uint8_t value);
#endif

#endif
