/*
 * bq4830y.h - BQ4830Y RTC emulation.
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

#ifndef VICE_BQ4830Y_H
#define VICE_BQ4830Y_H

#include <time.h>

#include "snapshot.h"
#include "types.h"

#define BQ4830Y_RAM_SIZE   0x8000
#define BQ4830Y_REG_SIZE   8

typedef struct rtc_bq4830y_s {
    int clock_halt;
    time_t clock_halt_latch;
    int read_latch;
    int write_latch;
    time_t latch;
    time_t offset;
    time_t old_offset;
    uint8_t *clock_regs;
    uint8_t old_clock_regs[BQ4830Y_REG_SIZE];
    uint8_t clock_regs_changed[BQ4830Y_REG_SIZE];
    uint8_t *ram;
    uint8_t old_ram[BQ4830Y_RAM_SIZE];
    char *device;
} rtc_bq4830y_t;

#define BQ4830Y_REG_CONTROL         0x7FF8
#define BQ4830Y_REG_SECONDS         0x7FF9
#define BQ4830Y_REG_MINUTES         0x7FFA
#define BQ4830Y_REG_HOURS           0x7FFB
#define BQ4830Y_REG_DAYS_OF_WEEK    0x7FFC
#define BQ4830Y_REG_DAYS_OF_MONTH   0x7FFD
#define BQ4830Y_REG_MONTHS          0x7FFE
#define BQ4830Y_REG_YEARS           0x7FFF

enum {
    LATCH_NONE = 0,
    READ_LATCH,
    WRITE_LATCH,
    READ_WRITE_LATCH,
    CLOCK_LATCH,
    CLOCK_READ_LATCH,
    CLOCK_WRITE_LATCH,
    CLOCK_READ_WRITE_LATCH
};

rtc_bq4830y_t *bq4830y_init(char *device);
void bq4830y_destroy(rtc_bq4830y_t *context, int save);

void bq4830y_store(rtc_bq4830y_t *context, uint16_t address, uint8_t val);
uint8_t bq4830y_read(rtc_bq4830y_t *context, uint16_t address);
int bq4830y_write_snapshot(rtc_bq4830y_t *context, snapshot_t *s);
int bq4830y_read_snapshot(rtc_bq4830y_t *context, snapshot_t *s);

#endif
