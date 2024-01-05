#include <app_manager.h>

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include <image_loader.h>
#include <image_workspace.h>
#include <operation_status_handler.h>
#include <input_handler.h>
#include <image_kernel_utils.h>
#include <utils.h>

static __u8 app_manager_tick(s_image_workspace_t *image_workspace);

static e_operation_status_t app_manager_load
		(u_command_data_t command_data, s_image_workspace_t *image_workspace);
static e_operation_status_t app_manager_select
		(u_command_data_t command_data, s_image_workspace_t *image_workspace);
static e_operation_status_t app_manager_select_all
		(u_command_data_t command_data, s_image_workspace_t *image_workspace);
static e_operation_status_t app_manager_histogram
		(u_command_data_t command_data, s_image_workspace_t *image_workspace);
static e_operation_status_t app_manager_equalize
		(u_command_data_t command_data, s_image_workspace_t *image_workspace);
static e_operation_status_t app_manager_rotate
		(u_command_data_t command_data, s_image_workspace_t *image_workspace);
static e_operation_status_t app_manager_crop
		(u_command_data_t command_data, s_image_workspace_t *image_workspace);
static e_operation_status_t app_manager_apply
		(u_command_data_t command_data,  s_image_workspace_t *image_workspace);
static e_operation_status_t app_manager_save
		(u_command_data_t command_data, s_image_workspace_t *image_workspace);
static e_operation_status_t app_manager_exit
		(u_command_data_t command_data, s_image_workspace_t *image_workspace);

static void app_manager_rotate_90_degrees
		(s_image_workspace_t *image_workspace);
static void app_manager_rotate_90_degrees_square
		(s_image_workspace_t *image_workspace);
static void app_manager_rotate_90_degrees_image
		(s_image_workspace_t *image_workspace);
static void app_manager_rotate_90_compute_rotated
		(s_vector2_t point_a, s_vector2_t point_b, s_image_t *out,
		 s_image_t *image);
static void app_manager_apply_kernel
		(double inverse_modifier, __s8 kernel[3][3],
		 s_image_workspace_t *image_workspace);

__u8 app_manager_main_loop(void)
{
	s_image_workspace_t image_workspace;
	image_workspace.m_image = NULL;

	__u8 is_running = app_manager_tick(&image_workspace);
	while (is_running)
		is_running = app_manager_tick(&image_workspace);

	return 0;
}

static __u8 app_manager_tick(s_image_workspace_t *image_workspace)
{
	u_command_data_t command_data = input_handler_read_command_data();

	e_operation_status_t return_status;
	switch (command_data.m_base.m_command_type) {
	case CT_LOAD:
		return_status = app_manager_load(command_data, image_workspace);
		break;
	case CT_SELECT:
		return_status = app_manager_select(command_data, image_workspace);
		break;
	case CT_SELECT_ALL:
		return_status = app_manager_select_all(command_data, image_workspace);
		break;
	case CT_HISTOGRAM:
		return_status = app_manager_histogram(command_data, image_workspace);
		break;
	case CT_EQUALIZE:
		return_status = app_manager_equalize(command_data, image_workspace);
		break;
	case CT_ROTATE:
		return_status = app_manager_rotate(command_data, image_workspace);
		break;
	case CT_CROP:
		return_status = app_manager_crop(command_data, image_workspace);
		break;
	case CT_APPLY:
		return_status = app_manager_apply(command_data, image_workspace);
		break;
	case CT_SAVE:
		return_status = app_manager_save(command_data, image_workspace);
		break;
	case CT_EXIT:
		return_status = app_manager_exit(command_data, image_workspace);
		break;
	default:
		return_status = OS_COMMAND_ERROR;
		break;
	}

	operation_status_handler_forward(command_data, return_status);
	if (command_data.m_base.m_command_type == CT_EXIT)
		return 0;

	return 1;
}

static e_operation_status_t app_manager_load
		(u_command_data_t command_data, s_image_workspace_t *image_workspace)
{
	if (command_data.m_load.m_command_type != CT_LOAD)
		return OS_COMMAND_ERROR;

	if (command_data.m_load.m_command_status == CST_INVALID)
		return OS_COMMAND_ERROR;

	if (image_workspace->m_image)
		image_delete(image_workspace->m_image);

	image_workspace->m_image =
			image_loader_load(command_data.m_load.m_file_path);

	if (!image_workspace->m_image)
		return OS_LOAD_FAILED;

	u_command_data_t select_all_command;
	select_all_command.m_select_all.m_command_type = CT_SELECT_ALL;
	select_all_command.m_select_all.m_command_status = CST_VALID;
	app_manager_select_all(select_all_command, image_workspace);

	return OS_LOAD_DONE;
}

