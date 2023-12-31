/*
 * c64dtvdma.h - C64DTV DMA controller
 *
 * Written by
 *  M.Kiesel <mayne@users.sourceforge.net>
 *  Daniel Kahlin <daniel@kahlin.net>
 * Based on code by
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

#ifndef VICE_C64DTVDMA_H
#define VICE_C64DTVDMA_H

#include "types.h"

extern int dma_active;
extern int dma_on_irq;

int c64dtvdma_resources_init(void);
void c64dtvdma_resources_shutdown(void);
int c64dtvdma_cmdline_options_init(void);
void c64dtvdma_init(void);
void c64dtvdma_reset(void);
void c64dtvdma_shutdown(void);

uint8_t c64dtv_dma_read(uint16_t addr);
void c64dtv_dma_store(uint16_t addr, uint8_t value);
void c64dtvdma_perform_dma(void);
void c64dtvdma_trigger_dma(void);

struct snapshot_s;

int c64dtvdma_snapshot_write_module(struct snapshot_s *s);
int c64dtvdma_snapshot_read_module(struct snapshot_s *s);

#endif
