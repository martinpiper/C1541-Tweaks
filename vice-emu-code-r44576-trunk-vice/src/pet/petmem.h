/*
 * petmem.h - PET memory handling.
 *
 * Written by
 *  Ettore Perazzoli <ettore@comm2000.it>
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

#ifndef VICE_PETMEM_H
#define VICE_PETMEM_H

#include <stdio.h>

#include "mem.h"
#include "types.h"

#define PET_RAM_SIZE            0x8000
#define PET_ROM_SIZE            0x8000
#define PET_CHARGEN_ROM_SIZE    0x4000

extern uint8_t mem_chargen_rom[PET_CHARGEN_ROM_SIZE];
extern uint8_t mem_rom[PET_ROM_SIZE];
extern uint8_t mem_6809rom[];

struct petres_s;
struct petinfo_s;

int pet_mem_init_resources(void);
int pet_mem_init_cmdline_options(void);

void mem_initialize_memory(void);
void get_mem_access_tables(read_func_ptr_t **read, store_func_ptr_t **write, uint8_t ***base, int **limit);
int petmem_get_screen_columns(void);
int petmem_get_rom_columns(void);
void petmem_check_info(struct petres_s *pi);

void petmem_reset(void);
int petmem_superpet_diag(void);
void petmem_set_vidmem(void);

int petmem_dump(FILE *fp);
int petmem_undump(FILE *fp);

int petmem_set_conf_info(const struct petinfo_s *pi);

extern int spet_ramen;
extern int spet_bank;
extern void set_spet_bank(int bank);
extern int spet_ctrlwp;
extern int spet_diag;
extern int spet_ramwp;
extern int spet_flat_mode;
extern int spet_firq_disabled;

struct dongle6702_s {
    int val;
    int prevodd;
    int wantodd;
    int shift[8];
};

extern struct dongle6702_s dongle6702;

extern uint8_t petmem_map_reg;
extern uint8_t petmem_ramON;
extern uint8_t petmem_2001_buf_ef[];

extern read_func_t mem6809_read;
extern store_func_t mem6809_store;

void mem6809_store16(uint16_t addr, uint16_t value);
uint16_t mem6809_read16(uint16_t addr);

#ifdef H6309
void mem6809_store32(uint16_t addr, uint32_t value);
uint32_t mem6809_read32(uint16_t addr);
#endif

void mem_initialize_memory_6809(void);
void ramsel_changed(void);

int superpet_sync(void);

uint8_t read_unused(uint16_t addr);

#endif
