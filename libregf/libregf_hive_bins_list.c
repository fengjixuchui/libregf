/*
 * Hive bins list functions
 *
 * Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#include "libregf_definitions.h"
#include "libregf_hive_bin.h"
#include "libregf_hive_bin_cell.h"
#include "libregf_hive_bin_header.h"
#include "libregf_hive_bins_list.h"
#include "libregf_io_handle.h"
#include "libregf_libbfio.h"
#include "libregf_libcerror.h"
#include "libregf_libcnotify.h"
#include "libregf_libfcache.h"
#include "libregf_libfdata.h"
#include "libregf_unused.h"

/* Creates a hive bins list
 * Make sure the value hive_bins_list is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libregf_hive_bins_list_initialize(
     libregf_hive_bins_list_t **hive_bins_list,
     libregf_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libregf_hive_bins_list_initialize";

	if( hive_bins_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid hive bins list.",
		 function );

		return( -1 );
	}
	if( *hive_bins_list != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid hive bins list value already set.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	*hive_bins_list = memory_allocate_structure(
	                   libregf_hive_bins_list_t );

	if( *hive_bins_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create hive bins list.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *hive_bins_list,
	     0,
	     sizeof( libregf_hive_bins_list_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		memory_free(
		 *hive_bins_list );

		*hive_bins_list = NULL;

		return( -1 );
	}
	if( libfdata_list_initialize(
	     &( ( *hive_bins_list )->data_list ),
	     NULL,
	     NULL,
	     NULL,
	     (int (*)(intptr_t *, intptr_t *, libfdata_list_element_t *, libfdata_cache_t *, int, off64_t, size64_t, uint32_t, uint8_t, libcerror_error_t **)) &libregf_hive_bins_list_read_element_data,
	     NULL,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data list.",
		 function );

		goto on_error;
	}
	if( libfcache_cache_initialize(
	     &( ( *hive_bins_list )->data_cache ),
	     LIBREGF_MAXIMUM_CACHE_ENTRIES_HIVE_BINS,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create data cache.",
		 function );

		goto on_error;
	}
	( *hive_bins_list )->io_handle = io_handle;

	return( 1 );

on_error:
	if( *hive_bins_list != NULL )
	{
		if( ( *hive_bins_list )->data_list != NULL )
		{
			libfdata_list_free(
			 &( ( *hive_bins_list )->data_list ),
			 NULL );
		}
		memory_free(
		 *hive_bins_list );

		*hive_bins_list = NULL;
	}
	return( -1 );
}

/* Frees a hive bins list
 * Returns 1 if successful or -1 on error
 */
