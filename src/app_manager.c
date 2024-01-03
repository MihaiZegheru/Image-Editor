#include <app_manager.h>

#include <image_loader.h>
#include <inttypes.h>
#include <input_handler.h>
#include <image_workspace.h>
#include <string.h>
#include <utils.h>
#include <stdlib.h>
#include <math.h>
#include <kernel_utils.h>
#include <status_handler.h>

status_type_t app_manager_load(command_data_t command_data,
                               image_workspace_t *image_workspace)
{
    if (command_data.load.command_type != CT_LOAD) {
        return ST_COMMAND_ERROR;
    }

    image_workspace->image = image_loader_load(command_data.load.file_path);
    if (!image_workspace->image) {
        return ST_LOAD_FAILED;
    }

    command_data_t select_all_command;
    select_all_command.select_all.command_type = CT_SELECT_ALL;
    app_manager_select_all(select_all_command, image_workspace);

    return ST_LOAD_DONE;
}

status_type_t app_manager_select(command_data_t command_data,
                                 image_workspace_t *image_workspace)
{
    if (command_data.select.command_type != CT_SELECT) {
        return ST_COMMAND_ERROR;
    }

    if (!image_workspace->image) {
        return ST_IMAGE_NOT_LOADED;
    }

    vector2_t point_a = command_data.select.point_a;
    vector2_t point_b = command_data.select.point_b;

    if (point_b.x > image_get_height(image_workspace->image) ||
        point_b.y > image_get_width(image_workspace->image) ||
        point_a.x >= point_b.x || point_a.y >= point_b.y) {
            return ST_SELECT_CUSTOM_FAILED;
    }

    image_workspace->selection_point_a = point_a;
    image_workspace->selection_point_b = point_b;

    return ST_SELECT_CUSTOM_DONE;
}

status_type_t app_manager_select_all(command_data_t command_data,
                                     image_workspace_t *image_workspace)
{
    if (command_data.select_all.command_type != CT_SELECT_ALL) {
        return ST_COMMAND_ERROR;
    }

    if (!image_workspace->image) {
        return ST_IMAGE_NOT_LOADED;
    }

    image_workspace->selection_point_a.x = 0;
    image_workspace->selection_point_a.y = 0;
    image_workspace->selection_point_b.x =
            image_get_height(image_workspace->image);
    image_workspace->selection_point_b.y =
            image_get_width(image_workspace->image);

    return ST_SELECT_ALL_DONE;
}

status_type_t app_manager_histogram(command_data_t command_data,
                                    image_workspace_t *image_workspace)
{
    if (command_data.histogram.command_type != CT_HISTOGRAM) {
        return ST_COMMAND_ERROR;
    }

    vector2_t histogram_resolution = command_data.histogram.resolution;

    if (image_workspace->image->image_data.format != IFT_P2 &&
        image_workspace->image->image_data.format != IFT_P5) {
        return ST_HISTOGRAM_GRAYSCALE_INVALID;
    }

    size_t *histogram = calloc(histogram_resolution.y, sizeof(size_t));
    image_t *image = image_workspace->image;

    for (size_t i = 0; i < image_get_height(image); i++) {
        for (size_t j = 0; j < image_get_width(image); j++) {
            vector2_t coords;
            coords.x = i;
            coords.y = j;

            uint8_t value =  image_get_pixel(coords, image).r;

            uint8_t bin_index = value / (256 / histogram_resolution.y);
            histogram[bin_index]++;
        }
    }

    size_t max_frequency = 0;
    for (size_t i = 0; i < histogram_resolution.y; i++) {
        max_frequency = utils_max_int64(max_frequency, histogram[i]);
    }

    for (size_t i = 0; i < histogram_resolution.y; i++) {
        histogram[i] = (int)(((double)histogram[i] / max_frequency) * histogram_resolution.x);
    }

    for (size_t i = 0; i < histogram_resolution.x; i++) {
        printf("%"SCNu64" |\t", histogram[i]);
        for (size_t j = 0; j < histogram[i]; j++) {
            printf("*");
        }
        printf("\n");
    }

    free(histogram);

    return ST_HISTOGRAM_DONE;
}

