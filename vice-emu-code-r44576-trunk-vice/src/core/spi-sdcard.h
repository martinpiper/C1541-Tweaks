/*
 * spi-sdcard.h - SD Card over SPI Emulation
 *
 * Written by
 *  Groepaz/Hitmen <groepaz@gmx.net>
 * large parts derived from mmc64.c written by
 *  Markus Stehr <bastetfurry@ircnet.de>
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

#ifndef VICE_SPI_SDCARD
#define VICE_SPI_SDCARD

#include "types.h"

void spi_mmc_trigger_mode_write(uint8_t value);
uint8_t spi_mmc_trigger_mode_read(void);
uint8_t spi_mmc_card_inserted(void);
uint8_t spi_mmc_busy(void);
uint8_t spi_mmc_card_write_enabled(void);
uint8_t spi_mmc_card_selected_read(void);
void spi_mmc_card_selected_write(uint8_t value);
uint8_t spi_mmc_enable_8mhz_read(void);
void spi_mmc_enable_8mhz_write(uint8_t value);
uint8_t spi_mmc_trigger_mode_read(void);
void spi_mmc_trigger_mode_write(uint8_t value);
uint8_t spi_mmc_data_read(void);
void spi_mmc_data_write(uint8_t value);
int  mmc_open_card_image(char *name, int rw);
void mmc_close_card_image(void);
uint8_t mmc_set_card_type(uint8_t value);

struct snapshot_s;

int mmc_snapshot_read_module(struct snapshot_s *s);
int mmc_snapshot_write_module(struct snapshot_s *s);

#endif
