#include <image.h>

#include <stdlib.h>
#include <assert.h>

s_image_t *image_new(s_image_data_t image_data)
{
	s_image_t *image = malloc(sizeof(s_image_t));
	image->m_image_data = m_image_data;

	image->m_pixels = malloc(m_image_data.width * m_image_data.height *
						  sizeof(s_color_t));
	assert(image->m_pixels);

	return image;
}

void image_delete(s_image_t *image)
{
	free(image->m_pixels);
	free(image);
}

s_color_t image_get_pixel(s_vector2_t coords, s_image_t *image)
{
	return image->m_pixels[coords.m_x * image->m_image_data.width + coords.m_y];
}

void image_set_pixel(s_vector2_t coords, s_color_t pixel, s_image_t *image)
{
	image->m_pixels[coords.m_x * image->m_image_data.width + coords.m_y] = pixel;
}

size_t image_get_width(s_image_t *image)
{
	return image->m_image_data.width;
}

size_t image_get_height(s_image_t *image)
{
	return image->m_image_data.height;
}

__s8 image_coords_in_bounds(s_vector2_t coords, s_image_t *image)
{
	if (coords.m_x >= (__s64)image->m_image_data.height ||
		coords.m_y >= (__s64)image->m_image_data.width)
		return 0;

	return 1;
}
