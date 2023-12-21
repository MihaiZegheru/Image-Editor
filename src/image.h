#ifndef IMAGE_H__
#define IMAGE_H__

#include <stddef.h>

#include <color.h>
#include <image_data.h>

typedef struct {
    color_t *pixels;
    image_data_t image_data;
} image_t;

image_t *image_new(image_data_t image_data);
void image_delete(image_t *image);

color_t image_at(size_t i, size_t j, image_t *image);

size_t image_get_width(image_t *image);
size_t image_get_height(image_t *image);

#endif
