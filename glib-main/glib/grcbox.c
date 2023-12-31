/* grcbox.c: Reference counted data
 *
 * Copyright 2018  Emmanuele Bassi
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

#include "config.h"

#include "grcboxprivate.h"

#include "gmessages.h"
#include "grefcount.h"
#include "gtestutils.h"

#ifdef ENABLE_VALGRIND
#include "valgrind.h"
#endif

#include "glib_trace.h"

#include <string.h>

/* We use the same alignment as GTypeInstance and GNU libc's malloc */
#define ALIGN_STRUCT(offset)    ((offset + (STRUCT_ALIGNMENT - 1)) & -STRUCT_ALIGNMENT)

#define G_RC_BOX(p)             (GRcBox *) (((char *) (p)) - G_RC_BOX_SIZE)

gpointer
g_rc_box_alloc_full (gsize    block_size,
                     gsize    alignment,
                     gboolean atomic,
                     gboolean clear)
{
  /* We don't do an (atomic ? G_ARC_BOX_SIZE : G_RC_BOX_SIZE) check, here
   * because we have a static assertion that sizeof(GArcBox) == sizeof(GRcBox)
   * inside grcboxprivate.h, and we don't want the compiler to unnecessarily
   * warn about both branches of the conditional yielding identical results
   */
  gsize private_size = G_ARC_BOX_SIZE;
  gsize private_offset = 0;
  gsize real_size;
  char *allocated;

  g_assert (alignment != 0);

  /* We need to ensure that the private data is aligned */
  if (private_size % alignment != 0)
    {
      private_offset = private_size % alignment;
      private_size += (alignment - private_offset);
    }

  g_assert (block_size < (G_MAXSIZE - private_size));
  real_size = private_size + block_size;

  /* The real allocated size must be a multiple of @alignment, to
   * maintain the alignment of block_size
   */
  if (real_size % alignment != 0)
    {
      gsize offset = real_size % alignment;
      g_assert (real_size < (G_MAXSIZE - (alignment - offset)));
      real_size += (alignment - offset);
    }

#ifdef ENABLE_VALGRIND
  if (RUNNING_ON_VALGRIND)
    {
      /* When running under Valgrind we massage the memory allocation
       * to include a pointer at the tail end of the block; the pointer
       * is then set to the start of the block. This trick allows
       * Valgrind to keep track of the over-allocation and not be
       * confused when passing the pointer around
       */
      g_assert (private_size < (G_MAXSIZE - ALIGN_STRUCT (1)));
      private_size += ALIGN_STRUCT (1);

      if (clear)
        allocated = g_malloc0 (real_size + sizeof (gpointer));
      else
        allocated = g_malloc (real_size + sizeof (gpointer));

      *(gpointer *) (allocated + private_size + block_size) = allocated + ALIGN_STRUCT (1);

      VALGRIND_MALLOCLIKE_BLOCK (allocated + private_size, block_size + sizeof (gpointer), 0, TRUE);
      VALGRIND_MALLOCLIKE_BLOCK (allocated + ALIGN_STRUCT (1), private_size - ALIGN_STRUCT (1), 0, TRUE);
    }
  else
#endif /* ENABLE_VALGRIND */
    {
      if (clear)
        allocated = g_malloc0 (real_size);
      else
        allocated = g_malloc (real_size);
    }

  if (atomic)
    {
      /* We leave the alignment padding at the top of the allocation,
       * so we have an in memory layout of:
       *
       *  |[ offset ][ sizeof(GArcBox) ]||[ block_size ]|
       */
      GArcBox *real_box = (GArcBox *) (allocated + private_offset);
      /* Store the real size */
      real_box->mem_size = block_size;
      /* Store the alignment offset, to be used when freeing the
       * allocated block
       */
      real_box->private_offset = private_offset;
#ifndef G_DISABLE_ASSERT
      real_box->magic = G_BOX_MAGIC;
#endif
      g_atomic_ref_count_init (&real_box->ref_count);
    }
  else
    {
      /* We leave the alignment padding at the top of the allocation,
       * so we have an in memory layout of:
       *
       *  |[ offset ][ sizeof(GRcBox) ]||[ block_size ]|
       */
      GRcBox *real_box = (GRcBox *) (allocated + private_offset);
      /* Store the real size */
      real_box->mem_size = block_size;
      /* Store the alignment offset, to be used when freeing the
       * allocated block
       */
      real_box->private_offset = private_offset;
#ifndef G_DISABLE_ASSERT
      real_box->magic = G_BOX_MAGIC;
#endif
      g_ref_count_init (&real_box->ref_count);
    }

  TRACE (GLIB_RCBOX_ALLOC (allocated, block_size, atomic, clear));

  return allocated + private_size;
}

/**
 * g_rc_box_alloc:
 * @block_size: the size of the allocation, must be greater than 0
 *
 * Allocates @block_size bytes of memory, and adds reference
 * counting semantics to it.
 *
 * The data will be freed when its reference count drops to
 * zero.
 *
 * The allocated data is guaranteed to be suitably aligned for any
 * built-in type.
 *
 * Returns: (transfer full) (not nullable): a pointer to the allocated memory
 *
 * Since: 2.58
 */
gpointer
g_rc_box_alloc (gsize block_size)
{
  g_return_val_if_fail (block_size > 0, NULL);

  return g_rc_box_alloc_full (block_size, STRUCT_ALIGNMENT, FALSE, FALSE);
}