int libregf_hive_bins_list_free(
     libregf_hive_bins_list_t **hive_bins_list,
     libcerror_error_t **error )
{
	static char *function = "libregf_hive_bins_list_free";
	int result            = 1;

	if( hive_bins_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid hive bins list.",
		 function );

		return( -1 );
	}
	if( *hive_bins_list != NULL )
	{
		/* The io_handle reference is freed elsewhere
		 */
		if( ( *hive_bins_list )->data_list != NULL )
		{
			if( libfdata_list_free(
			     &( ( *hive_bins_list )->data_list ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free data list.",
				 function );

				result = -1;
			}
		}
		if( ( *hive_bins_list )->data_cache != NULL )
		{
			if( libfcache_cache_free(
			     &( ( *hive_bins_list )->data_cache ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free data cache.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *hive_bins_list );

		*hive_bins_list = NULL;
	}
	return( result );
}

/* Empties the cache of a hive bins list
 * Returns 1 if successful or -1 on error
 */
int libregf_hive_bins_list_empty_cache(
     libregf_hive_bins_list_t *hive_bins_list,
     libcerror_error_t **error )
{
	static char *function = "libregf_hive_bins_list_empty_cache";

	if( hive_bins_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid hive bins list.",
		 function );

		return( -1 );
	}
	if( libfcache_cache_empty(
	     hive_bins_list->data_cache,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to empty data cache.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the hive bins
 * Returns 1 if successful, 0 if no hive bin signature was found or -1 on error
 */
int libregf_hive_bins_list_read_file_io_handle(
     libregf_hive_bins_list_t *hive_bins_list,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     uint32_t hive_bins_size,
     libcerror_error_t **error )
{
	libregf_hive_bin_header_t *hive_bin_header = NULL;
	static char *function                      = "libregf_hive_bins_list_read_file_io_handle";
	off64_t alignment_size                     = 0;
	int hive_bin_index                         = 0;
	int result                                 = 0;

	if( hive_bins_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid hive bins list.",
		 function );

		return( -1 );
	}
	if( hive_bins_list->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid hive bins list - missing IO handle.",
		 function );

		return( -1 );
	}
	if( libregf_hive_bin_header_initialize(
	     &hive_bin_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create hive bin header.",
		 function );

		goto on_error;
	}
	while( hive_bins_size > 0 )
	{
		result = libregf_hive_bin_header_read_file_io_handle(
		          hive_bin_header,
		          file_io_handle,
		          file_offset,
		          error );

		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read hive bin: %d header at offset: %" PRIi64 " (0x%08" PRIx64 ").",
			 function,
			 hive_bin_index,
			 file_offset,
			 file_offset );

			goto on_error;
		}
		if( ( result == 0 )
		 || ( hive_bin_header->size == 0 ) )
		{
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: invalid hive bin: %d header at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
				 function,
				 hive_bin_index,
				 file_offset,
				 file_offset );
			}
#endif
			hive_bins_list->flags |= LIBREGF_HIVE_BINS_FLAG_IS_CORRUPTED;

			alignment_size += 512;
			file_offset    += 512;
			hive_bins_size -= 512;

			continue;
		}
		if( hive_bin_header->offset != ( file_offset - ( 4096 + alignment_size ) ) )
		{
			if( ( hive_bins_list->flags & LIBREGF_HIVE_BINS_FLAG_IS_CORRUPTED ) == 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
				 "%s: mismatch in hive bin offset (stored: %" PRIu32 " != calculated: %" PRIi64 ").",
				 function,
				 hive_bin_header->offset,
				 file_offset - ( 4096 + alignment_size ) );

				goto on_error;
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: mismatch in hive bin offset (stored: %" PRIu32 " != calculated: %" PRIi64 ") difference: %" PRIi64 ".\n",
				 function,
				 hive_bin_header->offset,
				 file_offset - ( 4096 + alignment_size ),
				 file_offset - ( 4096 + hive_bin_header->offset ) );
			}
#endif
			alignment_size = file_offset - ( 4096 + hive_bin_header->offset );
		}
		if( libregf_hive_bins_list_append_bin(
		     hive_bins_list,
		     file_offset,
		     hive_bin_header->size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append hive bin: %d.",
			 function,
			 hive_bin_index );

			goto on_error;
		}
		file_offset    += hive_bin_header->size;
		hive_bins_size -= hive_bin_header->size;

		hive_bin_index++;
	}
	if( libregf_hive_bin_header_free(
	     &hive_bin_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free hive bin header.",
		 function );

		return( -1 );
	}
	if( result == 0 )
	{
		if( hive_bin_index == 0 )
		{
			return( 0 );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: missing hive bin at offset: %" PRIi64 " (0x%08" PRIx64 ").\n",
			 function,
			 file_offset,
			 file_offset );
		}
#endif
		hive_bins_list->flags |= LIBREGF_HIVE_BINS_FLAG_IS_CORRUPTED;
	}
	if( ( hive_bins_list->flags & LIBREGF_HIVE_BINS_FLAG_IS_CORRUPTED ) != 0 )
	{
		hive_bins_list->io_handle->flags |= LIBREGF_IO_HANDLE_FLAG_IS_CORRUPTED;
	}
	return( 1 );

on_error:
	if( hive_bin_header != NULL )
	{
		libregf_hive_bin_header_free(
		 &hive_bin_header,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the hive bin index for a specific offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int libregf_hive_bins_list_get_index_at_offset(
     libregf_hive_bins_list_t *hive_bins_list,
     off64_t offset,
     int *hive_bin_index,
     libcerror_error_t **error )
{
	static char *function       = "libregf_hive_bins_list_get_index_at_offset";
	off64_t element_data_offset = 0;
	int result                  = 0;

	if( hive_bins_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid hive bins list.",
		 function );

		return( -1 );
	}
	result = libfdata_list_get_element_index_at_offset(
	          hive_bins_list->data_list,
	          offset,
	          hive_bin_index,
	          &element_data_offset,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data list element index at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 offset,
		 offset );

		return( -1 );
	}
	return( result );
}

/* Retrives a hive bin cell at a specific offset
 * Returns 1 if successful or -1 on error
 */
