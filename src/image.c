#include <image.h>

#include <stdlib.h>
#include <assert.h>

image_t *image_new(image_data_t image_data)
{
	image_t *image = malloc(sizeof(image_t));
	image->image_data = image_data;

	image->pixels = malloc(image_data.width * image_data.height *
						  sizeof(color_t));
	assert(image->pixels);

	return image;
}

void image_delete(image_t *image)
{
	free(image->pixels);
	free(image);
}

color_t image_get_pixel(vector2_t coords, image_t *image)
{
	return image->pixels[coords.x * image->image_data.width + coords.y];
}

void image_set_pixel(vector2_t coords, color_t pixel, image_t *image)
{
	image->pixels[coords.x * image->image_data.width + coords.y] = pixel;
}

size_t image_get_width(image_t *image)
{
	return image->image_data.width;
}

size_t image_get_height(image_t *image)
{
	return image->image_data.height;
}

__s8 image_coords_in_bounds(vector2_t coords, image_t *image)
{
	if (coords.x >= (__s64)image->image_data.height ||
		coords.y >= (__s64)image->image_data.width) {
		return 0;
	}
	return 1;
}
