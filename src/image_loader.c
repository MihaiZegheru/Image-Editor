#include <image_loader.h>

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <linux/types.h>

#include <vector2.h>
#include <utils.h>

static s_image_data_t image_loader_load_image_data(FILE * file);
static void image_loader_load_pixels_p2(s_image_t *image, FILE *file);
static void image_loader_load_pixels_p3(s_image_t *image, FILE *file);
static void image_loader_load_pixels_p5(s_image_t *image, FILE *file);
static void image_loader_load_pixels_p6(s_image_t *image, FILE *file);
static void image_loader_load_pixels(s_image_t *image, FILE *file);

static void image_loader_save_image_data(s_image_data_t image_data, FILE *file);
static void image_loader_save_pixels_p2(s_image_t *image, FILE *file);
static void image_loader_save_pixels_p3(s_image_t *image, FILE *file);
static void image_loader_save_pixels_p5(s_image_t *image, FILE *file);
static void image_loader_save_pixels_p6(s_image_t *image, FILE *file);
static void image_loader_save_pixels(s_image_t *image, FILE *file);

s_image_t *image_loader_load(char *file_path)
{
	FILE *file = fopen(file_path, "r");
	if (!file)
		return NULL;

	s_image_data_t image_data = image_loader_load_image_data(file);
	s_image_t *image = image_new(image_data);
	image_loader_load_pixels(image, file);

	fclose(file);

	return image;
}

void image_loader_save(s_image_t *image, char *file_path)
{
	FILE *file = fopen(file_path, "w");

	image_loader_save_image_data(image->image_data, file);
	image_loader_save_pixels(image, file);

	fclose(file);
}

static s_image_data_t image_loader_load_image_data(FILE *file)
{
	s_image_data_t image_data;

	e_image_format_type_t format = IFT_NONE;
	__u16 width = 0;
	__u16 height = 0;
	__u16 max_pixel_value = 0;

	const __u8 MAX_BUFFER = 255;
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
			__u16 value = (__u16)utils_string_to_int64(line_buffer +
													   index);

			while (line_buffer[index] != ' ' && line_buffer[index] != '\n' &&
				   line_buffer[index] != '\0')
				index++;

			if (!width)
				width = value;
			else if (!height)
				height = value;
			else if (!max_pixel_value)
				max_pixel_value = value;
		}
	}

	image_data.format = format;
	image_data.width = width;
	image_data.height = height;
	image_data.max_pixel_value = max_pixel_value;

	return image_data;
}

static void image_loader_load_pixels_p2(s_image_t *image, FILE *file)
{
	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			__u8 value;
			fscanf(file, "%hhu", &value);

			s_color_t color;
			color.r = value;
			color.g = value;
			color.b = value;

			s_vector2_t coords;
			coords.x = i;
			coords.y = j;
			image_set_pixel(coords, color, image);
		}
	}
}

static void image_loader_load_pixels_p3(s_image_t *image, FILE *file)
{
	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			s_color_t color;
			fscanf(file, "%hhu", &color.r);
			fscanf(file, "%hhu", &color.g);
			fscanf(file, "%hhu", &color.b);

			s_vector2_t coords;
			coords.x = i;
			coords.y = j;
			image_set_pixel(coords, color, image);
		}
	}
}

static void image_loader_load_pixels_p5(s_image_t *image, FILE *file)
{
	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			__u8 value;
			fscanf(file, "%c", &value);

			s_color_t color;
			color.r = value;
			color.g = value;
			color.b = value;

			s_vector2_t coords;
			coords.x = i;
			coords.y = j;
			image_set_pixel(coords, color, image);
		}
	}
}

static void image_loader_load_pixels_p6(s_image_t *image, FILE *file)
{
	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			s_color_t color;
			fscanf(file, "%c", &color.r);
			fscanf(file, "%c", &color.g);
			fscanf(file, "%c", &color.b);

			s_vector2_t coords;
			coords.x = i;
			coords.y = j;
			image_set_pixel(coords, color, image);
		}
	}
}

static void image_loader_load_pixels(s_image_t *image, FILE *file)
{
	switch (image->image_data.format) {
	case IFT_P2:
		image_loader_load_pixels_p2(image, file);
		break;
	case IFT_P3:
		image_loader_load_pixels_p3(image, file);
		break;
	case IFT_P5:
		image_loader_load_pixels_p5(image, file);
		break;
	case IFT_P6:
		image_loader_load_pixels_p6(image, file);
		break;
	default:
		break;
	}
}

static void image_loader_save_image_data(s_image_data_t image_data, FILE *file)
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
	fprintf(file, "%u\n", image_data.max_pixel_value);
}

static void image_loader_save_pixels_p2(s_image_t *image, FILE *file)
{
	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			s_vector2_t coords;
			coords.x = i;
			coords.y = j;

			__u8 value = image_get_pixel(coords, image).r;
			fprintf(file, "%hhu ", value);
		}
		fprintf(file, "\n");
	}
}

static void image_loader_save_pixels_p3(s_image_t *image, FILE *file)
{
	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			s_vector2_t coords;
			coords.x = i;
			coords.y = j;

			s_color_t color = image_get_pixel(coords, image);
			fprintf(file, "%hhu ", color.r);
			fprintf(file, "%hhu ", color.g);
			fprintf(file, "%hhu ", color.b);
		}
		fprintf(file, "\n");
	}
}

static void image_loader_save_pixels_p5(s_image_t *image, FILE *file)
{
	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			s_vector2_t coords;
			coords.x = i;
			coords.y = j;

			__u8 value = image_get_pixel(coords, image).r;
			fprintf(file, "%c", value);
		}
	}
}

static void image_loader_save_pixels_p6(s_image_t *image, FILE *file)
{
	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			s_vector2_t coords;
			coords.x = i;
			coords.y = j;

			s_color_t color = image_get_pixel(coords, image);
			fprintf(file, "%c", color.r);
			fprintf(file, "%c", color.g);
			fprintf(file, "%c", color.b);
		}
	}
}

static void image_loader_save_pixels(s_image_t *image, FILE *file)
{
	switch (image->image_data.format) {
	case IFT_P2:
		image_loader_save_pixels_p2(image, file);
		break;
	case IFT_P3:
		image_loader_save_pixels_p3(image, file);
		break;
	case IFT_P5:
		image_loader_save_pixels_p5(image, file);
		break;
	case IFT_P6:
		image_loader_save_pixels_p6(image, file);
		break;
	default:
		break;
	}
}
