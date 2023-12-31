/*
 * SDL_include.h - Wrapper for the SDL header inclusion
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

#ifndef VICE_SDL_INCLUDE
#define VICE_SDL_INCLUDE

#include "vice.h"

/* get rid of some annoying SDL.h / config.h definition duplication warnings */

/* save condition of HAVE_STRDUP and undef HAVE_STRDUP */
#ifdef HAVE_STRDUP
#define HAVE_VICE_STRDUP
#undef HAVE_STRDUP
#endif

/* save condition of HAVE_NANOSLEEP and undef HAVE_NANOSLEEP */
#ifdef HAVE_NANOSLEEP
#define HAVE_VICE_NANOSLEEP
#undef HAVE_NANOSLEEP
#endif

#ifdef USE_SDL2UI
#  include <SDL.h>
#  include <SDL_keycode.h>
#  ifdef INCLUDE_SDL_SYSWM_H
#    include <SDL_syswm.h>
#  endif
#  ifdef HAVE_SDLMAIN
#    include <SDL_main.h>
#  endif
#  include <SDL_opengl.h>
#else
#  ifdef USE_SDL_PREFIX
#    include <SDL/SDL.h>
#    ifdef INCLUDE_SDL_SYSWM_H
#      include <SDL/SDL_syswm.h>
#    endif
#    ifdef HAVE_SDLMAIN
#      include <SDL/SDL_main.h>
#    endif
#    include <SDL/SDL_opengl.h>
#  else
#    include <SDL.h>
#    ifdef INCLUDE_SDL_SYSWM_H
#      include <SDL_syswm.h>
#    endif
#    ifdef HAVE_SDLMAIN
#      include <SDL_main.h>
#    endif
#    include <SDL_opengl.h>
#  endif
#endif

/* restore HAVE_STRDUP definition if it is not defined */
#ifdef HAVE_VICE_STRDUP
#ifndef HAVE_STRDUP
#define HAVE_STRDUP
#endif
#undef HAVE_VICE_STRDUP
#endif

/* restore HAVE_NANOSLEEP definition if it is not defined */
#ifdef HAVE_VICE_NANOSLEEP
#ifndef HAVE_NANOSLEEP
#define HAVE_NANOSLEEP
#endif
#undef HAVE_VICE_NANOSLEEP
#endif

/* SDL_JoystickID handling */
#ifdef USE_SDL2UI
#define VICE_SDL_JoystickID SDL_JoystickID
#else
#define VICE_SDL_JoystickID Sint16
#endif

#endif
