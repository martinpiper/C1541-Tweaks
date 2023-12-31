/*
 * iec.h - IEC drive specific routines.
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

#ifndef VICE_IEC_H
#define VICE_IEC_H

#include "types.h"

struct disk_image_s;
struct diskunit_context_s;
struct snapshot_s;

int iec_drive_resources_init(void);
void iec_drive_resources_shutdown(void);
int iec_drive_cmdline_options_init(void);
void iec_drive_init(struct diskunit_context_s *drv);
void iec_drive_shutdown(struct diskunit_context_s *drv);
void iec_drive_reset(struct diskunit_context_s *drv);
void iec_drive_mem_init(struct diskunit_context_s *drv, unsigned int type);
void iec_drive_setup_context(struct diskunit_context_s *drv);
void iec_drive_idling_method(unsigned int dnr);
void iec_drive_rom_load(void);
void iec_drive_rom_setup_image(unsigned int dnr);
int iec_drive_rom_check_loaded(unsigned int type);
void iec_drive_rom_do_checksum(unsigned int dnr);
int iec_drive_snapshot_read(struct diskunit_context_s *ctxptr, struct snapshot_s *s);
int iec_drive_snapshot_write(struct diskunit_context_s *ctxptr, struct snapshot_s *s);
int iec_drive_image_attach(struct disk_image_s *image, unsigned int unit, unsigned int drive);
int iec_drive_image_detach(struct disk_image_s *image, unsigned int unit, unsigned int drive);
void iec_drive_port_default(struct diskunit_context_s *drv);

#endif
