#ifndef IMAGE_DATA_H__
#define IMAGE_DATA_H__

#include <stdint.h>

#include <image_format_type.h>

typedef struct {
    size_t width;
    size_t height;
    uint32_t max_pixel_value;
    image_format_type_t format;
} image_data_t;

#endif // IMAGE_DATA_H__