#include <image.h>

#include <stdlib.h>
#include <assert.h>

image_t *image_new(image_data_t image_data)
{
    image_t *image = malloc(sizeof(image_t *));
    assert(image != NULL);

    image->image_data = image_data;

    image->pixels = malloc(image_data.width * image_data.height *
                           sizeof(color_t));
    assert(image->pixels != NULL);

    return image;
}

void image_delete(image_t *image)
{
    free(image->pixels);
    free(image);
}

color_t image_at(size_t i, size_t j, image_t *image)
{
    return image->pixels[i * image_get_width(image) + j]; 
}

size_t image_get_width(image_t *image)
{
    return image->image_data.width;
}

size_t image_get_height(image_t *image)
{
    return image->image_data.height;
}
