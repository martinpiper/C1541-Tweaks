/** \file   settings_finalexpansion.c
 * \brief   Settings widget controlling VIC-20 Final Expansion resources
 *
 * \author  Bas Wassink <b.wassink@ziggo.nl>
 */

/*
 * $VICERES FinalExpansionWriteBack     xvic
 */

/*
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
#include <gtk/gtk.h>

#include "cartridge.h"
#include "vice_gtk3.h"

#include "settings_finalexpansion.h"


/** \brief  Create widget to control Final Expansion resources
 *
 * \param[in]   parent  parent widget (unused)
 *
 * \return  GtkGrid
 */
GtkWidget *settings_finalexpansion_widget_create(GtkWidget *parent)
{
    GtkWidget *grid;
    GtkWidget *check;

    grid  = gtk_grid_new();
    check = vice_gtk3_resource_check_button_new("FinalExpansionWriteBack",
                                                "Enable "
                                                CARTRIDGE_VIC20_NAME_FINAL_EXPANSION
                                                " image write back");

    gtk_grid_attach(GTK_GRID(grid), check, 0, 0, 1, 1);
    gtk_widget_show_all(grid);

    return grid;
}