static e_operation_status_t app_manager_select
		(u_command_data_t command_data, s_image_workspace_t *image_workspace)
{
	if (command_data.m_select.m_command_type != CT_SELECT)
		return OS_COMMAND_ERROR;

	if (!image_workspace->m_image)
		return OS_IMAGE_NOT_LOADED;

	if (command_data.m_select.m_command_status == CST_INVALID)
		return OS_COMMAND_ERROR;

	s_vector2_t point_a = command_data.m_select.m_point_a;
	s_vector2_t point_b = command_data.m_select.m_point_b;

	if ((size_t)point_b.m_x > image_get_height(image_workspace->m_image) ||
		(size_t)point_b.m_y > image_get_width(image_workspace->m_image) ||
		point_a.m_x < 0 || point_a.m_y < 0 ||
		point_a.m_x >= point_b.m_x || point_a.m_y >= point_b.m_y)
		return OS_SELECT_CUSTOM_FAILED;

	image_workspace->m_selection_point_a = point_a;
	image_workspace->m_selection_point_b = point_b;

	return OS_SELECT_CUSTOM_DONE;
}

static e_operation_status_t app_manager_select_all
		(u_command_data_t command_data, s_image_workspace_t *image_workspace)
{
	if (command_data.m_select_all.m_command_type != CT_SELECT_ALL)
		return OS_COMMAND_ERROR;

	if (!image_workspace->m_image)
		return OS_IMAGE_NOT_LOADED;

	if (command_data.m_select_all.m_command_status == CST_INVALID)
		return OS_COMMAND_ERROR;

	image_workspace->m_selection_point_a.m_x = 0;
	image_workspace->m_selection_point_a.m_y = 0;
	image_workspace->m_selection_point_b.m_x =
			image_get_height(image_workspace->m_image);
	image_workspace->m_selection_point_b.m_y =
			image_get_width(image_workspace->m_image);

	return OS_SELECT_ALL_DONE;
}

static e_operation_status_t app_manager_histogram
		(u_command_data_t command_data, s_image_workspace_t *image_workspace)
{
	if (command_data.m_histogram.m_command_type != CT_HISTOGRAM)
		return OS_COMMAND_ERROR;

	if (!image_workspace->m_image)
		return OS_IMAGE_NOT_LOADED;

	if (command_data.m_histogram.m_command_status == CST_INVALID)
		return OS_COMMAND_ERROR;

	s_vector2_t histogram_resolution = command_data.m_histogram.resolution;
	if (histogram_resolution.m_y % 2 || histogram_resolution.m_y < 2 ||
		histogram_resolution.m_y > 256)
		return OS_COMMAND_ERROR;

	if (image_workspace->m_image->m_image_data.m_format != IFT_P2 &&
		image_workspace->m_image->m_image_data.m_format != IFT_P5)
		return OS_IMAGE_NOT_GRAYSCALE;

	size_t *histogram = calloc(histogram_resolution.m_y, sizeof(size_t));
	s_image_t *image = image_workspace->m_image;

	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			s_vector2_t coords;
			coords.m_x = i;
			coords.m_y = j;

			__u8 value =  image_get_pixel(coords, image).m_r;

			__u8 bin_index = value / (256 / histogram_resolution.m_y);
			histogram[bin_index]++;
		}
	}

	size_t max_frequency = 0;
	for (size_t i = 0; i <  (size_t)histogram_resolution.m_y; i++)
		max_frequency = utils_max_int64(max_frequency, histogram[i]);

	for (size_t i = 0; i <  (size_t)histogram_resolution.m_y; i++)
		histogram[i] = (int)(((double)histogram[i] / max_frequency) *
						histogram_resolution.m_x);

	for (size_t i = 0; i <  (size_t)histogram_resolution.m_y; i++) {
		printf("%lu\t|\t", histogram[i]);
		for (size_t j = 0; j < histogram[i]; j++)
			printf("*");

		printf("\n");
	}

	free(histogram);

	return OS_DEFAULT_DONE;
}

