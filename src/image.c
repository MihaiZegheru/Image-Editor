#include <image.h>

#include <stdlib.h>
#include <assert.h>

image_t *image_new(image_data_t image_data)
{
    image_t *image = malloc(sizeof(image_t));
    image->image_data = image_data;

    image->pixels = malloc(image_data.width * image_data.height *
                          sizeof(color_t));
    assert(image->pixels != NULL);

    return image;
}

void image_delete(image_t *image)
{
    free(image->pixels);
}

color_t image_get_pixel(vector2_t coords, image_t *image)
{
    // return IMAGE_PIXELS_AT(coords, image);
    // printf("GETTING FOR COORDS %d %d\n", coords.x, coords.y);
    return image->pixels[coords.x * image->image_data.height + coords.y];
}

void image_set_pixel(vector2_t coords, color_t pixel, image_t *image)
{
    // IMAGE_PIXELS_AT(coords, image) = pixel;
    image->pixels[coords.x * image->image_data.height + coords.y] = pixel;
}

size_t image_get_width(image_t *image)
{
    return image->image_data.width;
}

size_t image_get_height(image_t *image)
{
    return image->image_data.height;
}