int libregf_hive_bins_list_get_cell_at_offset(
     libregf_hive_bins_list_t *hive_bins_list,
     libbfio_handle_t *file_io_handle,
     uint32_t hive_bin_cell_offset,
     libregf_hive_bin_cell_t **hive_bin_cell,
     libcerror_error_t **error )
{
	libregf_hive_bin_t *hive_bin = NULL;
	static char *function        = "libregf_hive_bins_list_get_cell_at_offset";
	off64_t hive_bin_data_offset = 0;
	int hive_bin_index           = 0;

	if( hive_bins_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid hive bins list.",
		 function );

		return( -1 );
	}
	if( libfdata_list_get_element_value_at_offset(
	     hive_bins_list->data_list,
	     (intptr_t *) file_io_handle,
	     (libfdata_cache_t *) hive_bins_list->data_cache,
	     (off64_t) hive_bin_cell_offset,
	     &hive_bin_index,
	     &hive_bin_data_offset,
	     (intptr_t **) &hive_bin,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve hive bin at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 hive_bin_cell_offset,
		 hive_bin_cell_offset );

		return( -1 );
	}
	if( libregf_hive_bin_get_cell_at_offset(
	     hive_bin,
	     hive_bin_cell_offset,
	     hive_bin_cell,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve hive bin cell at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 hive_bin_cell_offset,
		 hive_bin_cell_offset );

		return( -1 );
	}
	return( 1 );
}

/* Appends a hive bin to the list
 * Returns 1 if successful or -1 on error
 */
int libregf_hive_bins_list_append_bin(
     libregf_hive_bins_list_t *hive_bins_list,
     off64_t offset,
     uint32_t size,
     libcerror_error_t **error )
{
	static char *function = "libregf_hive_bins_list_append_bin";
	int element_index     = 0;

	if( hive_bins_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid hive bins list.",
		 function );

		return( -1 );
	}
	if( libfdata_list_append_element(
	     hive_bins_list->data_list,
	     &element_index,
	     0,
	     offset,
	     (size64_t) size,
	     0,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append hive bin to data list.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads a hive bin
 * Callback function for the data list
 * Returns 1 if successful or -1 on error
 */
int libregf_hive_bins_list_read_element_data(
     intptr_t *data_handle LIBREGF_ATTRIBUTE_UNUSED,
     libbfio_handle_t *file_io_handle,
     libfdata_list_element_t *element,
     libfdata_cache_t *cache,
     int data_range_file_index LIBREGF_ATTRIBUTE_UNUSED,
     off64_t data_range_offset,
     size64_t data_range_size,
     uint32_t data_range_flags LIBREGF_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBREGF_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libregf_hive_bin_t *hive_bin               = NULL;
	libregf_hive_bin_header_t *hive_bin_header = NULL;
	static char *function                      = "libregf_hive_bins_list_read_element_data";

	LIBREGF_UNREFERENCED_PARAMETER( data_handle )
	LIBREGF_UNREFERENCED_PARAMETER( data_range_file_index )
	LIBREGF_UNREFERENCED_PARAMETER( data_range_flags )
	LIBREGF_UNREFERENCED_PARAMETER( read_flags )

	if( libregf_hive_bin_header_initialize(
	     &hive_bin_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create hive bin header.",
		 function );

		goto on_error;
	}
	if( libregf_hive_bin_header_read_file_io_handle(
	     hive_bin_header,
	     file_io_handle,
	     data_range_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read hive bin header at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 data_range_offset,
		 data_range_offset );

		goto on_error;
	}
	if( (size64_t) hive_bin_header->size != data_range_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: mismatch in hive bin size (stored: %" PRIu32 " != calculated: %" PRIu64 ").",
		 function,
		 hive_bin_header->size,
		 data_range_size );

		goto on_error;
	}
	if( libregf_hive_bin_initialize(
	     &hive_bin,
	     hive_bin_header->offset,
	     hive_bin_header->size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create hive bin.",
		 function );

		goto on_error;
	}
	if( libregf_hive_bin_read_cells_file_io_handle(
	     hive_bin,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read hive bin cells.",
		 function );

		goto on_error;
	}
	if( libfdata_list_element_set_element_value(
	     element,
	     (intptr_t *) file_io_handle,
	     cache,
	     (intptr_t *) hive_bin,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libregf_hive_bin_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set hive bin as element value.",
		 function );

		goto on_error;
	}
	if( libregf_hive_bin_header_free(
	     &hive_bin_header,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free hive bin header.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( hive_bin != NULL )
	{
		libregf_hive_bin_free(
		 &hive_bin,
		 NULL );
	}
	if( hive_bin_header != NULL )
	{
		libregf_hive_bin_header_free(
		 &hive_bin_header,
		 NULL );
	}
	return( -1 );
}

