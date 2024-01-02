#include <image_loader.h>

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <utils.h>
#include <vector2.h>

static void image_loader_read_line(char *s, size_t max_len, FILE *file)
{
    size_t index = 0;
    char c = 'a';
    printf("**");
    while (index < max_len && c != '\n' && c != 'EOF') {
        printf("%d ", ftell(file));
        // printf("1");
        fscanf(file, "%c", &c);
        s[index++] = c;
    }
}

static image_data_t image_loader_load_image_data_1(FILE *file)
{
    image_data_t image_data;

    image_format_type_t format = IFT_NONE;
    uint16_t width = 0;
    uint16_t height = 0;
    uint16_t max_pixel_value = 0;

    const size_t MAX_BUFFER = 255;
    char line_buffer[MAX_BUFFER];
printf("%d\n", ftell(file));
    image_loader_read_line(line_buffer, MAX_BUFFER, file);
    printf("%s", line_buffer);
printf("%d\n", ftell(file));
    size_t index = 0;
    while (!max_pixel_value) {
        if (line_buffer[index] == ' ') {
            index++;
            continue;
        }

        if (line_buffer[index] == '\n') {
            printf("%d\n", ftell(file));
            image_loader_read_line(line_buffer, MAX_BUFFER, file);
            printf("%s", line_buffer);
            printf("%s", line_buffer);
            index = 0;
            continue;
        }

        if (!format && line_buffer[index] == 'P') {
            index++;
            printf("%d\n", ftell(file));
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
                 printf("%d\n", ftell(file));
            } else if (!max_pixel_value) {
                max_pixel_value = value;
                printf("%d\n", ftell(file));
            }
        }
    }

    image_data.format = format;
    image_data.width = width;
    image_data.height = height;
    image_data.max_pixel_value = max_pixel_value;
printf("%d\n", ftell(file));

    return image_data;
}

static image_data_t image_loader_load_image_data(FILE *file)
{
    image_data_t image_data;

    image_format_type_t format = IFT_NONE;
    uint16_t width = 0;
    uint16_t height = 0;
    uint16_t max_pixel_value = 0;

    const uint8_t MAX_BUFFER = 255;
    char line_buffer[255];
// printf("%d\n", ftell(file));
    fgets(line_buffer, MAX_BUFFER, file);
    size_t index = 0;
    // printf("%s\n", line_buffer);
// printf("%d\n", ftell(file));
    while (!max_pixel_value) {
        if (line_buffer[index] == ' ') {
            index++;
            continue;
        }

        if (line_buffer[index] == '\n') {
            // printf("%d\n", ftell(file));
            fgets(line_buffer, MAX_BUFFER, file);
            // printf("%s", line_buffer);
            index = 0;
            continue;
        }

        if (!format && line_buffer[index] == 'P') {
            index++;
            // printf("%d\n", ftell(file));
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
                //  printf("%d\n", ftell(file));
            } else if (!max_pixel_value) {
                max_pixel_value = value;
                // printf("%d\n", ftell(file));
            }
        }
    }

    image_data.format = format;
    image_data.width = width;
    image_data.height = height;
    image_data.max_pixel_value = max_pixel_value;
// printf("%d\n", ftell(file));

    return image_data;
}

void image_loader_load_pixels_p2(image_t *image, FILE *file)
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
        }
    }
}

// static void image_loader_set_pixels_p3(image_t *image, FILE *file)
// {

// }

// static void image_loader_set_pixels_p5(image_t *image, FILE *file)
// {

// }

