/*
 * Copyright © 2011 Red Hat, Inc
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
 *
 * Author: Matthias Clasen
 */


/* This file collects documentation for macros, typedefs and
 * the like, which have no good home in any of the 'real' source
 * files.
 */

/* Basic types {{{1 */

/**
 * SECTION:types
 * @title: Basic Types
 * @short_description: standard GLib types, defined for ease-of-use
 *     and portability
 *
 * GLib defines a number of commonly used types, which can be divided
 * into several groups:
 * - New types which are not part of standard C (but are defined in
 *   various C standard library header files) — #gboolean, #gssize.
 * - Integer types which are guaranteed to be the same size across
 *   all platforms — #gint8, #guint8, #gint16, #guint16, #gint32,
 *   #guint32, #gint64, #guint64.
 * - Types which are easier to use than their standard C counterparts -
 *   #gpointer, #gconstpointer, #guchar, #guint, #gushort, #gulong.
 * - Types which correspond exactly to standard C types, but are
 *   included for completeness — #gchar, #gint, #gshort, #glong,
 *   #gfloat, #gdouble.
 * - Types which correspond exactly to standard C99 types, but are available
 *   to use even if your compiler does not support C99 — #gsize, #goffset,
 *   #gintptr, #guintptr.
 *
 * GLib also defines macros for the limits of some of the standard
 * integer and floating point types, as well as macros for suitable
 * printf() formats for these types.
 *
 * Note that depending on the platform and build configuration, the format
 * macros might not be compatible with the system provided printf() function,
 * because GLib might use a different printf() implementation internally.
 * The format macros will always work with GLib API (like g_print()), and with
 * any C99 compatible printf() implementation.
 */

/**
 * gboolean:
 *
 * A standard boolean type.
 * Variables of this type should only contain the value
 * %TRUE or %FALSE.
 *
 * Never directly compare the contents of a #gboolean variable with the values
 * %TRUE or %FALSE. Use `if (condition)` to check a #gboolean is "true", instead
 * of `if (condition == TRUE)`. Likewise use `if (!condition)` to check a
 * #gboolean is "false".
 *
 * There is no validation when assigning to a #gboolean variable and so it could
 * contain any value represented by a #gint. This is why the use of `if
 * (condition)` is recommended. All non-zero values in C evaluate to "true".
 */

/**
 * gpointer:
 *
 * An untyped pointer, exactly equivalent to `void *`.
 *
 * The standard C `void *` type should usually be preferred in
 * new code, but `gpointer` can be used in contexts where a type name
 * must be a single word, such as in the g_type_name() of %G_TYPE_POINTER
 * or when generating a family of function names for multiple types
 * using macros.
 */

/**
 * gconstpointer:
 *
 * An untyped pointer to constant data, exactly equivalent to `const void *`.
 *
 * The data pointed to should not be changed.
 *
 * This is typically used in function prototypes to indicate
 * that the data pointed to will not be altered by the function.
 *
 * The standard C `const void *` type should usually be preferred in
 * new code, but `gconstpointer` can be used in contexts where a type name
 * must be a single word.
 */

/**
 * gchar:
 *
 * Equivalent to the standard C `char` type.
 *
 * This type only exists for symmetry with `guchar`.
 * The standard C `char` type should be preferred in new code.
 */

/**
 * guchar:
 *
 * Equivalent to the standard C `unsigned char` type.
 *
 * The standard C `unsigned char` type should usually be preferred in
 * new code, but `guchar` can be used in contexts where a type name
 * must be a single word, such as in the g_type_name() of %G_TYPE_UCHAR
 * or when generating a family of function names for multiple types
 * using macros.
 */

/**
 * gint:
 *
 * Equivalent to the standard C `int` type.
 *
 * Values of this type can range from `INT_MIN` to `INT_MAX`,
 * or equivalently from %G_MININT to %G_MAXINT.
 *
 * This type only exists for symmetry with `guint`.
 * The standard C `int` type should be preferred in new code.
 */

/**
 * G_MININT:
 *
 * The minimum value which can be held in a #gint.
 *
 * This is the same as standard C `INT_MIN`, which is available since C99
 * and should be preferred in new code.
 */

/**
 * G_MAXINT:
 *
 * The maximum value which can be held in a #gint.
 *
 * This is the same as standard C `INT_MAX`, which is available since C99
 * and should be preferred in new code.
 */

/**
 * guint:
 *
 * Equivalent to the standard C `unsigned int` type.
 *
 * Values of this type can range from 0 to `UINT_MAX`,
 * or equivalently 0 to %G_MAXUINT.
 *
 * The standard C `unsigned int` type should usually be preferred in
 * new code, but `guint` can be used in contexts where a type name
 * must be a single word, such as in the g_type_name() of %G_TYPE_UINT
 * or when generating a family of function names for multiple types
 * using macros.
 */

/**
 * G_MAXUINT:
 *
 * The maximum value which can be held in a #guint.
 *
 * This is the same as standard C `UINT_MAX`, which is available since C99
 * and should be preferred in new code.
 */

/**
 * gshort:
 *
 * Equivalent to the standard C `short` type.
 *
 * Values of this type can range from `SHRT_MIN` to `SHRT_MAX`,
 * or equivalently %G_MINSHORT to %G_MAXSHORT.
 *
 * This type only exists for symmetry with `gushort`.
 * The standard C `short` type should be preferred in new code.
 */

/**
 * G_MINSHORT:
 *
 * The minimum value which can be held in a #gshort.
 *
 * This is the same as standard C `SHRT_MIN`, which is available since C99
 * and should be preferred in new code.
 */

/**
 * G_MAXSHORT:
 *
 * The maximum value which can be held in a #gshort.
 *
 * This is the same as standard C `SHRT_MAX`, which is available since C99
 * and should be preferred in new code.
 */

/**
 * gushort:
 *
 * Equivalent to the standard C `unsigned short` type.
 *
 * Values of this type can range from 0 to `USHRT_MAX`,
 * or equivalently from 0 to %G_MAXUSHORT.
 *
 * The standard C `unsigned short` type should usually be preferred in
 * new code, but `gushort` can be used in contexts where a type name
 * must be a single word, such as when generating a family of function
 * names for multiple types using macros.
 */

/**
 * G_MAXUSHORT:
 *
 * The maximum value which can be held in a #gushort.
 *
 * This is the same as standard C `USHRT_MAX`, which is available since C99
 * and should be preferred in new code.
 */

/**
 * glong:
 *
 * Equivalent to the standard C `long` type.
 *
 * Values of this type can range from `LONG_MIN` to `LONG_MAX`,
 * or equivalently %G_MINLONG to %G_MAXLONG.
 *
 * This type only exists for symmetry with `gulong`.
 * The standard C `long` type should be preferred in new code.
 */

/**
 * G_MINLONG:
 *
 * The minimum value which can be held in a #glong.
 *
 * This is the same as standard C `LONG_MIN`, which is available since C99
 * and should be preferred in new code.
 */

/**
 * G_MAXLONG:
 *
 * The maximum value which can be held in a #glong.
 *
 * This is the same as standard C `ULONG_MAX`, which is available since C99
 * and should be preferred in new code.
 */

/**
 * gulong:
 *
 * Equivalent to the standard C `unsigned long` type.
 *
 * Values of this type can range from 0 to %G_MAXULONG.
 *
 * The standard C `unsigned long` type should usually be preferred in
 * new code, but `gulong` can be used in contexts where a type name
 * must be a single word, such as in the g_type_name() of %G_TYPE_ULONG
 * or when generating a family of function names for multiple types
 * using macros.
 */

/**
 * G_MAXULONG:
 *
 * The maximum value which can be held in a #gulong.
 *
 * This is the same as standard C `ULONG_MAX`, which is available since C99
 * and should be preferred in new code.
 */

/**
 * gint8:
 *
 * A signed integer guaranteed to be 8 bits on all platforms,
 * similar to the standard C `int8_t`.
 *
 * The `int8_t` type should be preferred in new code, unless
 * consistency with pre-existing APIs requires use of `gint8`
 * (see #gsize for more details).
 *
 * Values of this type can range from %G_MININT8 (= -128) to
 * %G_MAXINT8 (= 127).
 */

/**
 * G_MAXINT8:
 *
 * The maximum value which can be held in a #gint8.
 *
 * This is the same as standard C `INT8_MAX`, which should be
 * preferred in new code.
 *
 * Since: 2.4
 */

/**
 * guint8:
 *
 * An unsigned integer guaranteed to be 8 bits on all platforms,
 * similar to the standard C `uint8_t`.
 *
 * The `uint8_t` type should be preferred in new code, unless
 * consistency with pre-existing APIs requires use of `guint8`
 * (see #gsize for more details).
 *
 * Values of this type can range from 0 to %G_MAXUINT8 (= 255).
 */

/**
 * G_MAXUINT8:
 *
 * The maximum value which can be held in a #guint8.
 *
 * This is the same as standard C `UINT8_MAX`, which should be
 * preferred in new code.
 *
 * Since: 2.4
 */

/**
 * gint16:
 *
 * A signed integer guaranteed to be 16 bits on all platforms,
 * similar to the standard C `int16_t`.
 *
 * The `int16_t` type should be preferred in new code, unless
 * consistency with pre-existing APIs requires use of `gint16`
 * (see #gsize for more details).
 *
 * Values of this type can range from %G_MININT16 (= -32,768) to
 * %G_MAXINT16 (= 32,767).
 *
 * To print or scan values of this type, use
 * %G_GINT16_MODIFIER and/or %G_GINT16_FORMAT.
 */

/**
 * G_MAXINT16:
 *
 * The maximum value which can be held in a #gint16.
 *
 * This is the same as standard C `INT16_MAX`, which should be
 * preferred in new code.
 *
 * Since: 2.4
 */

/**
 * G_GINT16_MODIFIER:
 *
 * The platform dependent length modifier for conversion specifiers
 * for scanning and printing values of type #gint16 or #guint16. It
 * is a string literal, but doesn't include the percent-sign, such
 * that you can add precision and length modifiers between percent-sign
 * and conversion specifier and append a conversion specifier.
 *
 * The following example prints "0x7b";
 * |[<!-- language="C" -->
 * gint16 value = 123;
 * g_print ("%#" G_GINT16_MODIFIER "x", value);
 * ]|
 *
 * This is not necessarily the correct modifier for printing and scanning
 * `int16_t` values, even though the in-memory representation is the same.
 * Standard C macros like `PRId16` and `SCNd16` should be used for `int16_t`.
 *
 * Since: 2.4
 */

