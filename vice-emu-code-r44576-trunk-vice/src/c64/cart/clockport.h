/*
 * clockport.h
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

#ifndef VICE_CLOCKPORT_H
#define VICE_CLOCKPORT_H

#include "types.h"

enum {
    CLOCKPORT_DEVICE_NONE = 0,
    CLOCKPORT_DEVICE_ETH64_II,
    CLOCKPORT_DEVICE_RRNET,
    CLOCKPORT_DEVICE_RRNETMK3,
    CLOCKPORT_DEVICE_SILVER_SURFER,
    CLOCKPORT_DEVICE_MP3_64,
    CLOCKPORT_DEVICE_CW3_SID,

    /* This entry needs to always be at the end */
    CLOCKPORT_MAX_ENTRIES
};

typedef struct clockport_device_s {
    const char *owner;
    int devicenr;
    void (*store)(uint16_t address, uint8_t byte, void *context);
    uint8_t (*read)(uint16_t address, int *valid, void *context);
    uint8_t (*peek)(uint16_t address, void *context);
    void (*reset)(void *context);
    int (*dump)(void *context);
    void (*close)(struct clockport_device_s *device);
    void *device_context;
} clockport_device_t;

typedef struct clockport_device_list_s {
    struct clockport_device_list_s *next;
    clockport_device_t *device;
} clockport_device_list_t;

typedef struct clockport_supported_devices_s {
    int id;
    char *name;
} clockport_supported_devices_t;

int clockport_resources_init(void);
void clockport_resources_shutdown(void);

clockport_device_t *clockport_open_device(int deviceid, const char *owner);
void clockport_close_device(clockport_device_t *device);

extern clockport_supported_devices_t clockport_supported_devices[];

char *clockport_device_id_to_name(int id);

#endif
