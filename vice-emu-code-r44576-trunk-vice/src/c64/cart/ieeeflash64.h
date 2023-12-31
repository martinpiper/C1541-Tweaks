/*
 * ieeeflash64.h - IEEE Flash! 64 interface emulation
 *
 * Written by
 *  Christopher Bongaarts <cab@bongalow.net>
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

#ifndef VICE_IEEEFLASH64_H
#define VICE_IEEEFLASH64_H

#include <stdio.h>

#include "types.h"
#include "c64cart.h"

struct snapshot_s;

int ieeeflash64_cart_enabled(void);
int ieeeflash64_resources_init(void);
void ieeeflash64_resources_shutdown(void);
int ieeeflash64_cmdline_options_init(void);
void ieeeflash64_passthrough_changed(export_t *export);
int ieeeflash64_enable(void);
int ieeeflash64_disable(void);

int ieeeflash64_mmu_translate(unsigned int addr, uint8_t **base, int *start, int *limit);
uint8_t ieeeflash64_romh_read_hirom(uint16_t addr);
int ieeeflash64_romh_phi1_read(uint16_t addr, uint8_t *value);
int ieeeflash64_romh_phi2_read(uint16_t addr, uint8_t *value);
int ieeeflash64_peek_mem(uint16_t addr, uint8_t *value);

void ieeeflash64_config_init(export_t *ex);
void ieeeflash64_reset(void);
void ieeeflash64_config_setup(uint8_t *rawcart);
int ieeeflash64_bin_attach(const char *filename, uint8_t *rawcart);
int ieeeflash64_crt_attach(FILE *fd, uint8_t *rawcart, const char *filename);
void ieeeflash64_detach(void);
const char *ieeeflash64_get_file_name(void);

int ieeeflash64_snapshot_write_module(struct snapshot_s *s);
int ieeeflash64_snapshot_read_module(struct snapshot_s *s);

#endif