status_type_t app_manager_equalize(command_data_t command_data,
                                   image_workspace_t *image_workspace)
{
    if (command_data.equalize.command_type != CT_EQUALIZE) {
        return ST_COMMAND_ERROR;
    }

    if (image_workspace->image->image_data.format != IFT_P2 &&
        image_workspace->image->image_data.format != IFT_P5) {
        return ST_EQUALIZE_FORMAT_INVALID;
    }
    
    const size_t RANGE = UINT8_MAX + 1;
    size_t histogram[RANGE];
    memset(histogram, 0, sizeof(histogram));

    image_t *image = image_workspace->image;

    for (size_t i = 0; i < image_get_height(image); i++) {
        for (size_t j = 0; j < image_get_width(image); j++) {
            vector2_t coords;
            coords.x = i;
            coords.y = j;

            uint8_t value =  image_get_pixel(coords, image).r;
            histogram[value]++;
        }
    }

    size_t area = image_get_height(image) * image_get_width(image);
    uint8_t equalized_values_link[RANGE];
    uint32_t frv_sum = 0;

    for (size_t i = 0; i < RANGE; i++) {
        frv_sum += histogram[i];
        equalized_values_link[i] = utils_clamp(round(255 * ((double)frv_sum / area)), 0, 255);
    }

    for (size_t i = 0; i < image_get_height(image); i++) {
        for (size_t j = 0; j < image_get_width(image); j++) {
            vector2_t coords;
            coords.x = i;
            coords.y = j;

            uint8_t value =  image_get_pixel(coords, image).r;
            uint8_t new_value = equalized_values_link[value];

            color_t new_color;
            new_color.r = new_value;
            new_color.g = new_value;
            new_color.b = new_value;
            image_set_pixel(coords, new_color, image);
        }
    }

    return ST_EQUALIZE_DONE;
}

// TO DO: ADD separate function for selection rotation

static void app_manager_rotate_90_degrees_square(image_workspace_t *image_workspace)
{
    image_t *image = image_workspace->image;
    vector2_t point_a = image_workspace->selection_point_a;
    vector2_t point_b = image_workspace->selection_point_b;

    image_data_t new_image_data;
    new_image_data.format = image->image_data.format;
    new_image_data.height = point_b.y - point_a.y;
    new_image_data.width = point_b.x - point_a.x;
    new_image_data.max_pixel_value = image->image_data.max_pixel_value;

    image_t *new_image = image_new(new_image_data);

    size_t curr_i = 0;
    for (size_t i = point_a.x; i < point_b.x; i++) {
        size_t curr_j = 0;

        for (size_t j = point_a.y; j < point_b.y; j++) {
            vector2_t coords;
            coords.x = i;
            coords.y = j;
            color_t pixel = image_get_pixel(coords, image);

            vector2_t curr_coords;
            curr_coords.x = curr_j;
            curr_coords.y = new_image_data.width - curr_i - 1;
            image_set_pixel(curr_coords, pixel, new_image);

            curr_j++;
        }
        curr_i++;
    }

    curr_i = 0;
    for (size_t i = point_a.x; i < point_b.x; i++) {
        size_t curr_j = 0;

        for (size_t j = point_a.y; j < point_b.y; j++) {
            vector2_t curr_coords;
            curr_coords.x = curr_i;
            curr_coords.y = curr_j;
            color_t pixel = image_get_pixel(curr_coords, new_image);

            vector2_t coords;
            coords.x = i;
            coords.y = j;
            image_set_pixel(coords, pixel, image);

            curr_j++;
        }
        curr_i++;
    }

    image_delete(new_image);
}

static void app_manager_rotate_90_degrees_image(image_workspace_t *image_workspace)
{
    image_t *image = image_workspace->image;
    vector2_t point_a = image_workspace->selection_point_a;
    vector2_t point_b = image_workspace->selection_point_b;

    image_data_t new_image_data;
    new_image_data.format = image->image_data.format;
    new_image_data.height = point_b.y - point_a.y;
    new_image_data.width = point_b.x - point_a.x;
    new_image_data.max_pixel_value = image->image_data.max_pixel_value;

    image_t *new_image = image_new(new_image_data);

    size_t curr_i = 0;
    for (size_t i = point_a.x; i < point_b.x; i++) {
        size_t curr_j = 0;

        for (size_t j = point_a.y; j < point_b.y; j++) {
            vector2_t coords;
            coords.x = i;
            coords.y = j;
            color_t pixel = image_get_pixel(coords, image);

            vector2_t curr_coords;
            curr_coords.x = curr_j;
            curr_coords.y = new_image_data.width- curr_i - 1;
            image_set_pixel(curr_coords, pixel, new_image);

            curr_j++;
        }
        curr_i++;
    }
    utils_swap_pointers((void **)&image, (void **)&new_image);
    image_delete(new_image);
    image_workspace->image = image;

    command_data_t select_all_command;
    select_all_command.select_all.command_type = CT_SELECT_ALL;
    app_manager_select_all(select_all_command, image_workspace);
}

