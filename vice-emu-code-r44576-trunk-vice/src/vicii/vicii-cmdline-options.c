/*
 * vicii-cmdline-options.c - Command-line options for the MOS 6569 (VIC-II)
 * emulation.
 *
 * Written by
 *  Ettore Perazzoli <ettore@comm2000.it>
 *  Andreas Boose <viceteam@t-online.de>
 *  Gunnar Ruthenberg <Krill.Plush@gmail.com>
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
 * */

#include "vice.h"

#include <stdio.h>
#include <string.h>

#include "cmdline.h"
#include "machine.h"
#include "raster-cmdline-options.h"
#include "resources.h"
#include "vicii-cmdline-options.h"
#include "vicii-resources.h"
#include "vicii-timing.h"
#include "vicii.h"
#include "viciitypes.h"


static int border_set_func(const char *value, void *extra_param)
{
    if (strcmp(value, "1") == 0 || strcmp(value, "full") == 0) {
        resources_set_int("VICIIBorderMode", 1);
    } else if (strcmp(value, "2") == 0 || strcmp(value, "debug") == 0) {
        resources_set_int("VICIIBorderMode", 2);
    } else if (strcmp(value, "3") == 0 || strcmp(value, "none") == 0) {
        resources_set_int("VICIIBorderMode", 3);
    } else {
        resources_set_int("VICIIBorderMode", 0);
    }

    return 0;
}

/* VIC-II command-line options.  */
static const cmdline_option_t cmdline_options[] =
{
    /* NOTE: although we use CALL_FUNCTION, we put the resource that will be
             modified into the array - this helps reconstructing the cmdline */
    { "-VICIIborders", CALL_FUNCTION, CMDLINE_ATTRIB_NEED_ARGS,
      border_set_func, NULL, "VICIIBorderMode", NULL,
      "<Mode>", "Set border display mode (0: normal, 1: full, 2: debug, 3: none)" },
    { "-VICIIchecksb", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "VICIICheckSbColl", (void *)1,
      NULL, "Enable sprite-background collision registers" },
    { "+VICIIchecksb", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "VICIICheckSbColl", (void *)0,
      NULL, "Disable sprite-background collision registers" },
    { "-VICIIcheckss", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "VICIICheckSsColl", (void *)1,
      NULL, "Enable sprite-sprite collision registers" },
    { "+VICIIcheckss", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "VICIICheckSsColl", (void *)0,
      NULL, "Disable sprite-sprite collision registers" },
    CMDLINE_LIST_END
};

static const cmdline_option_t cmdline_options_dtv[] =
{
    { "-VICIInewluminance", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "VICIINewLuminances", (void *)1,
      NULL, "Use new luminances" },
    { "+VICIInewluminance", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "VICIINewLuminances", (void *)0,
      NULL, "Use old luminances" },
    CMDLINE_LIST_END
};

int vicii_cmdline_options_init(void)
{
    if (raster_cmdline_options_chip_init("VICII", vicii.video_chip_cap) < 0) {
        return -1;
    }

    if (machine_class == VICE_MACHINE_C64DTV) {
        if (cmdline_register_options(cmdline_options_dtv) < 0) {
            return -1;
        }
    }
    return cmdline_register_options(cmdline_options);
}
