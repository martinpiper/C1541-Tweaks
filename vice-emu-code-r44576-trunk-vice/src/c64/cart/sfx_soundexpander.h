/*
 * sfx_soundexpander.h
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

#ifndef VICE_SFX_SOUNDEXPANDER_H
#define VICE_SFX_SOUNDEXPANDER_H

#include "types.h"
#include "sound.h"

int sfx_soundexpander_cart_enabled(void);
void sfx_soundexpander_reset(void);
int sfx_soundexpander_enable(void);
int sfx_soundexpander_disable(void);
void sfx_soundexpander_detach(void);

int sfx_soundexpander_resources_init(void);
void sfx_soundexpander_resources_shutdown(void);
int sfx_soundexpander_cmdline_options_init(void);

void sfx_soundexpander_sound_chip_init(void);

struct snapshot_s;

int sfx_soundexpander_snapshot_read_module(struct snapshot_s *s);
int sfx_soundexpander_snapshot_write_module(struct snapshot_s *s);

#endif
