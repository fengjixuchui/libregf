/*
 * Key item functions
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

#if !defined( _LIBREGF_KEY_ITEM_H )
#define _LIBREGF_KEY_ITEM_H

#include <common.h>
#include <types.h>

#include "libregf_hive_bins_list.h"
#include "libregf_key_descriptor.h"
#include "libregf_libbfio.h"
#include "libregf_libcdata.h"
#include "libregf_libcerror.h"
#include "libregf_libfcache.h"
#include "libregf_libfdata.h"
#include "libregf_named_key.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libregf_key_item libregf_key_item_t;

struct libregf_key_item
{
	/* The named key
	 */
	libregf_named_key_t *named_key;

	/* The class name
	 */
	uint8_t *class_name;

	/* The class name size
	 */
	uint16_t class_name_size;

	/* The security descriptor
	 */
	uint8_t *security_descriptor;

	/* The security descriptor size
	 */
	size_t security_descriptor_size;

	/* The values list
	 */
	libfdata_list_t *values_list;

	/* The values cache
	 */
	libfcache_cache_t *values_cache;

	/* The sub key descriptors
	 */
	libcdata_array_t *sub_key_descriptors;

	/* Various item flags
	 */
	uint8_t item_flags;
};

int libregf_key_item_initialize(
     libregf_key_item_t **key_item,
     libcerror_error_t **error );

int libregf_key_item_free(
     libregf_key_item_t **key_item,
     libcerror_error_t **error );

int libregf_key_item_read(
     libregf_key_item_t *key_item,
     libbfio_handle_t *file_io_handle,
     libregf_hive_bins_list_t *hive_bins_list,
     off64_t key_offset,
     uint32_t named_key_hash,
     libcerror_error_t **error );

int libregf_key_item_read_named_key(
     libregf_named_key_t *named_key,
     libbfio_handle_t *file_io_handle,
     libregf_hive_bins_list_t *hive_bins_list,
     off64_t named_key_offset,
     uint32_t named_key_hash,
     libcerror_error_t **error );

int libregf_key_item_read_class_name_data(
     libregf_key_item_t *key_item,
     const uint8_t *data,
     size_t data_size,
     uint16_t class_name_size,
     libcerror_error_t **error );

int libregf_key_item_read_class_name(
     libregf_key_item_t *key_item,
     libbfio_handle_t *file_io_handle,
     libregf_hive_bins_list_t *hive_bins_list,
     uint32_t class_name_offset,
     uint16_t class_name_size,
     libcerror_error_t **error );

int libregf_key_item_read_security_key(
     libregf_key_item_t *key_item,
     libbfio_handle_t *file_io_handle,
     libregf_hive_bins_list_t *hive_bins_list,
     uint32_t security_key_offset,
     libcerror_error_t **error );

int libregf_key_item_read_values_list(
     libregf_key_item_t *key_item,
     libbfio_handle_t *file_io_handle,
     libregf_hive_bins_list_t *hive_bins_list,
     uint32_t values_list_offset,
     uint32_t number_of_values_list_elements,
     libcerror_error_t **error );

int libregf_key_item_read_sub_keys_list(
     libcdata_array_t *sub_key_descriptors,
     libbfio_handle_t *file_io_handle,
     libregf_hive_bins_list_t *hive_bins_list,
     off64_t sub_keys_list_offset,
     int recursion_depth,
     libcerror_error_t **error );

int libregf_key_item_is_corrupted(
     libregf_key_item_t *key_item,
     libcerror_error_t **error );

int libregf_key_item_get_name_size(
     libregf_key_item_t *key_item,
     size_t *name_size,
     libcerror_error_t **error );

int libregf_key_item_get_name(
     libregf_key_item_t *key_item,
     uint8_t *name,
     size_t name_size,
     libcerror_error_t **error );

int libregf_key_item_get_utf8_name_size(
     libregf_key_item_t *key_item,
     size_t *utf8_string_size,
     int ascii_codepage,
     libcerror_error_t **error );

int libregf_key_item_get_utf8_name(
     libregf_key_item_t *key_item,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     int ascii_codepage,
     libcerror_error_t **error );

int libregf_key_item_get_utf16_name_size(
     libregf_key_item_t *key_item,
     size_t *utf16_string_size,
     int ascii_codepage,
     libcerror_error_t **error );

int libregf_key_item_get_utf16_name(
     libregf_key_item_t *key_item,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     int ascii_codepage,
     libcerror_error_t **error );

int libregf_key_item_get_class_name_size(
     libregf_key_item_t *key_item,
     size_t *class_name_size,
     libcerror_error_t **error );

int libregf_key_item_get_class_name(
     libregf_key_item_t *key_item,
     uint8_t *class_name,
     size_t class_name_size,
     libcerror_error_t **error );

int libregf_key_item_get_utf8_class_name_size(
     libregf_key_item_t *key_item,
     size_t *utf8_string_size,
     int ascii_codepage,
     libcerror_error_t **error );

int libregf_key_item_get_utf8_class_name(
     libregf_key_item_t *key_item,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     int ascii_codepage,
     libcerror_error_t **error );

int libregf_key_item_get_utf16_class_name_size(
     libregf_key_item_t *key_item,
     size_t *utf16_string_size,
     int ascii_codepage,
     libcerror_error_t **error );

int libregf_key_item_get_utf16_class_name(
     libregf_key_item_t *key_item,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     int ascii_codepage,
     libcerror_error_t **error );

int libregf_key_item_get_last_written_time(
     libregf_key_item_t *key_item,
     uint64_t *filetime,
     libcerror_error_t **error );

int libregf_key_item_get_security_descriptor_size(
     libregf_key_item_t *key_item,
     size_t *security_descriptor_size,
     libcerror_error_t **error );

int libregf_key_item_get_security_descriptor(
     libregf_key_item_t *key_item,
     uint8_t *security_descriptor,
     size_t security_descriptor_size,
     libcerror_error_t **error );

int libregf_key_item_get_number_of_values(
     libregf_key_item_t *key_item,
     int *number_of_values,
     libcerror_error_t **error );

int libregf_key_item_get_number_of_sub_key_descriptors(
     libregf_key_item_t *key_item,
     int *number_of_sub_key_descriptors,
     libcerror_error_t **error );

int libregf_key_item_get_sub_key_descriptor_by_index(
     libregf_key_item_t *key_item,
     int sub_key_descriptor_index,
     libregf_key_descriptor_t **sub_key_descriptor,
     libcerror_error_t **error );

int libregf_key_item_get_sub_key_descriptor_by_utf8_name(
     libregf_key_item_t *key_item,
     libbfio_handle_t *file_io_handle,
     libregf_hive_bins_list_t *hive_bins_list,
     uint32_t name_hash,
     const uint8_t *utf8_string,
     size_t utf8_string_length,
     libregf_key_descriptor_t **sub_key_descriptor,
     libcerror_error_t **error );

int libregf_key_item_get_sub_key_descriptor_by_utf16_name(
     libregf_key_item_t *key_item,
     libbfio_handle_t *file_io_handle,
     libregf_hive_bins_list_t *hive_bins_list,
     uint32_t name_hash,
     const uint16_t *utf16_string,
     size_t utf16_string_length,
     libregf_key_descriptor_t **sub_key_descriptor,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBREGF_KEY_ITEM_H ) */