/**
 * G_GINT16_FORMAT:
 *
 * This is the platform dependent conversion specifier for scanning and
 * printing values of type #gint16. It is a string literal, but doesn't
 * include the percent-sign, such that you can add precision and length
 * modifiers between percent-sign and conversion specifier.
 *
 * |[<!-- language="C" -->
 * gint16 in;
 * gint32 out;
 * sscanf ("42", "%" G_GINT16_FORMAT, &in)
 * out = in * 1000;
 * g_print ("%" G_GINT32_FORMAT, out);
 *
 * This is not necessarily the correct format for printing and scanning
 * `int16_t` values, even though the in-memory representation is the same.
 * Standard C macros like `PRId16` and `SCNd16` should be used for `int16_t`.
 * ]|
 */

/**
 * guint16:
 *
 * An unsigned integer guaranteed to be 16 bits on all platforms,
 * similar to the standard C `uint16_t`.
 *
 * The `uint16_t` type should be preferred in new code, unless
 * consistency with pre-existing APIs requires use of `guint16`
 * (see #gsize for more details).
 *
 * Values of this type can range from 0 to %G_MAXUINT16 (= 65,535).
 *
 * To print or scan values of this type, use
 * %G_GINT16_MODIFIER and/or %G_GUINT16_FORMAT.
 */

/**
 * G_MAXUINT16:
 *
 * The maximum value which can be held in a #guint16.
 *
 * This is the same as standard C `UINT16_MAX`, which should be
 * preferred in new code.
 *
 * Since: 2.4
 */

/**
 * G_GUINT16_FORMAT:
 *
 * This is the platform dependent conversion specifier for scanning
 * and printing values of type #guint16. See also %G_GINT16_FORMAT
 *
 * This is not necessarily the correct modifier for printing and scanning
 * `uint16_t` values, even though the in-memory representation is the same.
 * Standard C macros like `PRIu16` and `SCNu16` should be used for `uint16_t`.
 */

/**
 * gint32:
 *
 * A signed integer guaranteed to be 32 bits on all platforms.
 *
 * The `int32_t` type should be preferred in new code, unless
 * consistency with pre-existing APIs requires use of `gint16`
 * (see #gsize for more details).
 *
 * Values of this type can range from %G_MININT32 (= -2,147,483,648)
 * to %G_MAXINT32 (= 2,147,483,647).
 *
 * To print or scan values of this type, use
 * %G_GINT32_MODIFIER and/or %G_GINT32_FORMAT.
 *
 * Note that on platforms with more than one 32-bit standard integer type,
 * `gint32` and `int32_t` are not necessarily implemented by the same
 * 32-bit integer type.
 * For example, on an ILP32 platform where `int` and `long` are both 32-bit,
 * it might be the case that one of these types is `int` and the other
 * is `long`.
 * See #gsize for more details of what this implies.
 */

/**
 * G_MAXINT32:
 *
 * The maximum value which can be held in a #gint32.
 *
 * This is the same as standard C `INT32_MAX`, which should be
 * preferred in new code.
 *
 * Since: 2.4
 */

/**
 * G_GINT32_MODIFIER:
 *
 * The platform dependent length modifier for conversion specifiers
 * for scanning and printing values of type #gint32 or #guint32. It
 * is a string literal. See also %G_GINT16_MODIFIER.
 *
 * This is not necessarily the correct modifier for printing and scanning
 * `int32_t` values, even though the in-memory representation is the same.
 * Standard C macros like `PRId32` and `SCNd32` should be used for `int32_t`.
 *
 * Since: 2.4
 */

/**
 * G_GINT32_FORMAT:
 *
 * This is the platform dependent conversion specifier for scanning
 * and printing values of type #gint32. See also %G_GINT16_FORMAT.
 *
 * This is not necessarily the correct modifier for printing and scanning
 * `int32_t` values, even though the in-memory representation is the same.
 * Standard C macros like `PRId32` and `SCNd32` should be used for `int32_t`.
 */

/**
 * guint32:
 *
 * An unsigned integer guaranteed to be 32 bits on all platforms,
 * similar to the standard C `uint32_t`.
 *
 * The `uint32_t` type should be preferred in new code, unless
 * consistency with pre-existing APIs requires use of `guint32`
 * (see #gsize for more details).
 *
 * Values of this type can range from 0 to %G_MAXUINT32 (= 4,294,967,295).
 *
 * To print or scan values of this type, use
 * %G_GINT32_MODIFIER and/or %G_GUINT32_FORMAT.
 *
 * Note that on platforms with more than one 32-bit standard integer type,
 * `guint32` and `uint32_t` are not necessarily implemented by the same
 * 32-bit integer type.
 * See #gsize for more details of what this implies.
 */

/**
 * G_MAXUINT32:
 *
 * The maximum value which can be held in a #guint32.
 *
 * This is the same as standard C `UINT32_MAX`, which should be
 * preferred in new code.
 *
 * Since: 2.4
 */

/**
 * G_GUINT32_FORMAT:
 *
 * This is the platform dependent conversion specifier for scanning
 * and printing values of type #guint32. See also %G_GINT16_FORMAT.
 *
 * This is not necessarily the correct modifier for printing and scanning
 * `uint32_t` values, even though the in-memory representation is the same.
 * Standard C macros like `PRIu32` and `SCNu32` should be used for `uint32_t`.
 */

/**
 * gint64:
 *
 * A signed integer guaranteed to be 64 bits on all platforms,
 * similar to the standard C `int64_t`.
 *
 * The `int64_t` type should be preferred in new code, unless
 * consistency with pre-existing APIs requires use of `gint64`
 * (see #gsize for more details).
 *
 * Values of this type can range from %G_MININT64
 * (= -9,223,372,036,854,775,808) to %G_MAXINT64
 * (= 9,223,372,036,854,775,807).
 *
 * To print or scan values of this type, use
 * %G_GINT64_MODIFIER and/or %G_GINT64_FORMAT.
 *
 * Note that on platforms with more than one 64-bit standard integer type,
 * `gint64` and `int64_t` are not necessarily implemented by the same
 * 64-bit integer type.
 * For example, on a platform where both `long` and `long long` are 64-bit,
 * it might be the case that one of those types is used for `gint64`
 * and the other is used for `int64_t`.
 * See #gsize for more details of what this implies.
 */

/**
 * G_MAXINT64:
 *
 * The maximum value which can be held in a #gint64.
 */

/**
 * G_GINT64_MODIFIER:
 *
 * The platform dependent length modifier for conversion specifiers
 * for scanning and printing values of type #gint64 or #guint64.
 * It is a string literal.
 *
 * Some platforms do not support printing 64-bit integers, even
 * though the types are supported. On such platforms %G_GINT64_MODIFIER
 * is not defined.
 *
 * This is not necessarily the correct modifier for printing and scanning
 * `int64_t` values, even though the in-memory representation is the same.
 * Standard C macros like `PRId64` and `SCNd64` should be used for `int64_t`.
 *
 * Since: 2.4
 */

/**
 * G_GINT64_FORMAT:
 *
 * This is the platform dependent conversion specifier for scanning
 * and printing values of type #gint64. See also %G_GINT16_FORMAT.
 *
 * Some platforms do not support scanning and printing 64-bit integers,
 * even though the types are supported. On such platforms %G_GINT64_FORMAT
 * is not defined. Note that scanf() may not support 64-bit integers, even
 * if %G_GINT64_FORMAT is defined. Due to its weak error handling, scanf()
 * is not recommended for parsing anyway; consider using g_ascii_strtoull()
 * instead.
 *
 * This is not necessarily the correct format for printing and scanning
 * `int64_t` values, even though the in-memory representation is the same.
 * Standard C macros like `PRId64` and `SCNd64` should be used for `int64_t`.
 */

/**
 * guint64:
 *
 * An unsigned integer guaranteed to be 64-bits on all platforms,
 * similar to the standard C `uint64_t` type.
 *
 * The `uint64_t` type should be preferred in new code, unless
 * consistency with pre-existing APIs requires use of `guint64`
 * (see #gsize for more details).
 *
 * Values of this type can range from 0 to %G_MAXUINT64
 * (= 18,446,744,073,709,551,615).
 *
 * To print or scan values of this type, use
 * %G_GINT64_MODIFIER and/or %G_GUINT64_FORMAT.
 *
 * Note that on platforms with more than one 64-bit standard integer type,
 * `guint64` and `uint64_t` are not necessarily implemented by the same
 * 64-bit integer type.
 * See #gsize for more details of what this implies.
 */

/**
 * G_MAXUINT64:
 *
 * The maximum value which can be held in a #guint64.
 *
 * This is the same as standard C `UINT64_MAX`, which should be
 * preferred in new code.
 */

/**
 * G_GUINT64_FORMAT:
 *
 * This is the platform dependent conversion specifier for scanning
 * and printing values of type #guint64. See also %G_GINT16_FORMAT.
 *
 * Some platforms do not support scanning and printing 64-bit integers,
 * even though the types are supported. On such platforms %G_GUINT64_FORMAT
 * is not defined.  Note that scanf() may not support 64-bit integers, even
 * if %G_GINT64_FORMAT is defined. Due to its weak error handling, scanf()
 * is not recommended for parsing anyway; consider using g_ascii_strtoull()
 * instead.
 *
 * This is not necessarily the correct modifier for printing and scanning
 * `uint64_t` values, even though the in-memory representation is the same.
 * Standard C macros like `PRIu64` and `SCNu64` should be used for `uint64_t`.
 */

/**
 * G_GINT64_CONSTANT:
 * @val: a literal integer value, e.g. 0x1d636b02300a7aa7
 *
 * This macro is used to insert 64-bit integer literals
 * into the source code.
 *
 * It is similar to the standard C `INT64_C` macro,
 * which should be preferred in new code.
 */

/**
 * G_GUINT64_CONSTANT:
 * @val: a literal integer value, e.g. 0x1d636b02300a7aa7U
 *
 * This macro is used to insert 64-bit unsigned integer
 * literals into the source code.
 *
 * It is similar to the standard C `UINT64_C` macro,
 * which should be preferred in new code.
 *
 * Since: 2.10
 */

/**
 * gfloat:
 *
 * Equivalent to the standard C `float` type.
 *
 * Values of this type can range from `-FLT_MAX` to `FLT_MAX`,
 * or equivalently from -%G_MAXFLOAT to %G_MAXFLOAT.
 */

/**
 * G_MINFLOAT:
 *
 * The minimum positive value which can be held in a #gfloat.
 *
 * If you are interested in the smallest value which can be held
 * in a #gfloat, use -%G_MAXFLOAT.
 *
 * This is the same as standard C `FLT_MIN`, which is available since C99
 * and should be preferred in new code.
 */

/**
 * G_MAXFLOAT:
 *
 * The maximum value which can be held in a #gfloat.
 *
 * This is the same as standard C `FLT_MAX`, which is available since C99
 * and should be preferred in new code.
 */

