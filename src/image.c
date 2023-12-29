#include <image.h>

#include <stdlib.h>
#include <assert.h>

image_t image_new(image_data_t image_data)
{
    image_t image;
    image.image_data = image_data;

    image.pixels = malloc(image_data.width * image_data.height *
                          sizeof(color_t));
    assert(image.pixels != NULL);

    return image;
}

void image_delete(image_t *image)
{
    free(image->pixels);
}

color_t image_get_pixel(uint16_t i, uint16_t j, image_t *image)
{
    return IMAGE_PIXELS_AT(i, j, image);
}

void image_set_pixel(uint16_t i, uint16_t j, color_t pixel, image_t *image)
{
    IMAGE_PIXELS_AT(i, j, image) = pixel;
}

size_t image_get_width(image_t *image)
{
    return image->image_data.width;
}

size_t image_get_height(image_t *image)
{
    return image->image_data.height;
}
