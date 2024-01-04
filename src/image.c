#include <image.h>

#include <stdlib.h>
#include <assert.h>

s_image_t *image_new(s_image_data_t image_data)
{
	s_image_t *image = malloc(sizeof(s_image_t));
	image->image_data = image_data;

	image->pixels = malloc(image_data.width * image_data.height *
						  sizeof(s_color_t));
	assert(image->pixels);

	return image;
}

void image_delete(s_image_t *image)
{
	free(image->pixels);
	free(image);
}

s_color_t image_get_pixel(s_vector2_t coords, s_image_t *image)
{
	return image->pixels[coords.x * image->image_data.width + coords.y];
}

void image_set_pixel(s_vector2_t coords, s_color_t pixel, s_image_t *image)
{
	image->pixels[coords.x * image->image_data.width + coords.y] = pixel;
}

size_t image_get_width(s_image_t *image)
{
	return image->image_data.width;
}

size_t image_get_height(s_image_t *image)
{
	return image->image_data.height;
}

__s8 image_coords_in_bounds(s_vector2_t coords, s_image_t *image)
{
	if (coords.x >= (__s64)image->image_data.height ||
		coords.y >= (__s64)image->image_data.width)
		return 0;

	return 1;
}
