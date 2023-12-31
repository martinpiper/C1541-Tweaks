/*
 * menu_edit.c - Implementation of the EDIT for the SDL UI.
 *
 * Written by
 *  groepaz <groepaz@gmx.net>
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

#include "vice.h"

#include "menu_common.h"
#include "uiactions.h"

#include "menu_edit.h"

#ifdef USE_SDL2UI
const ui_menu_entry_t edit_menu[3] = {
    {   .action    = ACTION_EDIT_COPY,
        .string    = "Copy to Clipboard",
        .type      = MENU_ENTRY_OTHER,
        .activated = MENU_EXIT_UI_STRING
    },
    {   .action    = ACTION_EDIT_PASTE,
        .string    = "Paste from Clipboard",
        .type      = MENU_ENTRY_OTHER,
        .activated = MENU_EXIT_UI_STRING
    },
    SDL_MENU_LIST_END
};
#endif
