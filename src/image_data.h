#ifndef IMAGE_DATA_H__
#define IMAGE_DATA_H__

#include <stddef.h>
#include <linux/types.h>

#include <image_format_type.h>

typedef struct {
	size_t width;
	size_t height;
	__u32 max_pixel_value;
	e_image_format_type_t format;
} s_image_data_t;

#endif // IMAGE_DATA_H__
