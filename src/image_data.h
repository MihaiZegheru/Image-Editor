#ifndef IMAGE_DATA_H__
#define IMAGE_DATA_H__

#include <stddef.h>
#include <linux/types.h>

#include <image_format_type.h>

#define IMAGE_MAX_PIXEL_VALUE 256

typedef struct {
	size_t m_width;
	size_t m_height;
	__u32 m_max_pixel_value;
	e_image_format_type_t m_format;
} s_image_data_t;

#endif // IMAGE_DATA_H__