/**
 * g_rc_box_alloc0:
 * @block_size: the size of the allocation, must be greater than 0
 *
 * Allocates @block_size bytes of memory, and adds reference
 * counting semantics to it.
 *
 * The contents of the returned data is set to zero.
 *
 * The data will be freed when its reference count drops to
 * zero.
 *
 * The allocated data is guaranteed to be suitably aligned for any
 * built-in type.
 *
 * Returns: (transfer full) (not nullable): a pointer to the allocated memory
 *
 * Since: 2.58
 */
gpointer
g_rc_box_alloc0 (gsize block_size)
{
  g_return_val_if_fail (block_size > 0, NULL);

  return g_rc_box_alloc_full (block_size, STRUCT_ALIGNMENT, FALSE, TRUE);
}

/**
 * g_rc_box_new:
 * @type: the type to allocate, typically a structure name
 *
 * A convenience macro to allocate reference counted data with
 * the size of the given @type.
 *
 * This macro calls g_rc_box_alloc() with `sizeof (@type)` and
 * casts the returned pointer to a pointer of the given @type,
 * avoiding a type cast in the source code.
 *
 * Returns: (transfer full) (not nullable): a pointer to the
 *   allocated memory, cast to a pointer for the given @type
 *
 * Since: 2.58
 */

/**
 * g_rc_box_new0:
 * @type: the type to allocate, typically a structure name
 *
 * A convenience macro to allocate reference counted data with
 * the size of the given @type, and set its contents to zero.
 *
 * This macro calls g_rc_box_alloc0() with `sizeof (@type)` and
 * casts the returned pointer to a pointer of the given @type,
 * avoiding a type cast in the source code.
 *
 * Returns: (transfer full) (not nullable): a pointer to the
 *   allocated memory, cast to a pointer for the given @type
 *
 * Since: 2.58
 */

/**
 * g_rc_box_dup:
 * @block_size: the number of bytes to copy, must be greater than 0
 * @mem_block: (not nullable): the memory to copy
 *
 * Allocates a new block of data with reference counting
 * semantics, and copies @block_size bytes of @mem_block
 * into it.
 *
 * Returns: (transfer full) (not nullable): a pointer to the allocated
 *   memory
 *
 * Since: 2.58
 */
gpointer
(g_rc_box_dup) (gsize         block_size,
                gconstpointer mem_block)
{
  gpointer res;

  g_return_val_if_fail (block_size > 0, NULL);
  g_return_val_if_fail (mem_block != NULL, NULL);

  res = g_rc_box_alloc_full (block_size, STRUCT_ALIGNMENT, FALSE, FALSE);
  memcpy (res, mem_block, block_size);

  return res;
}

/**
 * g_rc_box_acquire:
 * @mem_block: (not nullable): a pointer to reference counted data
 *
 * Acquires a reference on the data pointed by @mem_block.
 *
 * Returns: (transfer full) (not nullable): a pointer to the data,
 *   with its reference count increased
 *
 * Since: 2.58
 */
gpointer
(g_rc_box_acquire) (gpointer mem_block)
{
  GRcBox *real_box = G_RC_BOX (mem_block);

  g_return_val_if_fail (mem_block != NULL, NULL);
#ifndef G_DISABLE_ASSERT
  g_return_val_if_fail (real_box->magic == G_BOX_MAGIC, NULL);
#endif

  g_ref_count_inc (&real_box->ref_count);

  TRACE (GLIB_RCBOX_ACQUIRE (mem_block, 0));

  return mem_block;
}

/**
 * g_rc_box_release:
 * @mem_block: (transfer full) (not nullable): a pointer to reference counted data
 *
 * Releases a reference on the data pointed by @mem_block.
 *
 * If the reference was the last one, it will free the
 * resources allocated for @mem_block.
 *
 * Since: 2.58
 */
void
g_rc_box_release (gpointer mem_block)
{
  g_rc_box_release_full (mem_block, NULL);
}

/**
 * g_rc_box_release_full:
 * @mem_block: (transfer full) (not nullable): a pointer to reference counted data
 * @clear_func: (not nullable): a function to call when clearing the data
 *
 * Releases a reference on the data pointed by @mem_block.
 *
 * If the reference was the last one, it will call @clear_func
 * to clear the contents of @mem_block, and then will free the
 * resources allocated for @mem_block.
 *
 * Since: 2.58
 */
void
g_rc_box_release_full (gpointer       mem_block,
                       GDestroyNotify clear_func)
{
  GRcBox *real_box = G_RC_BOX (mem_block);

  g_return_if_fail (mem_block != NULL);
#ifndef G_DISABLE_ASSERT
  g_return_if_fail (real_box->magic == G_BOX_MAGIC);
#endif

  if (g_ref_count_dec (&real_box->ref_count))
    {
      char *real_mem = (char *) real_box - real_box->private_offset;

      TRACE (GLIB_RCBOX_RELEASE (mem_block, 0));

      if (clear_func != NULL)
        clear_func (mem_block);

      TRACE (GLIB_RCBOX_FREE (mem_block));
      g_free (real_mem);
    }
}

/**
 * g_rc_box_get_size:
 * @mem_block: (not nullable): a pointer to reference counted data
 *
 * Retrieves the size of the reference counted data pointed by @mem_block.
 *
 * Returns: the size of the data, in bytes
 *
 * Since: 2.58
 */
gsize
g_rc_box_get_size (gpointer mem_block)
{
  GRcBox *real_box = G_RC_BOX (mem_block);

  g_return_val_if_fail (mem_block != NULL, 0);
#ifndef G_DISABLE_ASSERT
  g_return_val_if_fail (real_box->magic == G_BOX_MAGIC, 0);
#endif

  return real_box->mem_size;
}
