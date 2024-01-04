#include <status_handler.h>

#include <stdio.h>

static void status_handler_load_done(command_data_t command)
{
	printf("Loaded %s\n", command.load.file_path);
}

static void status_handler_load_failed(command_data_t command)
{
	printf("Failed to load %s\n", command.load.file_path);
}

static void status_handler_image_not_loaded(void)
{
	printf("No image loaded\n");
}

static void status_handler_select_custom_done(command_data_t command)
{
	vector2_t point_a = command.select.point_a;
	vector2_t point_b = command.select.point_b;
	printf("Selected %lld %lld %lld %lld\n",
		   point_a.y, point_a.x, point_b.y, point_b.x);
}

static void status_handler_select_custom_failed(void)
{
	printf("Invalid set of coordinates\n");
}

static void status_handler_select_all_done(void)
{
	printf("Selected ALL\n");
}

static void status_handler_rotate_done(command_data_t command)
{
	printf("Rotated %d\n", command.rotate.angle);
}

static void status_handler_rotate_selection_invalid(void)
{
	printf("The selection must be square\n");
}

static void status_handler_rotate_angle_invalid(void)
{
	printf("Unsupported rotation angle\n");
}

static void status_handler_equalize_done(void)
{
	printf("Equalize done\n");
}

static void status_handler_equalize_format_invalid(void)
{
	printf("Black and white image needed\n");
}

static void status_handler_crop_done(void)
{
	printf("Image cropped\n");
}

static void status_handler_apply_done(command_data_t command)
{
	image_kernel_type_t image_kernel_type = command.apply.image_kernel_type;

	char image_kernel_type_name[25];
	image_kernel_type_get_name(image_kernel_type_name, image_kernel_type);

	switch (image_kernel_type) {
	case IKT_EDGE:
		printf("APPLY %s done\n", image_kernel_type_name);
		break;
	case IKT_SHARPEN:
		printf("APPLY %s done\n", image_kernel_type_name);
		break;
	case IKT_BOX_BLUR:
		printf("APPLY %s done\n", image_kernel_type_name);
		break;
	case IKT_GAUSSIAN_BLUR:
		printf("APPLY %s done\n", image_kernel_type_name);
		break;
	default:
		break;
	}
}

static void status_handler_apply_grayscale_image(void)
{
	printf("Easy, Charlie Chaplin\n");
}

static void status_handler_apply_parameter_invalid(void)
{
	printf("APPLY parameter invalid\n");
}

static void status_handler_save_done(command_data_t command)
{
	printf("Saved %s\n", command.save.file_path);
}

static void status_handler_histogram_parameter_invalid(void)
{
	printf("Invalid set of parameters\n");
}

static void status_handler_command_error(void)
{
	printf("Invalid command\n");
}

void status_handler_forward(command_data_t command, status_type_t status)
{
	switch (status) {
	case ST_DEFAULT_DONE:
		break;
	case ST_IMAGE_NOT_LOADED:
		status_handler_image_not_loaded();
		break;
	case ST_IMAGE_NOT_GRAYSCALE:
		status_handler_equalize_format_invalid();
		break;
	case ST_LOAD_DONE:
		status_handler_load_done(command);
		break;
	case ST_LOAD_FAILED:
		status_handler_load_failed(command);
		break;
	case ST_SELECT_CUSTOM_DONE:
		status_handler_select_custom_done(command);
		break;
	case ST_SELECT_CUSTOM_FAILED:
		status_handler_select_custom_failed();
		break;
	case ST_SELECT_ALL_DONE:
		status_handler_select_all_done();
		break;
	case ST_ROTATE_DONE:
		status_handler_rotate_done(command);
		break;
	case ST_ROTATE_SELECTION_INVALID:
		status_handler_rotate_selection_invalid();
		break;
	case ST_ROTATE_ANGLE_INVALID:
		status_handler_rotate_angle_invalid();
		break;
	case ST_EQUALIZE_DONE:
		status_handler_equalize_done();
		break;
	case ST_CROP_DONE:
		status_handler_crop_done();
		break;
	case ST_APPLY_DONE:
		status_handler_apply_done(command);
		break;
	case ST_APPLY_GRAYSCALE_IMAGE:
		status_handler_apply_grayscale_image();
		break;
	case ST_APPLY_PARAMETER_INVALID:
		status_handler_apply_parameter_invalid();
		break;
	case ST_HISTOGRAM_PARAMETER_INVALID:
		status_handler_histogram_parameter_invalid();
		break;
	case ST_SAVE_DONE:
		status_handler_save_done(command);
		break;
	case ST_COMMAND_ERROR:
		status_handler_command_error();
	default:
		break;
	}
}