/**
 * gdouble:
 *
 * Equivalent to the standard C `double` type.
 *
 * Values of this type can range from `-DBL_MAX` to `DBL_MAX`,
 * or equivalently from -%G_MAXDOUBLE to %G_MAXDOUBLE.
 */

/**
 * G_MINDOUBLE:
 *
 * The minimum positive value which can be held in a #gdouble.
 *
 * If you are interested in the smallest value which can be held
 * in a #gdouble, use -%G_MAXDOUBLE.
 *
 * This is the same as standard C `DBL_MIN`, which is available since C99
 * and should be preferred in new code.
 */

/**
 * G_MAXDOUBLE:
 *
 * The maximum value which can be held in a #gdouble.
 *
 * This is the same as standard C `DBL_MAX`, which is available since C99
 * and should be preferred in new code.
 */

/**
 * gsize:
 *
 * An unsigned integer type of the result of the `sizeof` operator,
 * corresponding to the `size_t` type defined in C99.
 *
 * The standard `size_t` type should be preferred in new code, unless
 * consistency with pre-existing APIs requires `gsize`
 * (see below for more details).
 *
 * `gsize` is usually 32 bit wide on a 32-bit platform and 64 bit wide
 * on a 64-bit platform. Values of this type can range from 0 to
 * %G_MAXSIZE.
 *
 * This type is wide enough to hold the size of the largest possible
 * memory allocation, but is not guaranteed to be wide enough to hold
 * the numeric value of a pointer: on platforms that use tagged pointers,
 * such as [CHERI](https://cheri-cpu.org/), pointers can be numerically
 * larger than the size of the address space.
 * If the numeric value of a pointer needs to be stored in an integer
 * without information loss, use the standard C types `intptr_t` or
 * `uintptr_t`, or the similar GLib types #gintptr or #guintptr.
 *
 * To print or scan values of this type, use
 * %G_GSIZE_MODIFIER and/or %G_GSIZE_FORMAT.
 *
 * Note that on platforms where more than one standard integer type is
 * the same size, `size_t` and `gsize` are always the same size but are
 * not necessarily implemented by the same standard integer type.
 * For example, on an ILP32 platform where `int`, `long` and pointers
 * are all 32-bit, `size_t` might be `unsigned long` while `gsize`
 * might be `unsigned int`.
 * This can result in compiler warnings or unexpected C++ name-mangling
 * if the two types are used inconsistently.
 *
 * As a result, changing a type from `gsize` to `size_t` in existing APIs
 * might be an incompatible API or ABI change, especially if C++
 * is involved. The safe option is to leave existing APIs using the same type
 * that they have historically used, and only use the standard C types in
 * new APIs.
 *
 * Similar considerations apply to all the fixed-size types
 * (#gint8, #guint8, #gint16, #guint16, #gint32, #guint32, #gint64,
 * #guint64 and #goffset), as well as #gintptr and #guintptr.
 * Types that are 32 bits or larger are particularly likely to be
 * affected by this.
 */

/**
 * G_MAXSIZE:
 *
 * The maximum value which can be held in a #gsize.
 *
 * This is the same as standard C `SIZE_MAX` (available since C99),
 * which should be preferred in new code.
 *
 * Since: 2.4
 */

/**
 * G_GSIZE_MODIFIER:
 *
 * The platform dependent length modifier for conversion specifiers
 * for scanning and printing values of type #gsize. It
 * is a string literal.
 *
 * Note that this is not necessarily the correct modifier to scan or
 * print a `size_t`, even though the in-memory representation is the
 * same. The Standard C `"z"` modifier should be used for `size_t`,
 * assuming a C99-compliant `printf` implementation is available.
 *
 * Since: 2.6
 */

/**
 * G_GSIZE_FORMAT:
 *
 * This is the platform dependent conversion specifier for scanning
 * and printing values of type #gsize. See also %G_GINT16_FORMAT.
 *
 * Note that this is not necessarily the correct format to scan or
 * print a `size_t`, even though the in-memory representation is the
 * same. The standard C `"zu"` format should be used for `size_t`,
 * assuming a C99-compliant `printf` implementation is available.
 *
 * Since: 2.6
 */

/**
 * gssize:
 *
 * A signed variant of #gsize, corresponding to the
 * `ssize_t` defined in POSIX or the similar `SSIZE_T` in Windows.
 *
 * In new platform-specific code, consider using `ssize_t` or `SSIZE_T`
 * directly.
 *
 * Values of this type can range from %G_MINSSIZE
 * to %G_MAXSSIZE.
 *
 * Note that on platforms where `ssize_t` is implemented, `ssize_t` and
 * `gssize` might be implemented by different standard integer types
 * of the same size. Similarly, on Windows, `SSIZE_T` and `gssize`
 * might be implemented by different standard integer types of the same
 * size. See #gsize for more details.
 *
 * This type is also not guaranteed to be the same as standard C
 * `ptrdiff_t`, although they are the same on many platforms.
 *
 * To print or scan values of this type, use
 * %G_GSSIZE_MODIFIER and/or %G_GSSIZE_FORMAT.
 */

/**
 * G_MINSSIZE:
 *
 * The minimum value which can be held in a #gssize.
 *
 * Since: 2.14
 */

/**
 * G_MAXSSIZE:
 *
 * The maximum value which can be held in a #gssize.
 *
 * Since: 2.14
 */

/**
 * G_GSSIZE_FORMAT:
 *
 * This is the platform dependent conversion specifier for scanning
 * and printing values of type #gssize. See also %G_GINT16_FORMAT.
 *
 * Note that this is not necessarily the correct format to scan or print
 * a POSIX `ssize_t` or a Windows `SSIZE_T`, even though the in-memory
 * representation is the same.
 * On POSIX platforms, the `"zd"` format should be used for `ssize_t`.
 *
 * Since: 2.6
 */

/**
 * G_GSSIZE_MODIFIER:
 *
 * The platform dependent length modifier for conversion specifiers
 * for scanning and printing values of type #gssize. It
 * is a string literal.
 *
 * Note that this is not necessarily the correct modifier to scan or print
 * a POSIX `ssize_t` or a Windows `SSIZE_T`, even though the in-memory
 * representation is the same.
 * On POSIX platforms, the `"z"` modifier should be used for `ssize_t`.
 *
 * Since: 2.6
 */

/**
 * goffset:
 *
 * A signed integer type that is used for file offsets,
 * corresponding to the POSIX type `off_t` as if compiling with
 * `_FILE_OFFSET_BITS` set to 64. #goffset is always 64 bits wide, even on
 * 32-bit architectures, and even if `off_t` is only 32 bits.
 * Values of this type can range from %G_MINOFFSET to
 * %G_MAXOFFSET.
 *
 * To print or scan values of this type, use
 * %G_GOFFSET_MODIFIER and/or %G_GOFFSET_FORMAT.
 *
 * On platforms with more than one 64-bit standard integer type,
 * even if `off_t` is also 64 bits in size, `goffset` and `off_t` are not
 * necessarily implemented by the same 64-bit integer type.
 * See #gsize for more details of what this implies.
 *
 * Since: 2.14
 */

/**
 * G_MINOFFSET:
 *
 * The minimum value which can be held in a #goffset.
 */

/**
 * G_MAXOFFSET:
 *
 * The maximum value which can be held in a #goffset.
 */

/**
 * G_GOFFSET_MODIFIER:
 *
 * The platform dependent length modifier for conversion specifiers
 * for scanning and printing values of type #goffset. It is a string
 * literal. See also %G_GINT64_MODIFIER.
 *
 * This modifier should only be used with #goffset values, and not
 * with `off_t`, which is not necessarily the same type or even the same size.
 *
 * Since: 2.20
 */

/**
 * G_GOFFSET_FORMAT:
 *
 * This is the platform dependent conversion specifier for scanning
 * and printing values of type #goffset. See also %G_GINT64_FORMAT.
 *
 * This format should only be used with #goffset values, and not
 * with `off_t`, which is not necessarily the same type or even the same size.
 *
 * Since: 2.20
 */

/**
 * G_GOFFSET_CONSTANT:
 * @val: a literal integer value, e.g. 0x1d636b02300a7aa7
 *
 * This macro is used to insert #goffset 64-bit integer literals
 * into the source code.
 *
 * See also G_GINT64_CONSTANT().
 *
 * Since: 2.20
 */

/**
 * gintptr:
 *
 * Corresponds to the C99 type intptr_t,
 * a signed integer type that can hold any pointer.
 *
 * The standard `intptr_t` type should be preferred in new code, unless
 * consistency with pre-existing APIs requires `gintptr`.
 * Note that `intptr_t` and `gintptr` might be implemented by different
 * standard integer types of the same size. See #gsize for more details.
 *
 * #gintptr is not guaranteed to be the same type or the same size as #gssize,
 * even though they are the same on many CPU architectures.
 *
 * To print or scan values of this type, use
 * %G_GINTPTR_MODIFIER and/or %G_GINTPTR_FORMAT.
 *
 * Since: 2.18
 */

/**
 * G_GINTPTR_MODIFIER:
 *
 * The platform dependent length modifier for conversion specifiers
 * for scanning and printing values of type #gintptr or #guintptr.
 * It is a string literal.
 *
 * Note that this is not necessarily the correct modifier to scan or
 * print an `intptr_t`, even though the in-memory representation is the
 * same.
 * Standard C macros like `PRIdPTR` and `SCNdPTR` should be used for
 * `intptr_t`.
 *
 * Since: 2.22
 */

/**
 * G_GINTPTR_FORMAT:
 *
 * This is the platform dependent conversion specifier for scanning
 * and printing values of type #gintptr.
 *
 * Note that this is not necessarily the correct format to scan or
 * print an `intptr_t`, even though the in-memory representation is the
 * same.
 * Standard C macros like `PRIdPTR` and `SCNdPTR` should be used for
 * `intptr_t`.
 *
 * Since: 2.22
 */

/**
 * guintptr:
 *
 * Corresponds to the C99 type uintptr_t,
 * an unsigned integer type that can hold any pointer.
 *
 * The standard `uintptr_t` type should be preferred in new code, unless
 * consistency with pre-existing APIs requires `guintptr`.
 * Note that `uintptr_t` and `guintptr` might be implemented by different
 * standard integer types of the same size. See #gsize for more details.
 *
 * #guintptr is not guaranteed to be the same type or the same size as #gsize,
 * even though they are the same on many CPU architectures.
 *
 * To print or scan values of this type, use
 * %G_GINTPTR_MODIFIER and/or %G_GUINTPTR_FORMAT.
 *
 * Since: 2.18
 */

