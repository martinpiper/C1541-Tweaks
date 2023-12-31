/*
 * iec128dcr.h
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

#ifndef VICE_IEC128DCR_H
#define VICE_IEC128DCR_H

#include "types.h"

struct diskunit_context_s;

int iec128dcr_drive_resources_init(void);
void iec128dcr_drive_resources_shutdown(void);
int iec128dcr_drive_cmdline_options_init(void);
void iec128dcr_drive_init(struct diskunit_context_s *drv);
void iec128dcr_drive_shutdown(struct diskunit_context_s *drv);
void iec128dcr_drive_reset(struct diskunit_context_s *drv);
void iec128dcr_drive_mem_init(struct diskunit_context_s *drv, unsigned int type);
void iec128dcr_drive_setup_context(struct diskunit_context_s *drv);
void iec128dcr_drive_rom_load(void);
void iec128dcr_drive_rom_setup_image(unsigned int dnr);
int iec128dcr_drive_rom_check_loaded(unsigned int type);

#endif
