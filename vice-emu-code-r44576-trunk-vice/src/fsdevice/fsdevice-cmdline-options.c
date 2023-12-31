/*
 * fsdevice-cmdline-options.c - File system device, command line options.
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

#include "vice.h"

#include <stdio.h>
#include <string.h>

#include "archdep.h"
#include "cmdline.h"
#include "fsdevice.h"
#include "lib.h"
#include "resources.h"
#include "types.h"

#include "fsdevice-cmdline-options.h"


static int cmdline_fsdirectory(const char *param, void *extra_param)
{
    unsigned int unit;
    char directory[ARCHDEP_PATH_MAX];

    unit = vice_ptr_to_uint(extra_param);

    snprintf(directory, ARCHDEP_PATH_MAX - 1U, "%s%s", param, ARCHDEP_DIR_SEP_STR);
    directory[sizeof(directory) - 1] = '\0';

    fsdevice_set_directory(directory, unit);
    return 0;
}

static const cmdline_option_t cmdline_options[] =
{
    /* NOTE: although we use CALL_FUNCTION, we put the resource that will be
             modified into the array - this helps reconstructing the cmdline */
    { "-fs8", CALL_FUNCTION, CMDLINE_ATTRIB_NEED_ARGS,
      cmdline_fsdirectory, (void *)8, "FSDevice8Dir", NULL,
      "<Name>", "Use <name> as directory for file system device #8" },
    { "-fs9", CALL_FUNCTION, CMDLINE_ATTRIB_NEED_ARGS,
      cmdline_fsdirectory, (void *)9, "FSDevice9Dir", NULL,
      "<Name>", "Use <name> as directory for file system device #9" },
    { "-fs10", CALL_FUNCTION, CMDLINE_ATTRIB_NEED_ARGS,
      cmdline_fsdirectory, (void *)10, "FSDevice10Dir", NULL,
      "<Name>", "Use <name> as directory for file system device #10" },
    { "-fs11", CALL_FUNCTION, CMDLINE_ATTRIB_NEED_ARGS,
      cmdline_fsdirectory, (void *)11, "FSDevice11Dir", NULL,
      "<Name>", "Use <name> as directory for file system device #11" },
    { "-fs8convertp00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice8ConvertP00", (resource_value_t)1,
      NULL, "Enable on-read support for P00 files on drive 8" },
    { "+fs8convertp00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice8ConvertP00", (resource_value_t)0,
      NULL, "Disable on-read support for P00 files on drive 8" },
    { "-fs9convertp00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice9ConvertP00", (resource_value_t)1,
      NULL, "Enable on-read support for P00 files on drive 9" },
    { "+fs9convertp00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice9ConvertP00", (resource_value_t)0,
      NULL, "Disable on-read support for P00 files on drive 9" },
    { "-fs10convertp00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice10ConvertP00", (resource_value_t)1,
      NULL, "Enable on-read support for P00 files on drive 10" },
    { "+fs10convertp00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice10ConvertP00", (resource_value_t)0,
      NULL, "Disable on-read support for P00 files on drive 10" },
    { "-fs11convertp00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice11ConvertP00", (resource_value_t)1,
      NULL, "Enable on-read support for P00 files on drive 11" },
    { "+fs11convertp00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice11ConvertP00", (resource_value_t)0,
      NULL, "Disable on-read support for P00 files on drive 11" },
    { "-fs8savep00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice8SaveP00", (resource_value_t)1,
      NULL, "Enable saving of P00 files on drive 8" },
    { "+fs8savep00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice8SaveP00", (resource_value_t)0,
      NULL, "Disable saving of P00 files on drive 8" },
    { "-fs9savep00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice9SaveP00", (resource_value_t)1,
      NULL, "Enable saving of P00 files on drive 9" },
    { "+fs9savep00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice9SaveP00", (resource_value_t)0,
      NULL, "Disable saving of P00 files on drive 9" },
    { "-fs10savep00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice10SaveP00", (resource_value_t)1,
      NULL, "Enable saving of P00 files on drive 10" },
    { "+fs10savep00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice10SaveP00", (resource_value_t)0,
      NULL, "Disable saving of P00 files on drive 10" },
    { "-fs11savep00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice11SaveP00", (resource_value_t)1,
      NULL, "Enable saving of P00 files on drive 11" },
    { "+fs11savep00", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice11SaveP00", (resource_value_t)0,
      NULL, "Disable saving of P00 files on drive 11" },
    { "-fs8hidecbm", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice8HideCBMFiles", (resource_value_t)1,
      NULL, "Hide CBM files (only show P00 files) for drive 8" },
    { "+fs8hidecbm", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice8HideCBMFiles", (resource_value_t)0,
      NULL, "Do not hide CBM files (show all files) for drive 8" },
    { "-fs9hidecbm", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice9HideCBMFiles", (resource_value_t)1,
      NULL, "Hide CBM files (only show P00 files) for drive 9" },
    { "+fs9hidecbm", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice9HideCBMFiles", (resource_value_t)0,
      NULL, "Do not hide CBM files (show all files) for drive 9" },
    { "-fs10hidecbm", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice10HideCBMFiles", (resource_value_t)1,
      NULL, "Hide CBM files (only show P00 files) for drive 10" },
    { "+fs10hidecbm", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice10HideCBMFiles", (resource_value_t)0,
      NULL, "Do not hide CBM files (show all files) for drive 10" },
    { "-fs11hidecbm", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice11HideCBMFiles", (resource_value_t)1,
      NULL, "Hide CBM files (only show P00 files) for drive 11" },
    { "+fs11hidecbm", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDevice11HideCBMFiles", (resource_value_t)0,
      NULL, "Do not hide CBM files (show all files) for drive 11" },
    { "-fslongnames", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDeviceLongNames", (resource_value_t)1,
      NULL, "Allow filenames longer than 16 characters" },
    { "+fslongnames", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDeviceLongNames", (resource_value_t)0,
      NULL, "Do not allow filenames longer than 16 characters" },
    { "-fsoverwrite", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDeviceOverwrite", (resource_value_t)1,
      NULL, "Overwrite files without using SAVE\"@0:name\"" },
    { "+fsoverwrite", SET_RESOURCE, CMDLINE_ATTRIB_NONE,
      NULL, NULL, "FSDeviceOverwrite", (resource_value_t)0,
      NULL, "Refuse to overwrite files without using SAVE\"@0:name\"" },
    CMDLINE_LIST_END
};

int fsdevice_cmdline_options_init(void)
{
    return cmdline_register_options(cmdline_options);
}