/**
 * G_GUINTPTR_FORMAT:
 *
 * This is the platform dependent conversion specifier
 * for scanning and printing values of type #guintptr.
 *
 * Note that this is not necessarily the correct format to scan or
 * print a `uintptr_t`, even though the in-memory representation is the
 * same.
 * Standard C macros like `PRIuPTR` and `SCNuPTR` should be used for
 * `uintptr_t`.
 *
 * Since: 2.22
 */

/* Type conversion {{{1 */

/**
 * GINT_TO_POINTER:
 * @i: integer to stuff into a pointer
 *
 * Stuffs an integer into a pointer type.
 *
 * Remember, you may not store pointers in integers. This is not portable
 * in any way, shape or form. These macros only allow storing integers in
 * pointers, and only preserve 32 bits of the integer; values outside the
 * range of a 32-bit integer will be mangled.
 */

/**
 * GPOINTER_TO_INT:
 * @p: pointer containing an integer
 *
 * Extracts an integer from a pointer. The integer must have
 * been stored in the pointer with GINT_TO_POINTER().
 *
 * Remember, you may not store pointers in integers. This is not portable
 * in any way, shape or form. These macros only allow storing integers in
 * pointers, and only preserve 32 bits of the integer; values outside the
 * range of a 32-bit integer will be mangled.
 */

/**
 * GUINT_TO_POINTER:
 * @u: unsigned integer to stuff into the pointer
 *
 * Stuffs an unsigned integer into a pointer type.
 */

/**
 * GPOINTER_TO_UINT:
 * @p: pointer to extract an unsigned integer from
 *
 * Extracts an unsigned integer from a pointer. The integer must have
 * been stored in the pointer with GUINT_TO_POINTER().
 */

/**
 * GSIZE_TO_POINTER:
 * @s: #gsize to stuff into the pointer
 *
 * Stuffs a #gsize into a pointer type.
 */

/**
 * GPOINTER_TO_SIZE:
 * @p: pointer to extract a #gsize from
 *
 * Extracts a #gsize from a pointer. The #gsize must have
 * been stored in the pointer with GSIZE_TO_POINTER().
 */
 
/* Byte order {{{1 */

/**
 * G_BYTE_ORDER:
 *
 * The host byte order.
 * This can be either %G_LITTLE_ENDIAN or %G_BIG_ENDIAN (support for
 * %G_PDP_ENDIAN may be added in future.)
 */

/**
 * G_LITTLE_ENDIAN:
 *
 * Specifies one of the possible types of byte order.
 * See %G_BYTE_ORDER.
 */

/**
 * G_BIG_ENDIAN:
 *
 * Specifies one of the possible types of byte order.
 * See %G_BYTE_ORDER.
 */

/**
 * G_PDP_ENDIAN:
 *
 * Specifies one of the possible types of byte order
 * (currently unused). See %G_BYTE_ORDER.
 */

/**
 * g_htonl:
 * @val: a 32-bit integer value in host byte order
 *
 * Converts a 32-bit integer value from host to network byte order.
 *
 * Returns: @val converted to network byte order
 */

/**
 * g_htons:
 * @val: a 16-bit integer value in host byte order
 *
 * Converts a 16-bit integer value from host to network byte order.
 *
 * Returns: @val converted to network byte order
 */

/**
 * g_ntohl:
 * @val: a 32-bit integer value in network byte order
 *
 * Converts a 32-bit integer value from network to host byte order.
 *
 * Returns: @val converted to host byte order.
 */

/**
 * g_ntohs:
 * @val: a 16-bit integer value in network byte order
 *
 * Converts a 16-bit integer value from network to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GINT_FROM_BE:
 * @val: a #gint value in big-endian byte order
 *
 * Converts a #gint value from big-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GINT_FROM_LE:
 * @val: a #gint value in little-endian byte order
 *
 * Converts a #gint value from little-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GINT_TO_BE:
 * @val: a #gint value in host byte order
 *
 * Converts a #gint value from host byte order to big-endian.
 *
 * Returns: @val converted to big-endian byte order
 */

/**
 * GINT_TO_LE:
 * @val: a #gint value in host byte order
 *
 * Converts a #gint value from host byte order to little-endian.
 *
 * Returns: @val converted to little-endian byte order
 */

/**
 * GUINT_FROM_BE:
 * @val: a #guint value in big-endian byte order
 *
 * Converts a #guint value from big-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GUINT_FROM_LE:
 * @val: a #guint value in little-endian byte order
 *
 * Converts a #guint value from little-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GUINT_TO_BE:
 * @val: a #guint value in host byte order
 *
 * Converts a #guint value from host byte order to big-endian.
 *
 * Returns: @val converted to big-endian byte order
 */

/**
 * GUINT_TO_LE:
 * @val: a #guint value in host byte order
 *
 * Converts a #guint value from host byte order to little-endian.
 *
 * Returns: @val converted to little-endian byte order.
 */

/**
 * GLONG_FROM_BE:
 * @val: a #glong value in big-endian byte order
 *
 * Converts a #glong value from big-endian to the host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GLONG_FROM_LE:
 * @val: a #glong value in little-endian byte order
 *
 * Converts a #glong value from little-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GLONG_TO_BE:
 * @val: a #glong value in host byte order
 *
 * Converts a #glong value from host byte order to big-endian.
 *
 * Returns: @val converted to big-endian byte order
 */

/**
 * GLONG_TO_LE:
 * @val: a #glong value in host byte order
 *
 * Converts a #glong value from host byte order to little-endian.
 *
 * Returns: @val converted to little-endian
 */

/**
 * GULONG_FROM_BE:
 * @val: a #gulong value in big-endian byte order
 *
 * Converts a #gulong value from big-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GULONG_FROM_LE:
 * @val: a #gulong value in little-endian byte order
 *
 * Converts a #gulong value from little-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GULONG_TO_BE:
 * @val: a #gulong value in host byte order
 *
 * Converts a #gulong value from host byte order to big-endian.
 *
 * Returns: @val converted to big-endian
 */

/**
 * GULONG_TO_LE:
 * @val: a #gulong value in host byte order
 *
 * Converts a #gulong value from host byte order to little-endian.
 *
 * Returns: @val converted to little-endian
 */

/**
 * GSIZE_FROM_BE:
 * @val: a #gsize value in big-endian byte order
 *
 * Converts a #gsize value from big-endian to the host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GSIZE_FROM_LE:
 * @val: a #gsize value in little-endian byte order
 *
 * Converts a #gsize value from little-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GSIZE_TO_BE:
 * @val: a #gsize value in host byte order
 *
 * Converts a #gsize value from host byte order to big-endian.
 *
 * Returns: @val converted to big-endian byte order
 */

/**
 * GSIZE_TO_LE:
 * @val: a #gsize value in host byte order
 *
 * Converts a #gsize value from host byte order to little-endian.
 *
 * Returns: @val converted to little-endian
 */

/**
 * GSSIZE_FROM_BE:
 * @val: a #gssize value in big-endian byte order
 *
 * Converts a #gssize value from big-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GSSIZE_FROM_LE:
 * @val: a #gssize value in little-endian byte order
 *
 * Converts a #gssize value from little-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GSSIZE_TO_BE:
 * @val: a #gssize value in host byte order
 *
 * Converts a #gssize value from host byte order to big-endian.
 *
 * Returns: @val converted to big-endian
 */

/**
 * GSSIZE_TO_LE:
 * @val: a #gssize value in host byte order
 *
 * Converts a #gssize value from host byte order to little-endian.
 *
 * Returns: @val converted to little-endian
 */

/**
 * GINT16_FROM_BE:
 * @val: a #gint16 value in big-endian byte order
 *
 * Converts a #gint16 value from big-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GINT16_FROM_LE:
 * @val: a #gint16 value in little-endian byte order
 *
 * Converts a #gint16 value from little-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GINT16_TO_BE:
 * @val: a #gint16 value in host byte order
 *
 * Converts a #gint16 value from host byte order to big-endian.
 *
 * Returns: @val converted to big-endian
 */

/**
 * GINT16_TO_LE:
 * @val: a #gint16 value in host byte order
 *
 * Converts a #gint16 value from host byte order to little-endian.
 *
 * Returns: @val converted to little-endian
 */

/**
 * GUINT16_FROM_BE:
 * @val: a #guint16 value in big-endian byte order
 *
 * Converts a #guint16 value from big-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GUINT16_FROM_LE:
 * @val: a #guint16 value in little-endian byte order
 *
 * Converts a #guint16 value from little-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GUINT16_TO_BE:
 * @val: a #guint16 value in host byte order
 *
 * Converts a #guint16 value from host byte order to big-endian.
 *
 * Returns: @val converted to big-endian
 */

/**
 * GUINT16_TO_LE:
 * @val: a #guint16 value in host byte order
 *
 * Converts a #guint16 value from host byte order to little-endian.
 *
 * Returns: @val converted to little-endian
 */

/**
 * GINT32_FROM_BE:
 * @val: a #gint32 value in big-endian byte order
 *
 * Converts a #gint32 value from big-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GINT32_FROM_LE:
 * @val: a #gint32 value in little-endian byte order
 *
 * Converts a #gint32 value from little-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GINT32_TO_BE:
 * @val: a #gint32 value in host byte order
 *
 * Converts a #gint32 value from host byte order to big-endian.
 *
 * Returns: @val converted to big-endian
 */

/**
 * GINT32_TO_LE:
 * @val: a #gint32 value in host byte order
 *
 * Converts a #gint32 value from host byte order to little-endian.
 *
 * Returns: @val converted to little-endian
 */

/**
 * GUINT32_FROM_BE:
 * @val: a #guint32 value in big-endian byte order
 *
 * Converts a #guint32 value from big-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GUINT32_FROM_LE:
 * @val: a #guint32 value in little-endian byte order
 *
 * Converts a #guint32 value from little-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GUINT32_TO_BE:
 * @val: a #guint32 value in host byte order
 *
 * Converts a #guint32 value from host byte order to big-endian.
 *
 * Returns: @val converted to big-endian
 */

/**
 * GUINT32_TO_LE:
 * @val: a #guint32 value in host byte order
 *
 * Converts a #guint32 value from host byte order to little-endian.
 *
 * Returns: @val converted to little-endian
 */

/**
 * GINT64_FROM_BE:
 * @val: a #gint64 value in big-endian byte order
 *
 * Converts a #gint64 value from big-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GINT64_FROM_LE:
 * @val: a #gint64 value in little-endian byte order
 *
 * Converts a #gint64 value from little-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GINT64_TO_BE:
 * @val: a #gint64 value in host byte order
 *
 * Converts a #gint64 value from host byte order to big-endian.
 *
 * Returns: @val converted to big-endian
 */

