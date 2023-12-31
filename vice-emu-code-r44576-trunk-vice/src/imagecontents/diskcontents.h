/*
 * diskcontents.h
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

#ifndef VICE_DISKCONTENTS_H
#define VICE_DISKCONTENTS_H

struct image_contents_s;

struct image_contents_s *diskcontents_read(const char *file_name,
                                           unsigned int unit, unsigned int drive);
struct image_contents_s *diskcontents_filesystem_read(const char *file_name);
struct image_contents_s *diskcontents_read_unit8(const char *file_name);
struct image_contents_s *diskcontents_read_unit9(const char *file_name);
struct image_contents_s *diskcontents_read_unit10(const char *file_name);
struct image_contents_s *diskcontents_read_unit11(const char *file_name);

#endif