static e_operation_status_t app_manager_equalize
		(u_command_data_t command_data, s_image_workspace_t *image_workspace)
{
	if (command_data.m_equalize.m_command_type != CT_EQUALIZE)
		return OS_COMMAND_ERROR;

	if (!image_workspace->m_image)
		return OS_IMAGE_NOT_LOADED;

	if (command_data.m_equalize.m_command_status == CST_INVALID)
		return OS_COMMAND_ERROR;

	if (image_workspace->m_image->m_image_data.m_format != IFT_P2 &&
		image_workspace->m_image->m_image_data.m_format != IFT_P5)
		return OS_IMAGE_NOT_GRAYSCALE;

	size_t histogram[IMAGE_MAX_PIXEL_VALUE];
	memset(histogram, 0, sizeof(histogram));

	s_image_t *image = image_workspace->m_image;

	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			s_vector2_t coords;
			coords.m_x = i;
			coords.m_y = j;

			__u8 value =  image_get_pixel(coords, image).m_r;
			histogram[value]++;
		}
	}

	size_t area = image_get_height(image) * image_get_width(image);
	__u8 equalized_values_link[IMAGE_MAX_PIXEL_VALUE];
	__u32 frv_sum = 0;

	for (size_t i = 0; i < IMAGE_MAX_PIXEL_VALUE; i++) {
		frv_sum += histogram[i];
		equalized_values_link[i] =
				utils_clamp(round(255 * ((double)frv_sum / area)), 0, 255);
	}

	for (size_t i = 0; i < image_get_height(image); i++) {
		for (size_t j = 0; j < image_get_width(image); j++) {
			s_vector2_t coords;
			coords.m_x = i;
			coords.m_y = j;

			__u8 value =  image_get_pixel(coords, image).m_r;
			__u8 new_value = equalized_values_link[value];

			s_color_t new_color;
			new_color.m_r = new_value;
			new_color.m_g = new_value;
			new_color.m_b = new_value;
			image_set_pixel(coords, new_color, image);
		}
	}

	return OS_EQUALIZE_DONE;
}

static void app_manager_rotate_90_compute_rotated
		(s_vector2_t point_a, s_vector2_t point_b, s_image_t *out,
		 s_image_t *image)
{
	size_t curr_i = 0;
	for (size_t i = point_a.m_x; i <  (size_t)point_b.m_x; i++) {
		size_t curr_j = 0;

		for (size_t j = point_a.m_y; j <  (size_t)point_b.m_y; j++) {
			s_vector2_t coords;
			coords.m_x = i;
			coords.m_y = j;
			s_color_t pixel = image_get_pixel(coords, image);

			s_vector2_t curr_coords;
			curr_coords.m_x = curr_j;
			curr_coords.m_y = image_get_width(out) - curr_i - 1;
			image_set_pixel(curr_coords, pixel, out);

			curr_j++;
		}
		curr_i++;
	}
}

static void app_manager_rotate_90_degrees_square
		(s_image_workspace_t *image_workspace)
{
	s_image_t *image = image_workspace->m_image;
	s_vector2_t point_a = image_workspace->m_selection_point_a;
	s_vector2_t point_b = image_workspace->m_selection_point_b;

	s_image_data_t new_image_data;
	new_image_data.m_format = image->m_image_data.m_format;
	new_image_data.m_height = point_b.m_y - point_a.m_y;
	new_image_data.m_width = point_b.m_x - point_a.m_x;
	new_image_data.m_max_pixel_value = image->m_image_data.m_max_pixel_value;

	s_image_t *new_image = image_new(new_image_data);
	app_manager_rotate_90_compute_rotated(point_a, point_b, new_image, image);

	size_t curr_i = 0;
	for (size_t i = point_a.m_x; i <  (size_t)point_b.m_x; i++) {
		size_t curr_j = 0;

		for (size_t j = point_a.m_y; j <  (size_t)point_b.m_y; j++) {
			s_vector2_t curr_coords;
			curr_coords.m_x = curr_i;
			curr_coords.m_y = curr_j;
			s_color_t pixel = image_get_pixel(curr_coords, new_image);

			s_vector2_t coords;
			coords.m_x = i;
			coords.m_y = j;
			image_set_pixel(coords, pixel, image);

			curr_j++;
		}
		curr_i++;
	}

	image_delete(new_image);
}