/**
 * GINT64_TO_LE:
 * @val: a #gint64 value in host byte order
 *
 * Converts a #gint64 value from host byte order to little-endian.
 *
 * Returns: @val converted to little-endian
 */

/**
 * GUINT64_FROM_BE:
 * @val: a #guint64 value in big-endian byte order
 *
 * Converts a #guint64 value from big-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GUINT64_FROM_LE:
 * @val: a #guint64 value in little-endian byte order
 *
 * Converts a #guint64 value from little-endian to host byte order.
 *
 * Returns: @val converted to host byte order
 */

/**
 * GUINT64_TO_BE:
 * @val: a #guint64 value in host byte order
 *
 * Converts a #guint64 value from host byte order to big-endian.
 *
 * Returns: @val converted to big-endian
 */

/**
 * GUINT64_TO_LE:
 * @val: a #guint64 value in host byte order
 *
 * Converts a #guint64 value from host byte order to little-endian.
 *
 * Returns: @val converted to little-endian
 */

/**
 * GUINT16_SWAP_BE_PDP:
 * @val: a #guint16 value in big-endian or pdp-endian byte order
 *
 * Converts a #guint16 value between big-endian and pdp-endian byte order.
 * The conversion is symmetric so it can be used both ways.
 *
 * Returns: @val converted to the opposite byte order
 */

/**
 * GUINT16_SWAP_LE_BE:
 * @val: a #guint16 value in little-endian or big-endian byte order
 *
 * Converts a #guint16 value between little-endian and big-endian byte order.
 * The conversion is symmetric so it can be used both ways.
 *
 * Returns: @val converted to the opposite byte order
 */

/**
 * GUINT16_SWAP_LE_PDP:
 * @val: a #guint16 value in little-endian or pdp-endian byte order
 *
 * Converts a #guint16 value between little-endian and pdp-endian byte order.
 * The conversion is symmetric so it can be used both ways.
 *
 * Returns: @val converted to the opposite byte order
 */

/**
 * GUINT32_SWAP_BE_PDP:
 * @val: a #guint32 value in big-endian or pdp-endian byte order
 *
 * Converts a #guint32 value between big-endian and pdp-endian byte order.
 * The conversion is symmetric so it can be used both ways.
 *
 * Returns: @val converted to the opposite byte order
 */

/**
 * GUINT32_SWAP_LE_BE:
 * @val: a #guint32 value in little-endian or big-endian byte order
 *
 * Converts a #guint32 value between little-endian and big-endian byte order.
 * The conversion is symmetric so it can be used both ways.
 *
 * Returns: @val converted to the opposite byte order
 */

/**
 * GUINT32_SWAP_LE_PDP:
 * @val: a #guint32 value in little-endian or pdp-endian byte order
 *
 * Converts a #guint32 value between little-endian and pdp-endian byte order.
 * The conversion is symmetric so it can be used both ways.
 *
 * Returns: @val converted to the opposite byte order
 */

/**
 * GUINT64_SWAP_LE_BE:
 * @val: a #guint64 value in little-endian or big-endian byte order
 *
 * Converts a #guint64 value between little-endian and big-endian byte order.
 * The conversion is symmetric so it can be used both ways.
 *
 * Returns: @val converted to the opposite byte order
 */
 
/* Bounds-checked integer arithmetic {{{1 */
/**
 * SECTION:checkedmath
 * @title: Bounds-checking integer arithmetic
 * @short_description: a set of helpers for performing checked integer arithmetic
 *
 * GLib offers a set of macros for doing additions and multiplications
 * of unsigned integers, with checks for overflows.
 *
 * The helpers all have three arguments.  A pointer to the destination
 * is always the first argument and the operands to the operation are
 * the other two.
 *
 * Following standard GLib convention, the helpers return %TRUE in case
 * of success (ie: no overflow).
 *
 * The helpers may be macros, normal functions or inlines.  They may be
 * implemented with inline assembly or compiler intrinsics where
 * available.
 *
 * Since: 2.48
 */

/**
 * g_uint_checked_add
 * @dest: a pointer to the #guint destination
 * @a: the #guint left operand
 * @b: the #guint right operand
 *
 * Performs a checked addition of @a and @b, storing the result in
 * @dest.
 *
 * If the operation is successful, %TRUE is returned.  If the operation
 * overflows then the state of @dest is undefined and %FALSE is
 * returned.
 *
 * Returns: %TRUE if there was no overflow
 * Since: 2.48
 */

/**
 * g_uint_checked_mul
 * @dest: a pointer to the #guint destination
 * @a: the #guint left operand
 * @b: the #guint right operand
 *
 * Performs a checked multiplication of @a and @b, storing the result in
 * @dest.
 *
 * If the operation is successful, %TRUE is returned.  If the operation
 * overflows then the state of @dest is undefined and %FALSE is
 * returned.
 *
 * Returns: %TRUE if there was no overflow
 * Since: 2.48
 */

/**
 * g_uint64_checked_add
 * @dest: a pointer to the #guint64 destination
 * @a: the #guint64 left operand
 * @b: the #guint64 right operand
 *
 * Performs a checked addition of @a and @b, storing the result in
 * @dest.
 *
 * If the operation is successful, %TRUE is returned.  If the operation
 * overflows then the state of @dest is undefined and %FALSE is
 * returned.
 *
 * Returns: %TRUE if there was no overflow
 * Since: 2.48
 */

/**
 * g_uint64_checked_mul
 * @dest: a pointer to the #guint64 destination
 * @a: the #guint64 left operand
 * @b: the #guint64 right operand
 *
 * Performs a checked multiplication of @a and @b, storing the result in
 * @dest.
 *
 * If the operation is successful, %TRUE is returned.  If the operation
 * overflows then the state of @dest is undefined and %FALSE is
 * returned.
 *
 * Returns: %TRUE if there was no overflow
 * Since: 2.48
 */

/**
 * g_size_checked_add
 * @dest: a pointer to the #gsize destination
 * @a: the #gsize left operand
 * @b: the #gsize right operand
 *
 * Performs a checked addition of @a and @b, storing the result in
 * @dest.
 *
 * If the operation is successful, %TRUE is returned.  If the operation
 * overflows then the state of @dest is undefined and %FALSE is
 * returned.
 *
 * Returns: %TRUE if there was no overflow
 * Since: 2.48
 */

/**
 * g_size_checked_mul
 * @dest: a pointer to the #gsize destination
 * @a: the #gsize left operand
 * @b: the #gsize right operand
 *
 * Performs a checked multiplication of @a and @b, storing the result in
 * @dest.
 *
 * If the operation is successful, %TRUE is returned.  If the operation
 * overflows then the state of @dest is undefined and %FALSE is
 * returned.
 *
 * Returns: %TRUE if there was no overflow
 * Since: 2.48
 */
/* Numerical Definitions {{{1 */

/**
 * SECTION:numerical
 * @title: Numerical Definitions
 * @short_description: mathematical constants, and floating point decomposition
 *
 * GLib offers mathematical constants such as %G_PI for the value of pi;
 * many platforms have these in the C library, but some don't, the GLib
 * versions always exist.
 *
 * The #GFloatIEEE754 and #GDoubleIEEE754 unions are used to access the
 * sign, mantissa and exponent of IEEE floats and doubles. These unions are
 * defined as appropriate for a given platform. IEEE floats and doubles are
 * supported (used for storage) by at least Intel, PPC and Sparc. See
 * [IEEE 754-2008](http://en.wikipedia.org/wiki/IEEE_float)
 * for more information about IEEE number formats.
 */

/**
 * G_IEEE754_FLOAT_BIAS:
 *
 * The bias by which exponents in single-precision floats are offset.
 */

/**
 * G_IEEE754_DOUBLE_BIAS:
 *
 * The bias by which exponents in double-precision floats are offset.
 */

/**
 * GFloatIEEE754:
 * @v_float: the double value
 *
 * The #GFloatIEEE754 and #GDoubleIEEE754 unions are used to access the sign,
 * mantissa and exponent of IEEE floats and doubles. These unions are defined
 * as appropriate for a given platform. IEEE floats and doubles are supported
 * (used for storage) by at least Intel, PPC and Sparc.
 */

/**
 * GDoubleIEEE754:
 * @v_double: the double value
 *
 * The #GFloatIEEE754 and #GDoubleIEEE754 unions are used to access the sign,
 * mantissa and exponent of IEEE floats and doubles. These unions are defined
 * as appropriate for a given platform. IEEE floats and doubles are supported
 * (used for storage) by at least Intel, PPC and Sparc.
 */

/**
 * G_E:
 *
 * The base of natural logarithms.
 */

/**
 * G_LN2:
 *
 * The natural logarithm of 2.
 */

/**
 * G_LN10:
 *
 * The natural logarithm of 10.
 */

/**
 * G_PI:
 *
 * The value of pi (ratio of circle's circumference to its diameter).
 */

/**
 * G_PI_2:
 *
 * Pi divided by 2.
 */

/**
 * G_PI_4:
 *
 * Pi divided by 4.
 */

/**
 * G_SQRT2:
 *
 * The square root of two.
 */

/**
 * G_LOG_2_BASE_10:
 *
 * Multiplying the base 2 exponent by this number yields the base 10 exponent.
 */

/* Macros {{{1 */

/**
 * G_OS_WIN32:
 *
 * This macro is defined only on Windows. So you can bracket
 * Windows-specific code in "\#ifdef G_OS_WIN32".
 */

/**
 * G_OS_UNIX:
 *
 * This macro is defined only on UNIX. So you can bracket
 * UNIX-specific code in "\#ifdef G_OS_UNIX".
 *
 * To detect whether to compile features that require a specific kernel
 * or operating system, check for the appropriate OS-specific predefined
 * macros instead, for example:
 *
 * - Linux kernel (any libc, including glibc, musl or Android): `\#ifdef __linux__`
 * - Linux kernel and GNU user-space: `\#if defined(__linux__) && defined(__GLIBC__)`
 * - FreeBSD kernel (any libc, including glibc): `\#ifdef __FreeBSD_kernel__`
 * - FreeBSD kernel and user-space: `\#ifdef __FreeBSD__`
 * - Apple operating systems (macOS, iOS, tvOS), regardless of whether
 *   Cocoa/Carbon toolkits are available: `\#ifdef __APPLE__`
 *
 * See <https://sourceforge.net/p/predef/wiki/OperatingSystems/> for more.
 */

/**
 * G_DIR_SEPARATOR:
 *
 * The directory separator character.
 * This is '/' on UNIX machines and '\' under Windows.
 */

/**
 * G_DIR_SEPARATOR_S:
 *
 * The directory separator as a string.
 * This is "/" on UNIX machines and "\" under Windows.
 */

