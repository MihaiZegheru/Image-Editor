#include <status_handler.h>

#include <stdio.h>
#include <inttypes.h>

static void status_handler_load_done(command_data_t command)
{
    printf("Loaded %s\n", command.load.file_path);
}

static void status_handler_load_failed(command_data_t command)
{
    printf("Failed to load %s\n", command.load.file_path);
}

static void status_handler_image_not_loaded()
{
    printf("No image loaded\n");
}

static void status_handler_select_custom_done(command_data_t command)
{
    vector2_t point_a = command.select.point_a;
    vector2_t point_b = command.select.point_b;
    printf("Selected %zu %zu %zu %zu\n", point_a.y, point_a.x, point_b.y,
           point_b.x);
}

static void status_handler_select_custom_failed()
{
    printf("Invalid set of coordinates\n");
}

static void status_handler_select_all_done()
{
    printf("Selected ALL\n");
}

static void status_handler_rotate_done(command_data_t command)
{
    printf("Rotated %"SCNd16"\n", command.rotate.angle);
}

static void status_handler_rotate_selection_invalid()
{
    printf("The selection must be square\n");
}

static void status_handler_rotate_angle_invalid()
{
    printf("Unsupported rotation angle\n");
}

static void status_handler_equalize_done()
{
    printf("Equalization done\n");
}

static void status_handler_equalize_format_invalid()
{
    printf("Black and white image needed\n");
}

void status_handler_forward(command_data_t command, status_type_t status)
{
    switch (status) {
        case ST_LOAD_DONE:
            status_handler_load_done(command);
            break;
        case ST_LOAD_FAILED:
            status_handler_load_failed(command);
            break;
        case ST_IMAGE_NOT_LOADED:
            status_handler_image_not_loaded();
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
        case ST_EQUALIZE_FORMAT_INVALID:
            status_handler_equalize_format_invalid();
            break;
    }
}