static void app_manager_rotate_90_degrees_image
		(s_image_workspace_t *image_workspace)
{
	s_image_t *image = image_workspace->m_image;
	s_vector2_t point_a = image_workspace->m_selection_point_a;
	s_vector2_t point_b = image_workspace->m_selection_point_b;

	s_image_data_t new_image_data;
	new_image_data.m_format = image->m_image_data.m_format;
	new_image_data.m_height = point_b.m_y - point_a.m_y;
	new_image_data.m_width = point_b.m_x - point_a.m_x;
	new_image_data.m_max_pixel_value = image->m_image_data.m_max_pixel_value;

	s_image_t *new_image = image_new(new_image_data);
	app_manager_rotate_90_compute_rotated(point_a, point_b, new_image, image);

	utils_swap_pointers((void **)&image, (void **)&new_image);
	image_delete(new_image);
	image_workspace->m_image = image;

	u_command_data_t select_all_command;
	select_all_command.m_select_all.m_command_type = CT_SELECT_ALL;
	select_all_command.m_select_all.m_command_status = CST_VALID;
	app_manager_select_all(select_all_command, image_workspace);
}

static void app_manager_rotate_90_degrees(s_image_workspace_t *image_workspace)
{
	s_vector2_t point_a = image_workspace->m_selection_point_a;
	s_vector2_t point_b = image_workspace->m_selection_point_b;

	size_t selection_height = point_b.m_x - point_a.m_x;
	size_t selection_width = point_b.m_y - point_a.m_y;

	if (selection_height == selection_width)
		app_manager_rotate_90_degrees_square(image_workspace);
	else
		app_manager_rotate_90_degrees_image(image_workspace);
}

static e_operation_status_t app_manager_rotate
		(u_command_data_t command_data, s_image_workspace_t *image_workspace)
{
	if (command_data.m_rotate.m_command_type != CT_ROTATE)
		return OS_COMMAND_ERROR;

	if (!image_workspace->m_image)
		return OS_IMAGE_NOT_LOADED;

	if (command_data.m_rotate.m_command_status == CST_INVALID)
		return OS_COMMAND_ERROR;

	s_image_t *image = image_workspace->m_image;
	s_vector2_t point_a = image_workspace->m_selection_point_a;
	s_vector2_t point_b = image_workspace->m_selection_point_b;

	size_t selection_height = point_b.m_x - point_a.m_x;
	size_t selection_width = point_b.m_y - point_a.m_y;

	if ((selection_height != image_get_height(image) &&
		 selection_width != image_get_width(image)) &&
		selection_height != selection_width)
		return OS_ROTATE_SELECTION_INVALID;

	if (command_data.m_rotate.angle % 90 || command_data.m_rotate.angle > 360 ||
		command_data.m_rotate.angle < -360)
		return OS_ROTATE_ANGLE_INVALID;

	switch (command_data.m_rotate.angle) {
	case 360:
		break;
	case -360:
		break;
	case 270:
		app_manager_rotate_90_degrees(image_workspace);
		app_manager_rotate_90_degrees(image_workspace);
		app_manager_rotate_90_degrees(image_workspace);
		break;
	case -270:
		app_manager_rotate_90_degrees(image_workspace);
		break;
	case 180:
		app_manager_rotate_90_degrees(image_workspace);
		app_manager_rotate_90_degrees(image_workspace);
		break;
	case -180:
		app_manager_rotate_90_degrees(image_workspace);
		app_manager_rotate_90_degrees(image_workspace);
		break;
	case 90:
		app_manager_rotate_90_degrees(image_workspace);
		break;
	case -90:
		app_manager_rotate_90_degrees(image_workspace);
		app_manager_rotate_90_degrees(image_workspace);
		app_manager_rotate_90_degrees(image_workspace);
		break;
	}

	return OS_ROTATE_DONE;
}