/**
 * G_IS_DIR_SEPARATOR:
 * @c: a character
 *
 * Checks whether a character is a directory
 * separator. It returns %TRUE for '/' on UNIX
 * machines and for '\' or '/' under Windows.
 *
 * Since: 2.6
 */

/**
 * G_SEARCHPATH_SEPARATOR:
 *
 * The search path separator character.
 * This is ':' on UNIX machines and ';' under Windows.
 */

/**
 * G_SEARCHPATH_SEPARATOR_S:
 *
 * The search path separator as a string.
 * This is ":" on UNIX machines and ";" under Windows.
 */

/**
 * TRUE:
 *
 * Defines the %TRUE value for the #gboolean type.
 */

/**
 * FALSE:
 *
 * Defines the %FALSE value for the #gboolean type.
 */

/**
 * NULL:
 *
 * Defines the standard %NULL pointer.
 */

/**
 * MIN:
 * @a: a numeric value
 * @b: a numeric value
 *
 * Calculates the minimum of @a and @b.
 *
 * Returns: the minimum of @a and @b.
 */

/**
 * MAX:
 * @a: a numeric value
 * @b: a numeric value
 *
 * Calculates the maximum of @a and @b.
 *
 * Returns: the maximum of @a and @b.
 */

/**
 * ABS:
 * @a: a numeric value
 *
 * Calculates the absolute value of @a.
 * The absolute value is simply the number with any negative sign taken away.
 *
 * For example,
 * - ABS(-10) is 10.
 * - ABS(10) is also 10.
 *
 * Returns: the absolute value of @a.
 */

/**
 * CLAMP:
 * @x: the value to clamp
 * @low: the minimum value allowed
 * @high: the maximum value allowed
 *
 * Ensures that @x is between the limits set by @low and @high. If @low is
 * greater than @high the result is undefined.
 *
 * For example,
 * - CLAMP(5, 10, 15) is 10.
 * - CLAMP(15, 5, 10) is 10.
 * - CLAMP(20, 15, 25) is 20.
 *
 * Returns: the value of @x clamped to the range between @low and @high
 */

/**
 * G_APPROX_VALUE:
 * @a: a numeric value
 * @b: a numeric value
 * @epsilon: a numeric value that expresses the tolerance between @a and @b
 *
 * Evaluates to a truth value if the absolute difference between @a and @b is
 * smaller than @epsilon, and to a false value otherwise.
 *
 * For example,
 * - `G_APPROX_VALUE (5, 6, 2)` evaluates to true
 * - `G_APPROX_VALUE (3.14, 3.15, 0.001)` evaluates to false
 * - `G_APPROX_VALUE (n, 0.f, FLT_EPSILON)` evaluates to true if `n` is within
 *   the single precision floating point epsilon from zero
 *
 * Returns: %TRUE if the two values are within the desired range
 *
 * Since: 2.58
 */

/**
 * G_STRUCT_MEMBER:
 * @member_type: the type of the struct field
 * @struct_p: a pointer to a struct
 * @struct_offset: the offset of the field from the start of the struct,
 *     in bytes
 *
 * Returns a member of a structure at a given offset, using the given type.
 *
 * Returns: the struct member
 */

/**
 * G_STRUCT_MEMBER_P:
 * @struct_p: a pointer to a struct
 * @struct_offset: the offset from the start of the struct, in bytes
 *
 * Returns an untyped pointer to a given offset of a struct.
 *
 * Returns: an untyped pointer to @struct_p plus @struct_offset bytes
 */

/**
 * G_STRUCT_OFFSET:
 * @struct_type: a structure type, e.g. #GtkWidget
 * @member: a field in the structure, e.g. @window
 *
 * Returns the offset, in bytes, of a member of a struct.
 *
 * Consider using standard C `offsetof()`, available since at least C89
 * and C++98, in new code (but note that `offsetof()` returns a `size_t`
 * rather than a `long`).
 *
 * Returns: the offset of @member from the start of @struct_type,
 *  as a value of type #glong.
 */

/**
 * G_N_ELEMENTS:
 * @arr: the array
 *
 * Determines the number of elements in an array. The array must be
 * declared so the compiler knows its size at compile-time; this
 * macro will not work on an array allocated on the heap, only static
 * arrays or arrays on the stack.
 */

/* Miscellaneous Macros {{{1 */

/**
 * G_STMT_START:
 *
 * Used within multi-statement macros so that they can be used in places
 * where only one statement is expected by the compiler.
 */

/**
 * G_STMT_END:
 *
 * Used within multi-statement macros so that they can be used in places
 * where only one statement is expected by the compiler.
 */

/**
 * G_BEGIN_DECLS:
 *
 * Used (along with %G_END_DECLS) to bracket header files. If the
 * compiler in use is a C++ compiler, adds extern "C"
 * around the header.
 */

/**
 * G_END_DECLS:
 *
 * Used (along with %G_BEGIN_DECLS) to bracket header files. If the
 * compiler in use is a C++ compiler, adds extern "C"
 * around the header.
 */

/**
 * G_VA_COPY:
 * @ap1: the va_list variable to place a copy of @ap2 in
 * @ap2: a va_list
 *
 * Portable way to copy va_list variables.
 *
 * In order to use this function, you must include string.h yourself,
 * because this macro may use memmove() and GLib does not include
 * string.h for you.
 *
 * Each invocation of `G_VA_COPY (ap1, ap2)` must be matched with a
 * corresponding `va_end (ap1)` call in the same function.
 *
 * This is equivalent to standard C `va_copy()`, available since C99
 * and C++11, which should be preferred in new code.
 */

/**
 * G_STRINGIFY:
 * @macro_or_string: a macro or a string
 *
 * Accepts a macro or a string and converts it into a string after
 * preprocessor argument expansion. For example, the following code:
 *
 * |[<!-- language="C" -->
 * #define AGE 27
 * const gchar *greeting = G_STRINGIFY (AGE) " today!";
 * ]|
 *
 * is transformed by the preprocessor into (code equivalent to):
 *
 * |[<!-- language="C" -->
 * const gchar *greeting = "27 today!";
 * ]|
 */

/**
 * G_PASTE:
 * @identifier1: an identifier
 * @identifier2: an identifier
 *
 * Yields a new preprocessor pasted identifier
 * @identifier1identifier2 from its expanded
 * arguments @identifier1 and @identifier2. For example,
 * the following code:
 * |[<!-- language="C" -->
 * #define GET(traveller,method) G_PASTE(traveller_get_, method) (traveller)
 * const gchar *name = GET (traveller, name);
 * const gchar *quest = GET (traveller, quest);
 * GdkColor *favourite = GET (traveller, favourite_colour);
 * ]|
 *
 * is transformed by the preprocessor into:
 * |[<!-- language="C" -->
 * const gchar *name = traveller_get_name (traveller);
 * const gchar *quest = traveller_get_quest (traveller);
 * GdkColor *favourite = traveller_get_favourite_colour (traveller);
 * ]|
 *
 * Since: 2.20
 */

/**
 * G_STATIC_ASSERT:
 * @expr: a constant expression
 *
 * The G_STATIC_ASSERT() macro lets the programmer check
 * a condition at compile time, the condition needs to
 * be compile time computable. The macro can be used in
 * any place where a typedef is valid.
 *
 * A typedef is generally allowed in exactly the same places that
 * a variable declaration is allowed. For this reason, you should
 * not use G_STATIC_ASSERT() in the middle of blocks of code.
 *
 * The macro should only be used once per source code line.
 *
 * Since: 2.20
 */

/**
 * G_STATIC_ASSERT_EXPR:
 * @expr: a constant expression
 *
 * The G_STATIC_ASSERT_EXPR() macro lets the programmer check
 * a condition at compile time. The condition needs to be
 * compile time computable.
 *
 * Unlike G_STATIC_ASSERT(), this macro evaluates to an expression
 * and, as such, can be used in the middle of other expressions.
 * Its value should be ignored. This can be accomplished by placing
 * it as the first argument of a comma expression.
 *
 * |[<!-- language="C" -->
 * #define ADD_ONE_TO_INT(x) \
 *   (G_STATIC_ASSERT_EXPR(sizeof (x) == sizeof (int)), ((x) + 1))
 * ]|
 *
 * Since: 2.30
 */

/**
 * G_GNUC_EXTENSION:
 *
 * Expands to __extension__ when gcc is used as the compiler. This simply
 * tells gcc not to warn about the following non-standard code when compiling
 * with the `-pedantic` option.
 */

/**
 * G_GNUC_CHECK_VERSION:
 * @major: major version to check against
 * @minor: minor version to check against
 *
 * Expands to a check for a compiler with __GNUC__ defined and a version
 * greater than or equal to the major and minor numbers provided. For example,
 * the following would only match on compilers such as GCC 4.8 or newer.
 *
 * |[<!-- language="C" -->
 * #if G_GNUC_CHECK_VERSION(4, 8)
 * #endif
 * ]|
 *
 * Since: 2.42
 */

/**
 * G_GNUC_BEGIN_IGNORE_DEPRECATIONS:
 *
 * Tells gcc (if it is a new enough version) to temporarily stop emitting
 * warnings when functions marked with %G_GNUC_DEPRECATED or
 * %G_GNUC_DEPRECATED_FOR are called. This is useful for when you have
 * one deprecated function calling another one, or when you still have
 * regression tests for deprecated functions.
 *
 * Use %G_GNUC_END_IGNORE_DEPRECATIONS to begin warning again. (If you
 * are not compiling with `-Wdeprecated-declarations` then neither macro
 * has any effect.)
 *
 * This macro can be used either inside or outside of a function body,
 * but must appear on a line by itself. Both this macro and the corresponding
 * %G_GNUC_END_IGNORE_DEPRECATIONS are considered statements, so they
 * should not be used around branching or loop conditions; for instance,
 * this use is invalid:
 *
 * |[<!-- language="C" -->
 *   G_GNUC_BEGIN_IGNORE_DEPRECATIONS
 *   if (check == some_deprecated_function ())
 *   G_GNUC_END_IGNORE_DEPRECATIONS
 *     {
 *       do_something ();
 *     }
 * ]|
 *
 * and you should move the deprecated section outside the condition
 *
 * |[<!-- language="C" -->
 *
 *   // Solution A
 *   some_data_t *res;
 *
 *   G_GNUC_BEGIN_IGNORE_DEPRECATIONS
 *   res = some_deprecated_function ();
 *   G_GNUC_END_IGNORE_DEPRECATIONS
 *
 *   if (check == res)
 *     {
 *       do_something ();
 *     }
 *
 *   // Solution B
 *   G_GNUC_BEGIN_IGNORE_DEPRECATIONS
 *   if (check == some_deprecated_function ())
 *     {
 *       do_something ();
 *     }
 *   G_GNUC_END_IGNORE_DEPRECATIONS
 * ]|
 *
 * |[<!-- language="C" -->
 * static void
 * test_deprecated_function (void)
 * {
 *   G_GNUC_BEGIN_IGNORE_DEPRECATIONS
 *   g_assert_cmpint (my_mistake (), ==, 42);
 *   G_GNUC_END_IGNORE_DEPRECATIONS
 * }
 * ]|
 *
 * Since: 2.32
 */

