#include <image_loader.h>

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

image_t *image_loader_load(const char *file_path)
{
    FILE *file = fopen(file_path, "rb");
    assert(file != NULL);

    char format[2];
    fscanf(file, "%s", format);
    
    if (!strcmp(format, "P6")) {
        char c;
        c = fgetc(file);
        return image_loader_get_ppm(file);
    }

    return NULL;
}

image_t *image_loader_get_ppm(FILE *file)
{
    image_data_t image_data;

    uint16_t width;
    uint16_t height;
    uint16_t max_pixel_value;
    fscanf(file, "%"SCNu16"%"SCNu16"%"SCNu16, &width, &height,
           &max_pixel_value);

    image_data.width = width;
    image_data.height = height;
    image_data.max_pixel_value = max_pixel_value;

    image_t *image = image_new(image_data);

    for (uint16_t i = 0; i < height; i++) {
        for (uint16_t j = 0; j < width; j++) {
            color_t pixel;
            fscanf(file, "%"SCNu16"%"SCNu16"%"SCNu16, &pixel.r, &pixel.g,
                   &pixel.b);

            image_set_pixel(i, j, pixel, image);
        }
    }

    return image;
}
