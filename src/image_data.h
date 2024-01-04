#ifndef IMAGE_DATA_H__
#define IMAGE_DATA_H__

#include <linux/types.h>

#include <image_format_type.h>

typedef struct {
	size_t width;
	size_t height;
	__u32 max_pixel_value;
	image_format_type_t format;
} image_data_t;

#endif // IMAGE_DATA_H__