/**
 * G_GNUC_END_IGNORE_DEPRECATIONS:
 *
 * Undoes the effect of %G_GNUC_BEGIN_IGNORE_DEPRECATIONS, telling
 * gcc to begin outputting warnings again (assuming those warnings
 * had been enabled to begin with).
 *
 * This macro can be used either inside or outside of a function body,
 * but must appear on a line by itself.
 *
 * Since: 2.32
 */

/**
 * G_DEPRECATED:
 *
 * This macro is similar to %G_GNUC_DEPRECATED, and can be used to mark
 * functions declarations as deprecated. Unlike %G_GNUC_DEPRECATED, it is
 * meant to be portable across different compilers and must be placed
 * before the function declaration.
 *
 * |[<!-- language="C" -->
 * G_DEPRECATED
 * int my_mistake (void);
 * ]|
 *
 * Since: 2.32
 */

/**
 * G_DEPRECATED_FOR:
 * @f: the name of the function that this function was deprecated for
 *
 * This macro is similar to %G_GNUC_DEPRECATED_FOR, and can be used to mark
 * functions declarations as deprecated. Unlike %G_GNUC_DEPRECATED_FOR, it
 * is meant to be portable across different compilers and must be placed
 * before the function declaration.
 *
 * |[<!-- language="C" -->
 * G_DEPRECATED_FOR(my_replacement)
 * int my_mistake (void);
 * ]|
 *
 * Since: 2.32
 */

/**
 * G_UNAVAILABLE:
 * @maj: the major version that introduced the symbol
 * @min: the minor version that introduced the symbol
 *
 * This macro can be used to mark a function declaration as unavailable.
 * It must be placed before the function declaration. Use of a function
 * that has been annotated with this macros will produce a compiler warning.
 *
 * Since: 2.32
 */

/**
 * GLIB_DISABLE_DEPRECATION_WARNINGS:
 *
 * A macro that should be defined before including the glib.h header.
 * If it is defined, no compiler warnings will be produced for uses
 * of deprecated GLib APIs.
 */

/**
 * G_GNUC_INTERNAL:
 *
 * This attribute can be used for marking library functions as being used
 * internally to the library only, which may allow the compiler to handle
 * function calls more efficiently. Note that static functions do not need
 * to be marked as internal in this way. See the GNU C documentation for
 * details.
 *
 * When using a compiler that supports the GNU C hidden visibility attribute,
 * this macro expands to __attribute__((visibility("hidden"))).
 * When using the Sun Studio compiler, it expands to __hidden.
 *
 * Note that for portability, the attribute should be placed before the
 * function declaration. While GCC allows the macro after the declaration,
 * Sun Studio does not.
 *
 * |[<!-- language="C" -->
 * G_GNUC_INTERNAL
 * void _g_log_fallback_handler (const gchar    *log_domain,
 *                               GLogLevelFlags  log_level,
 *                               const gchar    *message,
 *                               gpointer        unused_data);
 * ]|
 *
 * Since: 2.6
 */

/**
 * G_C_STD_VERSION:
 *
 * The C standard version the code is compiling against, it's normally
 * defined with the same value of `__STDC_VERSION__` for C standard
 * compatible compilers, while it uses the lowest standard version
 * in pure MSVC, given that in such compiler the definition depends on
 * a compilation flag.
 *
 * This is granted to be undefined when compiling with a C++ compiler.
 *
 * See also: %G_C_STD_CHECK_VERSION and %G_CXX_STD_VERSION
 *
 * Since: 2.76
 */

/**
 * G_C_STD_CHECK_VERSION:
 * @version: The C version to be checked for compatibility
 *
 * Macro to check if the current compiler supports a specified @version
 * of the C standard. Such value must be numeric and can be provided both
 * in the short form for the well-known versions (e.g. `90`, `99`...) or in
 * the complete form otherwise (e.g. `199000L`, `199901L`, `205503L`...).
 *
 * When a C++ compiler is used, the macro is defined and returns always %FALSE.
 *
 * This value is compared against %G_C_STD_VERSION.
 *
 * |[<!-- language="C" -->
 * #if G_C_STD_CHECK_VERSION(17)
 * #endif
 * ]|
 *
 * See also: %G_CXX_STD_CHECK_VERSION
 *
 * Returns: %TRUE if @version is supported by the compiler, %FALSE otherwise
 *
 * Since: 2.76
 */

/**
 * G_CXX_STD_VERSION:
 *
 * The C++ standard version the code is compiling against, it's defined
 * with the same value of `__cplusplus` for C++ standard compatible
 * compilers, while it uses `_MSVC_LANG` in MSVC, given that the
 * standard definition depends on a compilation flag in such compiler.
 *
 * This is granted to be undefined when not compiling with a C++ compiler.
 *
 * See also: %G_CXX_STD_CHECK_VERSION and %G_C_STD_VERSION
 *
 * Since: 2.76
 */

/**
 * G_CXX_STD_CHECK_VERSION:
 * @version: The C++ version to be checked for compatibility
 *
 * Macro to check if the current compiler supports a specified @version
 * of the C++ standard. Such value must be numeric and can be provided both
 * in the short form for the well-known versions (e.g. `11`, `17`...) or in
 * the complete form otherwise (e.g. `201103L`, `201703L`, `205503L`...).
 *
 * When a C compiler is used, the macro is defined and returns always %FALSE.
 *
 * This value is compared against %G_CXX_STD_VERSION.
 *
 * |[<!-- language="C" -->
 * #if G_CXX_STD_CHECK_VERSION(20)
 * #endif
 * ]|
 *
 * See also: %G_C_STD_CHECK_VERSION
 *
 * Returns: %TRUE if @version is supported by the compiler, %FALSE otherwise
 *
 * Since: 2.76
 */

/**
 * G_LIKELY:
 * @expr: the expression
 *
 * Hints the compiler that the expression is likely to evaluate to
 * a true value. The compiler may use this information for optimizations.
 *
 * |[<!-- language="C" -->
 * if (G_LIKELY (random () != 1))
 *   g_print ("not one");
 * ]|
 *
 * Returns: the value of @expr
 *
 * Since: 2.2
 */

/**
 * G_UNLIKELY:
 * @expr: the expression
 *
 * Hints the compiler that the expression is unlikely to evaluate to
 * a true value. The compiler may use this information for optimizations.
 *
 * |[<!-- language="C" -->
 * if (G_UNLIKELY (random () == 1))
 *   g_print ("a random one");
 * ]|
 *
 * Returns: the value of @expr
 *
 * Since: 2.2
 */

/**
 * G_STRLOC:
 *
 * Expands to a string identifying the current code position.
 */

/**
 * G_STRFUNC:
 *
 * Expands to a string identifying the current function.
 *
 * Since: 2.4
 */

/**
 * G_HAVE_GNUC_VISIBILITY:
 *
 * Defined to 1 if gcc-style visibility handling is supported.
 */

/* g_auto(), g_autoptr() and helpers {{{1 */

/**
 * g_auto:
 * @TypeName: a supported variable type
 *
 * Helper to declare a variable with automatic cleanup.
 *
 * The variable is cleaned up in a way appropriate to its type when the
 * variable goes out of scope.  The type must support this.
 * The way to clean up the type must have been defined using one of the macros
 * G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC() or G_DEFINE_AUTO_CLEANUP_FREE_FUNC().
 *
 * This feature is only supported on GCC and clang.  This macro is not
 * defined on other compilers and should not be used in programs that
 * are intended to be portable to those compilers.
 *
 * This is meant to be used with stack-allocated structures and
 * non-pointer types.  For the (more commonly used) pointer version, see
 * g_autoptr().
 *
 * This macro can be used to avoid having to do explicit cleanups of
 * local variables when exiting functions.  It often vastly simplifies
 * handling of error conditions, removing the need for various tricks
 * such as `goto out` or repeating of cleanup code.  It is also helpful
 * for non-error cases.
 *
 * Consider the following example:
 *
 * |[
 * GVariant *
 * my_func(void)
 * {
 *   g_auto(GQueue) queue = G_QUEUE_INIT;
 *   g_auto(GVariantBuilder) builder;
 *   g_auto(GStrv) strv;
 *
 *   g_variant_builder_init (&builder, G_VARIANT_TYPE_VARDICT);
 *   strv = g_strsplit("a:b:c", ":", -1);
 *
 *   ...
 *
 *   if (error_condition)
 *     return NULL;
 *
 *   ...
 *
 *   return g_variant_builder_end (&builder);
 * }
 * ]|
 *
 * You must initialize the variable in some way — either by use of an
 * initialiser or by ensuring that an `_init` function will be called on
 * it unconditionally before it goes out of scope.
 *
 * Since: 2.44
 */

/**
 * g_autoptr:
 * @TypeName: a supported variable type
 *
 * Helper to declare a pointer variable with automatic cleanup.
 *
 * The variable is cleaned up in a way appropriate to its type when the
 * variable goes out of scope.  The type must support this.
 * The way to clean up the type must have been defined using the macro
 * G_DEFINE_AUTOPTR_CLEANUP_FUNC().
 *
 * This feature is only supported on GCC and clang.  This macro is not
 * defined on other compilers and should not be used in programs that
 * are intended to be portable to those compilers.
 *
 * This is meant to be used to declare pointers to types with cleanup
 * functions.  The type of the variable is a pointer to @TypeName.  You
 * must not add your own `*`.
 *
 * This macro can be used to avoid having to do explicit cleanups of
 * local variables when exiting functions.  It often vastly simplifies
 * handling of error conditions, removing the need for various tricks
 * such as `goto out` or repeating of cleanup code.  It is also helpful
 * for non-error cases.
 *
 * Consider the following example:
 *
 * |[
 * gboolean
 * check_exists(GVariant *dict)
 * {
 *   g_autoptr(GVariant) dirname, basename = NULL;
 *   g_autofree gchar *path = NULL;
 *
 *   dirname = g_variant_lookup_value (dict, "dirname", G_VARIANT_TYPE_STRING);
 *
 *   if (dirname == NULL)
 *     return FALSE;
 *
 *   basename = g_variant_lookup_value (dict, "basename", G_VARIANT_TYPE_STRING);
 *
 *   if (basename == NULL)
 *     return FALSE;
 *
 *   path = g_build_filename (g_variant_get_string (dirname, NULL),
 *                            g_variant_get_string (basename, NULL),
 *                            NULL);
 *
 *   return g_access (path, R_OK) == 0;
 * }
 * ]|
 *
 * You must initialise the variable in some way — either by use of an
 * initialiser or by ensuring that it is assigned to unconditionally
 * before it goes out of scope.
 *
 * See also g_auto(), g_autofree() and g_steal_pointer().
 *
 * Since: 2.44
 */

