/*
 * cbm2-resources.h
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

#ifndef VICE_CBM2_RESOURCES_H
#define VICE_CBM2_RESOURCES_H

int cbm2_resources_init(void);
void cbm2_resources_shutdown(void);

extern int cart08_ram;
extern int cart1_ram;
extern int cart2_ram;
extern int cart4_ram;
extern int cart6_ram;
extern int cartC_ram;

extern int cbm2_model_line;
extern int ramsize;
extern int cia1_model;

#endif
