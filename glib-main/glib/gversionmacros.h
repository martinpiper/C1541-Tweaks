/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __G_VERSION_MACROS_H__
#define __G_VERSION_MACROS_H__

#if !defined(__GLIB_H_INSIDE__) && !defined(GLIB_COMPILATION)
#error "Only <glib.h> can be included directly."
#endif

/* Version boundaries checks */

#define G_ENCODE_VERSION(major, minor) ((major) << 16 | (minor) << 8)

//@GLIB_VERSIONS@

/**
 * GLIB_VERSION_CUR_STABLE:
 *
 * A macro that evaluates to the current stable version of GLib, in a format
 * that can be used by the C pre-processor.
 *
 * During an unstable development cycle, this evaluates to the next stable
 * (unreleased) version which will be the result of the development cycle.
 *
 * Since: 2.32
 */
#define GLIB_VERSION_CUR_STABLE (G_ENCODE_VERSION (GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION))

/**
 * GLIB_VERSION_PREV_STABLE:
 *
 * A macro that evaluates to the previous stable version of GLib, in a format
 * that can be used by the C pre-processor.
 *
 * During an unstable development cycle, this evaluates to the most recent
 * released stable release, which preceded this development cycle.
 *
 * Since: 2.32
 */
#define GLIB_VERSION_PREV_STABLE (G_ENCODE_VERSION (GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION - 2))

/**
 * GLIB_VERSION_MIN_REQUIRED:
 *
 * A macro that should be defined by the user prior to including
 * the glib.h header.
 * The definition should be one of the predefined GLib version
 * macros: %GLIB_VERSION_2_26, %GLIB_VERSION_2_28,...
 *
 * This macro defines the earliest version of GLib that the package is
 * required to be able to compile against.
 *
 * If the compiler is configured to warn about the use of deprecated
 * functions, then using functions that were deprecated in version
 * %GLIB_VERSION_MIN_REQUIRED or earlier will cause warnings (but
 * using functions deprecated in later releases will not).
 *
 * Since: 2.32
 */
/* If the package sets GLIB_VERSION_MIN_REQUIRED to some future
 * GLIB_VERSION_X_Y value that we don't know about, it will compare as
 * 0 in preprocessor tests.
 */
#ifndef GLIB_VERSION_MIN_REQUIRED
#define GLIB_VERSION_MIN_REQUIRED (GLIB_VERSION_CUR_STABLE)
#elif GLIB_VERSION_MIN_REQUIRED == 0
#undef GLIB_VERSION_MIN_REQUIRED
#define GLIB_VERSION_MIN_REQUIRED (GLIB_VERSION_CUR_STABLE + 2)
#endif

/**
 * GLIB_VERSION_MAX_ALLOWED:
 *
 * A macro that should be defined by the user prior to including
 * the glib.h header.
 * The definition should be one of the predefined GLib version
 * macros: %GLIB_VERSION_2_26, %GLIB_VERSION_2_28,...
 *
 * This macro defines the latest version of the GLib API that the
 * package is allowed to make use of.
 *
 * If the compiler is configured to warn about the use of deprecated
 * functions, then using functions added after version
 * %GLIB_VERSION_MAX_ALLOWED will cause warnings.
 *
 * Unless you are using GLIB_CHECK_VERSION() or the like to compile
 * different code depending on the GLib version, then this should be
 * set to the same value as %GLIB_VERSION_MIN_REQUIRED.
 *
 * Since: 2.32
 */
#if !defined(GLIB_VERSION_MAX_ALLOWED) || (GLIB_VERSION_MAX_ALLOWED == 0)
#undef GLIB_VERSION_MAX_ALLOWED
#define GLIB_VERSION_MAX_ALLOWED (GLIB_VERSION_CUR_STABLE)
#endif

/* sanity checks */

#endif /*  __G_VERSION_MACROS_H__ */