/**
 * g_autofree:
 *
 * Macro to add an attribute to pointer variable to ensure automatic
 * cleanup using g_free().
 *
 * This macro differs from g_autoptr() in that it is an attribute supplied
 * before the type name, rather than wrapping the type definition.  Instead
 * of using a type-specific lookup, this macro always calls g_free() directly.
 *
 * This means it's useful for any type that is returned from
 * g_malloc().
 *
 * Otherwise, this macro has similar constraints as g_autoptr(): only
 * supported on GCC and clang, the variable must be initialized, etc.
 *
 * |[
 * gboolean
 * operate_on_malloc_buf (void)
 * {
 *   g_autofree guint8* membuf = NULL;
 *
 *   membuf = g_malloc (8192);
 *
 *   // Some computation on membuf
 *
 *   // membuf will be automatically freed here
 *   return TRUE;
 * }
 * ]|
 *
 * Since: 2.44
 */

/**
 * g_autolist:
 * @TypeName: a supported variable type
 *
 * Helper to declare a list variable with automatic deep cleanup.
 *
 * The list is deeply freed, in a way appropriate to the specified type, when the
 * variable goes out of scope.  The type must support this.
 *
 * This feature is only supported on GCC and clang.  This macro is not
 * defined on other compilers and should not be used in programs that
 * are intended to be portable to those compilers.
 *
 * This is meant to be used to declare lists of a type with a cleanup
 * function.  The type of the variable is a `GList *`.  You
 * must not add your own `*`.
 *
 * This macro can be used to avoid having to do explicit cleanups of
 * local variables when exiting functions.  It often vastly simplifies
 * handling of error conditions, removing the need for various tricks
 * such as `goto out` or repeating of cleanup code.  It is also helpful
 * for non-error cases.
 *
 * See also g_autoslist(), g_autoptr() and g_steal_pointer().
 *
 * Since: 2.56
 */

/**
 * g_autoslist:
 * @TypeName: a supported variable type
 *
 * Helper to declare a singly linked list variable with automatic deep cleanup.
 *
 * The list is deeply freed, in a way appropriate to the specified type, when the
 * variable goes out of scope.  The type must support this.
 *
 * This feature is only supported on GCC and clang.  This macro is not
 * defined on other compilers and should not be used in programs that
 * are intended to be portable to those compilers.
 *
 * This is meant to be used to declare lists of a type with a cleanup
 * function.  The type of the variable is a `GSList *`.  You
 * must not add your own `*`.
 *
 * This macro can be used to avoid having to do explicit cleanups of
 * local variables when exiting functions.  It often vastly simplifies
 * handling of error conditions, removing the need for various tricks
 * such as `goto out` or repeating of cleanup code.  It is also helpful
 * for non-error cases.
 *
 * See also g_autolist(), g_autoptr() and g_steal_pointer().
 *
 * Since: 2.56
 */

/**
 * g_autoqueue:
 * @TypeName: a supported variable type
 *
 * Helper to declare a double-ended queue variable with automatic deep cleanup.
 *
 * The queue is deeply freed, in a way appropriate to the specified type, when the
 * variable goes out of scope.  The type must support this.
 *
 * This feature is only supported on GCC and clang.  This macro is not
 * defined on other compilers and should not be used in programs that
 * are intended to be portable to those compilers.
 *
 * This is meant to be used to declare queues of a type with a cleanup
 * function.  The type of the variable is a `GQueue *`.  You
 * must not add your own `*`.
 *
 * This macro can be used to avoid having to do explicit cleanups of
 * local variables when exiting functions.  It often vastly simplifies
 * handling of error conditions, removing the need for various tricks
 * such as `goto out` or repeating of cleanup code.  It is also helpful
 * for non-error cases.
 *
 * See also g_autolist(), g_autoptr() and g_steal_pointer().
 *
 * Since: 2.62
 */


/**
 * G_DEFINE_AUTOPTR_CLEANUP_FUNC:
 * @TypeName: a type name to define a g_autoptr() cleanup function for
 * @func: the cleanup function
 *
 * Defines the appropriate cleanup function for a pointer type.
 *
 * The function will not be called if the variable to be cleaned up
 * contains %NULL.
 *
 * This will typically be the `_free()` or `_unref()` function for the given
 * type.
 *
 * With this definition, it will be possible to use g_autoptr() with
 * @TypeName.
 *
 * |[
 * G_DEFINE_AUTOPTR_CLEANUP_FUNC(GObject, g_object_unref)
 * ]|
 *
 * This macro should be used unconditionally; it is a no-op on compilers
 * where cleanup is not supported.
 *
 * Since: 2.44
 */

/**
 * G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC:
 * @TypeName: a type name to define a g_auto() cleanup function for
 * @func: the clear function
 *
 * Defines the appropriate cleanup function for a type.
 *
 * This will typically be the `_clear()` function for the given type.
 *
 * With this definition, it will be possible to use g_auto() with
 * @TypeName.
 *
 * |[
 * G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC(GQueue, g_queue_clear)
 * ]|
 *
 * This macro should be used unconditionally; it is a no-op on compilers
 * where cleanup is not supported.
 *
 * Since: 2.44
 */

/**
 * G_DEFINE_AUTO_CLEANUP_FREE_FUNC:
 * @TypeName: a type name to define a g_auto() cleanup function for
 * @func: the free function
 * @none: the "none" value for the type
 *
 * Defines the appropriate cleanup function for a type.
 *
 * With this definition, it will be possible to use g_auto() with
 * @TypeName.
 *
 * This function will be rarely used.  It is used with pointer-based
 * typedefs and non-pointer types where the value of the variable
 * represents a resource that must be freed.  Two examples are #GStrv
 * and file descriptors.
 *
 * @none specifies the "none" value for the type in question.  It is
 * probably something like %NULL or `-1`.  If the variable is found to
 * contain this value then the free function will not be called.
 *
 * |[
 * G_DEFINE_AUTO_CLEANUP_FREE_FUNC(GStrv, g_strfreev, NULL)
 * ]|
 *
 * This macro should be used unconditionally; it is a no-op on compilers
 * where cleanup is not supported.
 *
 * Since: 2.44
 */

/* Warnings and Assertions {{{1 */

/**
 * SECTION:warnings
 * @title: Warnings and Assertions
 * @short_description: warnings and assertions to use in runtime code
 *
 * GLib defines several warning functions and assertions which can be used to
 * warn of programmer errors when calling functions, and print error messages
 * from command line programs.
 *
 * The g_return_if_fail(), g_return_val_if_fail(), g_return_if_reached() and
 * g_return_val_if_reached() macros are intended as pre-condition assertions, to
 * be used at the top of a public function to check that the function’s
 * arguments are acceptable. Any failure of such a pre-condition assertion is
 * considered a programming error on the part of the caller of the public API,
 * and the program is considered to be in an undefined state afterwards. They
 * are similar to the libc assert() function, but provide more context on
 * failures.
 *
 * For example:
 * |[<!-- language="C" -->
 * gboolean
 * g_dtls_connection_shutdown (GDtlsConnection  *conn,
 *                             gboolean          shutdown_read,
 *                             gboolean          shutdown_write,
 *                             GCancellable     *cancellable,
 *                             GError          **error)
 * {
 *   // local variable declarations
 *
 *   g_return_val_if_fail (G_IS_DTLS_CONNECTION (conn), FALSE);
 *   g_return_val_if_fail (cancellable == NULL || G_IS_CANCELLABLE (cancellable), FALSE);
 *   g_return_val_if_fail (error == NULL || *error == NULL, FALSE);
 *
 *   // function body
 *
 *   return return_val;
 * }
 * ]|
 *
 * g_print() and g_printerr() are intended to be used for
 * output from command line applications, since they output to standard output
 * and standard error by default — whereas functions like g_message() and
 * g_log() may be redirected to special purpose message windows, files, or the
 * system journal.
 *
 * If the console encoding is not UTF-8 (as specified by g_get_console_charset())
 * then these functions convert the message first. Any Unicode
 * characters not defined by that charset are replaced by `'?'`. On Linux,
 * setlocale() must be called early in main() to load the encoding. This behaviour
 * can be changed by providing custom handlers to g_set_print_handler(),
 * g_set_printerr_handler() and g_log_set_handler().
 */

/* Windows Compatibility Functions {{{1 */

/**
 * SECTION:windows
 * @title: Windows Compatibility Functions
 * @short_description: UNIX emulation on Windows
 *
 * These functions provide some level of UNIX emulation on the
 * Windows platform. If your application really needs the POSIX
 * APIs, we suggest you try the Cygwin project.
 */

/**
 * MAXPATHLEN:
 *
 * Provided for UNIX emulation on Windows; equivalent to UNIX
 * macro %MAXPATHLEN, which is the maximum length of a filename
 * (including full path).
 */

/**
 * G_WIN32_DLLMAIN_FOR_DLL_NAME:
 * @static: empty or "static"
 * @dll_name: the name of the (pointer to the) char array where
 *     the DLL name will be stored. If this is used, you must also
 *     include `windows.h`. If you need a more complex DLL entry
 *     point function, you cannot use this
 *
 * On Windows, this macro defines a DllMain() function that stores
 * the actual DLL name that the code being compiled will be included in.
 *
 * On non-Windows platforms, expands to nothing.
 */

/**
 * G_WIN32_HAVE_WIDECHAR_API:
 *
 * On Windows, this macro defines an expression which evaluates to
 * %TRUE if the code is running on a version of Windows where the wide
 * character versions of the Win32 API functions, and the wide character
 * versions of the C library functions work. (They are always present in
 * the DLLs, but don't work on Windows 9x and Me.)
 *
 * On non-Windows platforms, it is not defined.
 *
 * Since: 2.6
 */


/**
 * G_WIN32_IS_NT_BASED:
 *
 * On Windows, this macro defines an expression which evaluates to
 * %TRUE if the code is running on an NT-based Windows operating system.
 *
 * On non-Windows platforms, it is not defined.
 *
 * Since: 2.6
 */
 
 /* Epilogue {{{1 */
/* vim: set foldmethod=marker: */