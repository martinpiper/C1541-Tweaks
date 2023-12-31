/*
 * parallel-trap.h
 *
 * Written by
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

#ifndef VICE_PARALLEL_TRAP_H
#define VICE_PARALLEL_TRAP_H

#include "types.h"

int parallel_trap_attention(int b);
int parallel_trap_sendbyte(uint8_t data);
int parallel_trap_receivebyte(uint8_t *data, int fake);

/* Same as SERIAL_EOF and SERIAL_DEVICE_NOT_PRESENT */
#define PAR_STATUS_TIME_OUT_ON_WRITE    0x01
#define PAR_STATUS_TIME_OUT_ON_READ     0x02
#define PAR_STATUS_EOI                  0x40
#define PAR_STATUS_DEVICE_NOT_PRESENT   0x80

#endif
