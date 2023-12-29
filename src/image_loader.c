#include <image_loader.h>

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <utils.h>
#include <vector2.h>

static image_data_t image_loader_get_image_data(FILE *file)
{
    image_data_t image_data;

    image_format_type_t format = IFT_NONE;
    uint16_t width = 0;
    uint16_t height = 0;
    uint16_t max_pixel_value = 0;

    const uint8_t MAX_BUFFER = 255;
    char line_buffer[MAX_BUFFER];

    fgets(line_buffer, MAX_BUFFER, file);
    size_t index = 0;

    while (!max_pixel_value) {
        if (line_buffer[index] == ' ') {
            index++;
            continue;
        }

        if (line_buffer[index] == '\n') {
            fgets(line_buffer, MAX_BUFFER, file);
            index = 0;
            continue;
        }

        if (!format && line_buffer[index] == 'P') {
            index++;
            switch (line_buffer[index]) {
                case '2':
                    format = IFT_P2;
                    break;
                case '3':
                    format = IFT_P3;
                    break;
                case '5':
                    format = IFT_P5;
                    break;
                case '6':
                    format = IFT_P6;
                    break;
                default:
                    break;
            }

            index++;
            continue;
        } else {
            uint16_t value = (uint16_t)utils_string_to_int64(line_buffer +
                                                             index);
            while (line_buffer[index] != ' ' && line_buffer[index] != '\n' &&
                   line_buffer[index] != '\0') {
                index++;
            }

            if (!width) {
                width = value;
            } else if (!height) {
                height = value;
            } else if (!max_pixel_value) {
                max_pixel_value = value;
            }
        }
    }

    image_data.format = format;
    image_data.width = width;
    image_data.height = height;
    image_data.max_pixel_value = max_pixel_value;

    return image_data;
}

void image_loader_set_pixels_p2(image_t *image, FILE *file)
{
    // size_t i = 100;
    for (size_t i = 0; i < image_get_height(image); i++) {
        for (size_t j = 0; j < image_get_width(image); j++) {
            uint8_t value;
            fscanf(file, "%"SCNu8, &value);

            color_t color;
            color.r = value;
            color.g = value;
            color.b = value;

            vector2_t coords;
            coords.x = i;
            coords.y = j;

            image_set_pixel(coords, color, image);
            // printf("%d\n", image_get_pixel(coords, image).r);
        }
    }
    // size_t i = 100;
    // printf("%d\n", image->pixels[0].r);
    // for (size_t i = 0; i < 1; i++) {
        // for (size_t j = 0; j < 10; j++) {
            // uint8_t value;

            // vector2_t coords;
            // coords.x = i;
            // coords.y = j;
            // value = image_get_pixel(coords, image).r;
            // printf("%d ", value);
        // }
    // }
    // printf("\n");
}

// static void image_loader_set_pixels_p3(image_t *image, FILE *file)
// {

// }

// static void image_loader_set_pixels_p5(image_t *image, FILE *file)
// {

// }

static void image_loader_set_pixels_p6(image_t *image, FILE *file)
{
    freopen("res/a.pgm", "rb", file);
	fseek(file, ftell(file) + 1, SEEK_SET);

    for (size_t i = 0; i < image_get_height(image); i++) {
        for (size_t j = 0; j < image_get_width(image); j++) {
            color_t color;
            fread(&color.r, sizeof(color.r), 1, file);
            fread(&color.g, sizeof(color.g), 1, file);
            fread(&color.b, sizeof(color.b), 1, file);

            vector2_t coords;
            coords.x = i;
            coords.y = j;
            image_set_pixel(coords, color, image);
        }
    }
}

void image_loader_set_pixels(image_t *image, FILE *file)
{
    switch (image->image_data.format) {
        case IFT_P2:
        printf("LOADING P2...\n");
            image_loader_set_pixels_p2(image, file);


    for (size_t i = 0; i < 1; i++) {
        for (size_t j = 0; j < 10; j++) {
            uint8_t value;

            vector2_t coords;
            coords.x = i;
            coords.y = j;

            // int64_t a;
            // a = j;
            // printf("*%d*", (int64_t)j);

            printf("%zu %zu ", i, j);
            printf("%zu %zu ", coords.x, coords.y);

            value = image_get_pixel(coords, image).r;

            printf("%d\n", value);
            // printf("%d ", i * image->image_data.height + j);
            // printf("%d\n", image->pixels[i * image->image_data.height + j].r);
        }
    }


            break;
        case IFT_P3:
            // image_loader_set_pixels_p3(image, file);
            break;
        case IFT_P5:
            // image_loader_set_pixels_p5(image, file);
            break;
        case IFT_P6:
            image_loader_set_pixels_p6(image, file);
            break;
        default:
            break;
    }
}

image_t *image_loader_load(char *file_path)
{
    FILE *file = fopen(file_path, "r");
    assert(file != NULL);

    image_data_t image_data = image_loader_get_image_data(file);

    image_t *image = image_new(image_data);
    image_loader_set_pixels(image, file);

    return image;
}