static e_operation_status_t app_manager_crop
		(u_command_data_t command_data, s_image_workspace_t *image_workspace)
{
	if (command_data.m_crop.m_command_type != CT_CROP)
		return OS_COMMAND_ERROR;

	if (!image_workspace->m_image)
		return OS_IMAGE_NOT_LOADED;

	if (command_data.m_crop.m_command_status == CST_INVALID)
		return OS_COMMAND_ERROR;

	s_image_t *image = image_workspace->m_image;
	s_vector2_t point_a = image_workspace->m_selection_point_a;
	s_vector2_t point_b = image_workspace->m_selection_point_b;

	s_image_data_t new_image_data;
	new_image_data.m_format = image->m_image_data.m_format;
	new_image_data.m_height = point_b.m_x - point_a.m_x;
	new_image_data.m_width = point_b.m_y - point_a.m_y;
	new_image_data.m_max_pixel_value = image->m_image_data.m_max_pixel_value;

	s_image_t *new_image = image_new(new_image_data);

	size_t curr_i = 0;
	for (size_t i = point_a.m_x; i < (size_t)point_b.m_x; i++) {
		size_t curr_j = 0;
		for (size_t j = point_a.m_y; j < (size_t)point_b.m_y; j++) {
			s_vector2_t coords;
			coords.m_x = i;
			coords.m_y = j;
			s_color_t pixel = image_get_pixel(coords, image);

			s_vector2_t curr_coords;
			curr_coords.m_x = curr_i;
			curr_coords.m_y = curr_j;
			image_set_pixel(curr_coords, pixel, new_image);
			curr_j++;
		}
		curr_i++;
	}

	utils_swap_pointers((void **)&image, (void **)&new_image);
	image_delete(new_image);
	image_workspace->m_image = image;

	u_command_data_t select_all_command;
	select_all_command.m_select_all.m_command_type = CT_SELECT_ALL;
	select_all_command.m_select_all.m_command_status = CST_VALID;
	app_manager_select_all(select_all_command, image_workspace);

	return OS_CROP_DONE;
}

static void app_manager_apply_kernel(double inverse_modifier, __s8 kernel[3][3],
									 s_image_workspace_t *image_workspace)
{
	s_image_t *image = image_workspace->m_image;
	s_vector2_t point_a = image_workspace->m_selection_point_a;
	s_vector2_t point_b = image_workspace->m_selection_point_b;

	s_image_data_t new_image_data;
	new_image_data.m_format = image->m_image_data.m_format;
	new_image_data.m_height = point_b.m_x - point_a.m_x;
	new_image_data.m_width = point_b.m_y - point_a.m_y;
	new_image_data.m_max_pixel_value = image->m_image_data.m_max_pixel_value;
	s_image_t *new_image = image_new(new_image_data);

	size_t curr_i = 0;
	for (size_t i = point_a.m_x; i < (size_t)point_b.m_x; i++) {
		size_t curr_j = 0;
		for (size_t j = point_a.m_y; j < (size_t)point_b.m_y; j++) {
			if (i <= 0 || j <= 0 || i >= image_get_height(image) - 1 ||
				j >= image_get_width(image) - 1)
				continue;

			__s16 sum_r = 0;
			__s16 sum_g = 0;
			__s16 sum_b = 0;
			for (__s8 k = -1; k <= 1; k++) {
				for (__s8 l = -1; l <= 1; l++) {
					s_vector2_t neighbour_coords;
					neighbour_coords.m_x = i + k;
					neighbour_coords.m_y = j + l;
					if (!image_coords_in_bounds(neighbour_coords, image))
						continue;

					s_color_t neighbour_pixel = image_get_pixel
							(neighbour_coords, image);
					sum_r += kernel[k + 1][l + 1] * neighbour_pixel.m_r;
					sum_g += kernel[k + 1][l + 1] * neighbour_pixel.m_g;
					sum_b += kernel[k + 1][l + 1] * neighbour_pixel.m_b;
				}
			}

			s_color_t new_pixel;
			new_pixel.m_r =
					utils_clamp((double)sum_r / inverse_modifier, 0, 255);
			new_pixel.m_g =
					utils_clamp((double)sum_g / inverse_modifier, 0, 255);
			new_pixel.m_b =
					utils_clamp((double)sum_b / inverse_modifier, 0, 255);
			s_vector2_t curr_coords;
			curr_coords.m_x = curr_i;
			curr_coords.m_y = curr_j;
			image_set_pixel(curr_coords, new_pixel, new_image);
			curr_j++;
		}
		curr_i++;
	}

	curr_i = 0;
	for (size_t i = point_a.m_x; i < (size_t)point_b.m_x; i++) {
		size_t curr_j = 0;
		for (size_t j = point_a.m_y; j < (size_t)point_b.m_y; j++) {
			if (i <= 0 || j <= 0 || i >= image_get_height(image) - 1 ||
				j >= image_get_width(image) - 1)
				continue;

			s_vector2_t curr_coords;
			curr_coords.m_x = curr_i;
			curr_coords.m_y = curr_j;
			s_color_t new_pixel = image_get_pixel(curr_coords, new_image);

			s_vector2_t coords;
			coords.m_x = i;
			coords.m_y = j;
			image_set_pixel(coords, new_pixel, image);

			curr_j++;
		}
		curr_i++;
	}
	image_delete(new_image);
}