static void app_manager_rotate_90_degrees(image_workspace_t *image_workspace)
{
    vector2_t point_a = image_workspace->selection_point_a;
    vector2_t point_b = image_workspace->selection_point_b;

    size_t selection_height = point_b.x - point_a.x;
    size_t selection_width = point_b.y - point_a.y;

    if (selection_height == selection_width) {
        app_manager_rotate_90_degrees_square(image_workspace);
    } else {
        app_manager_rotate_90_degrees_image(image_workspace);
    }
}

status_type_t app_manager_rotate(command_data_t command_data,
                                 image_workspace_t *image_workspace)
{
    if (command_data.rotate.command_type != CT_ROTATE) {
        return ST_COMMAND_ERROR;
    }

    if (!image_workspace->image) {
        return ST_IMAGE_NOT_LOADED;
    }

    image_t *image = image_workspace->image;
    vector2_t point_a = image_workspace->selection_point_a;
    vector2_t point_b = image_workspace->selection_point_b;

    size_t selection_height = point_b.x - point_a.x;
    size_t selection_width = point_b.y - point_a.y;

    if ((selection_height != image_get_height(image) &&
        selection_width != image_get_width(image)) &&
        selection_height != selection_width) {
        return ST_ROTATE_SELECTION_INVALID;
    }

    if (command_data.rotate.angle % 90 || command_data.rotate.angle > 360 ||
        command_data.rotate.angle < -360) {
        return ST_ROTATE_ANGLE_INVALID;
    }

    switch (command_data.rotate.angle) {
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

    return ST_ROTATE_DONE;
}

status_type_t app_manager_crop(command_data_t command_data,
                               image_workspace_t *image_workspace)
{
    if (command_data.crop.command_type != CT_CROP) {
        return ST_COMMAND_ERROR;
    }

    if (!image_workspace->image) {
        return ST_IMAGE_NOT_LOADED;
    }

    image_t *image = image_workspace->image;
    vector2_t point_a = image_workspace->selection_point_a;
    vector2_t point_b = image_workspace->selection_point_b;

    image_data_t new_image_data;
    new_image_data.format = image->image_data.format;
    new_image_data.height = point_b.x - point_a.x;
    new_image_data.width = point_b.y - point_a.y;
    new_image_data.max_pixel_value = image->image_data.max_pixel_value;

    image_t *new_image = image_new(new_image_data);

    size_t curr_i = 0;
    for (size_t i = point_a.x; i < point_b.x; i++) {
        size_t curr_j = 0;
        for (size_t j = point_a.y; j < point_b.y; j++) {
            vector2_t coords;
            coords.x = i;
            coords.y = j;
            color_t pixel = image_get_pixel(coords, image);

            vector2_t curr_coords;
            curr_coords.x = curr_i;
            curr_coords.y = curr_j;
            image_set_pixel(curr_coords, pixel, new_image);
            curr_j++;
        }
        curr_i++;
    }

    utils_swap_pointers((void **)&image, (void **)&new_image);
    image_delete(new_image);
    image_workspace->image = image;

    return ST_CROP_DONE;
}

static void app_manager_apply_kernel(
        double inverse_modifier, int8_t kernel[3][3],
        image_workspace_t *image_workspace)
{
    image_t *image = image_workspace->image;
    vector2_t point_a = image_workspace->selection_point_a;
    vector2_t point_b = image_workspace->selection_point_b;

    image_data_t new_image_data;
    new_image_data.format = image->image_data.format;
    new_image_data.height = point_b.x - point_a.x;
    new_image_data.width = point_b.y - point_a.y;
    new_image_data.max_pixel_value = image->image_data.max_pixel_value;

    image_t *new_image = image_new(new_image_data);

    size_t curr_i = 0;
    for (size_t i = point_a.x; i < point_b.x; i++) {
        size_t curr_j = 0;

        for (size_t j = point_a.y; j < point_b.y; j++) {
            if (i <= 0 || j <= 0 || i >= image_get_height(image) - 1 ||
                j >= image_get_width(image) - 1) {
                continue;
            }

            int16_t sum_r = 0;
            int16_t sum_g = 0;
            int16_t sum_b = 0;
            for (int8_t k = -1; k <= 1; k++) {
                for (int8_t l = -1; l <= 1; l++) {
                    vector2_t neighbour_coords;
                    neighbour_coords.x = i + k;
                    neighbour_coords.y = j + l;
                    if (!image_coords_in_bounds(neighbour_coords, image)) {
                        continue;
                    }

                    color_t neighbour_pixel = image_get_pixel(neighbour_coords,
                                                              image);
                    sum_r += kernel[k + 1][l + 1] * neighbour_pixel.r;
                    sum_g += kernel[k + 1][l + 1] * neighbour_pixel.g;
                    sum_b += kernel[k + 1][l + 1] * neighbour_pixel.b;
                }
            }

            color_t new_pixel;
            new_pixel.r = utils_clamp((double)sum_r / inverse_modifier, 0, 255);
            new_pixel.g = utils_clamp((double)sum_g / inverse_modifier, 0, 255);
            new_pixel.b = utils_clamp((double)sum_b / inverse_modifier, 0, 255);

            vector2_t curr_coords;
            curr_coords.x = curr_i;
            curr_coords.y = curr_j;
            image_set_pixel(curr_coords, new_pixel, new_image);
            curr_j++;
        }
        curr_i++;
    }

    curr_i = 0;
    for (size_t i = point_a.x; i < point_b.x; i++) {
        size_t curr_j = 0;

        for (size_t j = point_a.y; j < point_b.y; j++) {
            if (i <= 0 || j <= 0 || i >= image_get_height(image) - 1 ||
                j >= image_get_width(image) - 1) {
                continue;
            }
            vector2_t curr_coords;
            curr_coords.x = curr_i;
            curr_coords.y = curr_j;
            color_t new_pixel = image_get_pixel(curr_coords, new_image);

            vector2_t coords;
            coords.x = i;
            coords.y = j;
            image_set_pixel(coords, new_pixel, image);

            curr_j++;
        }
        curr_i++;
    }

    image_delete(new_image);
}

status_type_t app_manager_apply(command_data_t command_data,
                               image_workspace_t *image_workspace)
{
    if (command_data.apply.command_type != CT_APPLY) {
        return ST_COMMAND_ERROR;
    }

    if (!image_workspace->image) {
        return ST_IMAGE_NOT_LOADED;
    }

    if (image_workspace->image->image_data.format == IFT_P2 &&
        image_workspace->image->image_data.format == IFT_P5) {
        return ST_APPLY_GRAYSCALE_IMAGE;
    }

    int8_t kernel[3][3];
    double inverse_modifier;

    switch (command_data.apply.image_kernel_type) {
        case IKT_EDGE:
            kernel_utils_edge(&inverse_modifier, kernel);
            app_manager_apply_kernel(inverse_modifier, kernel,
                                            image_workspace);
            break;
        case IKT_SHARPEN:
            kernel_utils_sharpen(&inverse_modifier, kernel);
            app_manager_apply_kernel(inverse_modifier, kernel,
                                            image_workspace);
            break;
        case IKT_BOX_BLUR:
            kernel_utils_box_blur(&inverse_modifier, kernel);
            app_manager_apply_kernel(inverse_modifier, kernel,
                                            image_workspace);
            break;
        case IKT_GAUSSIAN_BLUR:
            kernel_utils_gaussian_blur(&inverse_modifier, kernel);
            app_manager_apply_kernel(inverse_modifier, kernel,
                                            image_workspace);
            break;
        default:
            return ST_APPLY_PARAMETER_INVALID;
            break;
    }

    return ST_APPLY_DONE;
}

status_type_t app_manager_save(command_data_t command_data,
                               image_workspace_t *image_workspace)
{
    if (command_data.save.command_type != CT_SAVE) {
        return ST_COMMAND_ERROR;
    }

    if (!image_workspace->image) {
        return ST_IMAGE_NOT_LOADED;
    }

    image_loader_save(image_workspace->image, command_data.save.file_path);
    return ST_SAVE_DONE;
}

status_type_t app_manager_exit(command_data_t command_data,
                               image_workspace_t *image_workspace)
{
    if (command_data.exit.command_type != CT_EXIT) {
        return ST_COMMAND_ERROR;
    }
    image_delete(image_workspace->image);
    return ST_EXIT;
}

uint8_t app_manager_tick(image_workspace_t *image_workspace)
{
    command_data_t command_data = input_handler_read_command_data();

    status_type_t return_status;
    switch (command_data.base.command_type) {
        case CT_LOAD:
            return_status = app_manager_load(command_data, image_workspace);
            break;
        case CT_SELECT:
            return_status = app_manager_select(command_data, image_workspace);
            break;
        case CT_SELECT_ALL:
            return_status = app_manager_select_all(command_data,
                                                   image_workspace);
            break;
        case CT_HISTOGRAM:
            return_status = app_manager_histogram(command_data,
                                                  image_workspace);
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
            // TO DO: EXIT bug from ASCII check
            return_status = app_manager_exit(command_data, image_workspace);
            return 1;
            break;
        default:
            break;
    }

    status_handler_forward(command_data, return_status);

    return 0;
}

uint8_t app_manager_main_loop()
{
    image_workspace_t image_workspace;
    image_workspace.image = NULL;
    while (!app_manager_tick(&image_workspace));

    return 0;
}
