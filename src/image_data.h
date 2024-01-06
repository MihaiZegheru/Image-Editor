/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#ifndef IMAGE_DATA_H__
#define IMAGE_DATA_H__

#include <stddef.h>
#include <linux/types.h>

#include <image_format_type.h>

#define IMAGE_MAX_PIXEL_VALUE 256

typedef struct {
	/**
	 * @brief The width of an image
	 *
	 */
	size_t m_width;
	/**
	 * @brief The height of an image
	 *
	 */
	size_t m_height;
	/**
	 * @brief The maximum value that a pixel can be in an image
	 *
	 */
	__u32 m_max_pixel_value;
	/**
	 * @brief The format of an image
	 *
	 */
	e_image_format_type_t m_format;
} s_image_data_t;

#endif // IMAGE_DATA_H__
