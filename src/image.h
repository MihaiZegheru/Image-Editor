#ifndef IMAGE_H__
#define IMAGE_H__

#include <stddef.h>

#include <color.h>
#include <image_data.h>
#include <vector2.h>

#define IMAGE_PIXELS_AT(coords_d, image_d) (image_d)->pixels[(coords_d).x *\
                                         (image_d)->image_data.width +\
                                         (coords_d).y]

typedef struct {
    color_t *pixels;
    image_data_t image_data;
} image_t;

image_t *image_new(image_data_t image_data);
void image_delete(image_t *image);

color_t image_get_pixel(vector2_t coords, image_t *image);
void image_set_pixel(vector2_t coords, color_t pixel, image_t *image);

size_t image_get_width(image_t *image);
size_t image_get_height(image_t *image);

#endif // IMAGE_H__