static e_operation_status_t app_manager_apply
		(u_command_data_t command_data, s_image_workspace_t *image_workspace)
{
	if (command_data.m_apply.m_command_type != CT_APPLY)
		return OS_COMMAND_ERROR;

	if (!image_workspace->m_image)
		return OS_IMAGE_NOT_LOADED;

	if (command_data.m_apply.m_command_status == CST_INVALID)
		return OS_COMMAND_ERROR;

	if (command_data.m_apply.image_kernel_type == IKT_NONE)
		return OS_APPLY_PARAMETER_INVALID;

	if (image_workspace->m_image->m_image_data.m_format == IFT_P2 ||
		image_workspace->m_image->m_image_data.m_format == IFT_P5)
		return OS_APPLY_GRAYSCALE_IMAGE;

	__s8 kernel[3][3];
	double inverse_modifier;

	switch (command_data.m_apply.image_kernel_type) {
	case IKT_EDGE:
		image_kernel_utils_edge(&inverse_modifier, kernel);
		app_manager_apply_kernel(inverse_modifier, kernel, image_workspace);
		break;
	case IKT_SHARPEN:
		image_kernel_utils_sharpen(&inverse_modifier, kernel);
		app_manager_apply_kernel(inverse_modifier, kernel, image_workspace);
		break;
	case IKT_BOX_BLUR:
		image_kernel_utils_box_blur(&inverse_modifier, kernel);
		app_manager_apply_kernel(inverse_modifier, kernel, image_workspace);
		break;
	case IKT_GAUSSIAN_BLUR:
		image_kernel_utils_gaussian_blur(&inverse_modifier, kernel);
		app_manager_apply_kernel(inverse_modifier, kernel, image_workspace);
		break;
	default:
		return OS_APPLY_PARAMETER_INVALID;
	}

	return OS_APPLY_DONE;
}

static e_operation_status_t app_manager_save
		(u_command_data_t command_data, s_image_workspace_t *image_workspace)
{
	if (command_data.m_save.m_command_type != CT_SAVE)
		return OS_COMMAND_ERROR;

	if (!image_workspace->m_image)
		return OS_IMAGE_NOT_LOADED;

	if (command_data.m_save.m_command_status == CST_INVALID)
		return OS_COMMAND_ERROR;

	s_image_data_t *m_image_data = &image_workspace->m_image->m_image_data;
	if (command_data.m_save.m_save_as_ascii) {
		if (m_image_data->m_format == IFT_P5)
			m_image_data->m_format = IFT_P2;
		else if (m_image_data->m_format == IFT_P6)
			m_image_data->m_format = IFT_P3;
	} else {
		if (m_image_data->m_format == IFT_P2)
			m_image_data->m_format = IFT_P5;
		else if (m_image_data->m_format == IFT_P3)
			m_image_data->m_format = IFT_P6;
	}

	image_loader_save(image_workspace->m_image,
					  command_data.m_save.m_file_path);
	return OS_SAVE_DONE;
}

static e_operation_status_t app_manager_exit
		(u_command_data_t command_data, s_image_workspace_t *image_workspace)
{
	if (command_data.m_exit.m_command_type != CT_EXIT)
		return OS_COMMAND_ERROR;

	if (!image_workspace->m_image)
		return OS_IMAGE_NOT_LOADED;

	if (command_data.m_exit.m_command_status == CST_INVALID)
		return OS_COMMAND_ERROR;

	image_delete(image_workspace->m_image);
	return OS_DEFAULT_DONE;
}
