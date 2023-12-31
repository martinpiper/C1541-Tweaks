/*
 * fsdevice-read.h - File system device.
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

#ifndef VICE_FSDEVICE_READ_H
#define VICE_FSDEVICE_READ_H

#include "types.h"

struct vdrive_s;
struct bufinfo_s;

int fsdevice_read(struct vdrive_s *vdrive, uint8_t *data,
                  unsigned int secondary);
void fsdevice_relative_pad_record(struct bufinfo_s *bufinfo);
int fsdevice_relative_switch_record(struct vdrive_s *vdrive,
                                    struct bufinfo_s *bufinfo,
                                    int record, int pos);

#endif
