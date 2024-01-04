#ifndef IMAGE_H__
#define IMAGE_H__

#include <linux/types.h>
#include <stddef.h>

#include <color.h>
#include <image_data.h>
#include <vector2.h>

typedef struct {
	s_color_t *m_pixels;
	s_image_data_t m_image_data;
} s_image_t;

s_image_t *image_new(s_image_data_t image_data);
void image_delete(s_image_t *image);

s_color_t image_get_pixel(s_vector2_t coords, s_image_t *image);
void image_set_pixel(s_vector2_t coords, s_color_t pixel, s_image_t *image);

size_t image_get_width(s_image_t *image);
size_t image_get_height(s_image_t *image);

__s8 image_coords_in_bounds(s_vector2_t coords, s_image_t *image);

#endif // IMAGE_H__