static void image_loader_load_pixels_p6(image_t *image, FILE *file)
{
    // freopen("res/a.pgm", "rb", file);
	// fseek(file, ftell(file) + 1, SEEK_SET);
    printf("AA");
    printf("%d %d\n", image_get_height(image), image_get_width(image));

    for (size_t i = 0; i < image_get_height(image); i++) {
        for (size_t j = 0; j < image_get_width(image); j++) {
            color_t color;

            // uint8_t a,b,c;
            fscanf(file, "%c", &color.r);
            fscanf(file, "%c", &color.g);
            fscanf(file, "%c", &color.b);

            printf("%d ", ftell(file));


            // fread(&color.r, sizeof(color.r), 1, file);
            // fread(&color.g, sizeof(color.g), 1, file);
            // fread(&color.b, sizeof(color.b), 1, file);
            printf("INDEX: %d %d\n", i, j);
            printf("%"SCNu8" %"SCNu8" %"SCNu8"\n", color.r, color.g, color.b);

            vector2_t coords;
            coords.x = i;
            coords.y = j;
            image_set_pixel(coords, color, image);
            color_t c = image_get_pixel(coords, image);

            printf("%d %d %d\n", c.r, c.g, c.b);
        }
    }
}

static void image_loader_load_pixels(image_t *image, FILE *file)
{
    switch (image->image_data.format) {
        case IFT_P2:
            image_loader_load_pixels_p2(image, file);
            break;
        case IFT_P3:
            // image_loader_set_pixels_p3(image, file);
            break;
        case IFT_P5:
            // image_loader_set_pixels_p5(image, file);
            break;
        case IFT_P6:
            image_loader_load_pixels_p6(image, file);
            break;
        default:
            break;
    }
}

image_t *image_loader_load(char *file_path)
{
    FILE *file = fopen(file_path, "r");
    
    image_data_t image_data = image_loader_load_image_data(file);
    image_t *image = image_new(image_data);
    image_loader_load_pixels(image, file);
        printf("BB");

    return image;
}

void image_loader_save_pixels_p2(image_t *image, FILE *file)
{
    for (size_t i = 0; i < image_get_height(image); i++) {
        for (size_t j = 0; j < image_get_width(image); j++) {
            vector2_t coords;
            coords.x = i;
            coords.y = j;

            uint8_t value = image_get_pixel(coords, image).r;
            fprintf(file, "%"SCNu8" ", value);
        }
        fprintf(file, "\n");
    }
}

// static void image_loader_save_pixels_p3(image_t *image, FILE *file)
// {

// }

// static void image_loader_save_pixels_p5(image_t *image, FILE *file)
// {

// }

static void image_loader_save_pixels_p6(image_t *image, FILE *file)
{
    // freopen("res/a.pgm", "wb", file);
	// fseek(file, ftell(file) + 1, SEEK_SET);

    for (size_t i = 0; i < image_get_height(image); i++) {
        for (size_t j = 0; j < image_get_width(image); j++) {
            vector2_t coords;
            coords.x = i;
            coords.y = j;
            
            color_t color = image_get_pixel(coords, image);
            fprintf(file, "%c", color.r);
            fprintf(file, "%c", color.g);
            fprintf(file, "%c", color.b);
            // printf("%d %d %d\n", color.r, color.g, color.b);
        }
    }
}

static void image_loader_save_pixels(image_t *image, FILE *file)
{
    switch (image->image_data.format) {
        case IFT_P2:
            image_loader_save_pixels_p2(image, file);
            break;
        case IFT_P3:
            // image_loader_save_pixels_p3(image, file);
            break;
        case IFT_P5:
            // image_loader_save_pixels_p5(image, file);
            break;
        case IFT_P6:
            image_loader_save_pixels_p6(image, file);
            break;
        default:
            break;
    }
}

static void image_loader_save_image_data(image_data_t image_data, FILE *file)
{
    switch (image_data.format) {
        case IFT_P2:
            fprintf(file, "P2\n");
            break;
        case IFT_P3:
            fprintf(file, "P3\n");
            break;
        case IFT_P5:
            fprintf(file, "P5\n");
            break;
        case IFT_P6:
            fprintf(file, "P6\n");
            break;
        default:
            break;
    }

    fprintf(file, "%zu %zu\n", image_data.width, image_data.height);
    fprintf(file, "%"SCNu32"\n", image_data.max_pixel_value);
}

void image_loader_save(image_t *image, char *file_path)
{
    FILE *file = fopen(file_path, "w");
    // printf("%s", file_path);

    image_loader_save_image_data(image->image_data, file);
    image_loader_save_pixels(image, file);
}
