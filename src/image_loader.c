/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#include <image_loader.h>

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <linux/types.h>

#include <vector2.h>
#include <utils.h>

/**
 * @brief Load image_data from given FILE
 *
 * @param file
 * @return s_image_data_t
 */
static s_image_data_t image_loader_load_image_data(FILE * file);

/**
 * @brief Load pixels for IFT_P2 from FILE into image
 *
 * @param image
 * @param file
 */
static void image_loader_load_pixels_p2(s_image_t *image, FILE *file);

/**
 * @brief Load pixels for IFT_P3 from FILE into image
 *
 * @param image
 * @param file
 */
static void image_loader_load_pixels_p3(s_image_t *image, FILE *file);

/**
 * @brief Load pixels for IFT_P5 from FILE into image
 *
 * @param image
 * @param file
 */
static void image_loader_load_pixels_p5(s_image_t *image, FILE *file);

/**
 * @brief Load pixels for IFT_P6 from FILE into image
 *
 * @param image
 * @param file
 */
static void image_loader_load_pixels_p6(s_image_t *image, FILE *file);

/**
 * @brief Decide on how to load pixels for an image_format_type from FILE into
 *		  image and calls the respective function
 *
 * @param image
 * @param file
 */
static void image_loader_load_pixels(s_image_t *image, FILE *file);

/**
 * @brief Save image_data to given FILE
 *
 * @param image_data
 * @param file
 */
static void image_loader_save_image_data(s_image_data_t image_data, FILE *file);

/**
 * @brief Save pixels for IFT_P2 from image to FILE
 *
 * @param image
 * @param file
 */
static void image_loader_save_pixels_p2(s_image_t *image, FILE *file);

/**
 * @brief Save pixels for IFT_P3 from image to FILE
 *
 * @param image
 * @param file
 */
static void image_loader_save_pixels_p3(s_image_t *image, FILE *file);

/**
 * @brief Save pixels for IFT_P5 from image to FILE
 *
 * @param image
 * @param file
 */
static void image_loader_save_pixels_p5(s_image_t *image, FILE *file);

/**
 * @brief Save pixels for IFT_P6 from image to FILE
 *
 * @param image
 * @param file
 */
static void image_loader_save_pixels_p6(s_image_t *image, FILE *file);

/**
 * @brief Decide on how to save pixels for an image_format_type from image into
 *		  FILE and calls the respective function
 *
 * @param image
 * @param file
 */
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

	image_loader_save_image_data(image->m_image_data, file);
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

	char line_buffer[LINE_MAX_BUFFER];

	fgets(line_buffer, LINE_MAX_BUFFER, file);
	size_t index = 0;

	while (!max_pixel_value) {
		if (line_buffer[index] == ' ') {
			index++;
			continue;
		}

		if (line_buffer[index] == '\n' || line_buffer[index] == '#') {
			fgets(line_buffer, LINE_MAX_BUFFER, file);
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
			__u16 value = (__u16)utils_string_to_int64(line_buffer + index);

			while (line_buffer[index] >= '0' && line_buffer[index] <= '9')
				index++;

			if (!width)
				width = value;
			else if (!height)
				height = value;
			else if (!max_pixel_value)
				max_pixel_value = value;
		}
	}

	image_data.m_format = format;
	image_data.m_width = width;
	image_data.m_height = height;
	image_data.m_max_pixel_value = max_pixel_value;

	return image_data;
}

static void image_loader_load_pixels_p2(s_image_t *image, FILE *file)
{
	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			__u8 value;
			fscanf(file, "%hhu", &value);

			s_color_t color;
			color.m_r = value;
			color.m_g = value;
			color.m_b = value;

			s_vector2_t coords;
			coords.m_x = i;
			coords.m_y = j;
			image_set_pixel(coords, color, image);
		}
	}
}

static void image_loader_load_pixels_p3(s_image_t *image, FILE *file)
{
	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			s_color_t color;
			fscanf(file, "%hhu", &color.m_r);
			fscanf(file, "%hhu", &color.m_g);
			fscanf(file, "%hhu", &color.m_b);

			s_vector2_t coords;
			coords.m_x = i;
			coords.m_y = j;
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
			color.m_r = value;
			color.m_g = value;
			color.m_b = value;

			s_vector2_t coords;
			coords.m_x = i;
			coords.m_y = j;
			image_set_pixel(coords, color, image);
		}
	}
}

static void image_loader_load_pixels_p6(s_image_t *image, FILE *file)
{
	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			s_color_t color;
			fscanf(file, "%c", &color.m_r);
			fscanf(file, "%c", &color.m_g);
			fscanf(file, "%c", &color.m_b);

			s_vector2_t coords;
			coords.m_x = i;
			coords.m_y = j;
			image_set_pixel(coords, color, image);
		}
	}
}

static void image_loader_load_pixels(s_image_t *image, FILE *file)
{
	switch (image->m_image_data.m_format) {
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
	switch (image_data.m_format) {
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

	fprintf(file, "%zu %zu\n", image_data.m_width, image_data.m_height);
	fprintf(file, "%u\n", image_data.m_max_pixel_value);
}

static void image_loader_save_pixels_p2(s_image_t *image, FILE *file)
{
	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			s_vector2_t coords;
			coords.m_x = i;
			coords.m_y = j;

			__u8 value = image_get_pixel(coords, image).m_r;
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
			coords.m_x = i;
			coords.m_y = j;

			s_color_t color = image_get_pixel(coords, image);
			fprintf(file, "%hhu ", color.m_r);
			fprintf(file, "%hhu ", color.m_g);
			fprintf(file, "%hhu ", color.m_b);
		}
		fprintf(file, "\n");
	}
}

static void image_loader_save_pixels_p5(s_image_t *image, FILE *file)
{
	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			s_vector2_t coords;
			coords.m_x = i;
			coords.m_y = j;

			__u8 value = image_get_pixel(coords, image).m_r;
			fprintf(file, "%c", value);
		}
	}
}

static void image_loader_save_pixels_p6(s_image_t *image, FILE *file)
{
	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			s_vector2_t coords;
			coords.m_x = i;
			coords.m_y = j;

			s_color_t color = image_get_pixel(coords, image);
			fprintf(file, "%c", color.m_r);
			fprintf(file, "%c", color.m_g);
			fprintf(file, "%c", color.m_b);
		}
	}
}

static void image_loader_save_pixels(s_image_t *image, FILE *file)
{
	switch (image->m_image_data.m_format) {
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
