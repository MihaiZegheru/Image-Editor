#include <app_manager.h>

#include <image_loader.h>
#include <inttypes.h>
#include <input_handler.h>
#include <image_workspace.h>
#include <string.h>
#include <utils.h>
#include <stdlib.h>

error_type_t app_manager_load(image_workspace_t *image_workspace)
{
    char file_path[100];
    input_handler_read_string(file_path);
    image_workspace->image = image_loader_load(file_path);
    app_manager_select_all(image_workspace);

    return 0;
}

error_type_t app_manager_select(image_workspace_t *image_workspace)
{
    char input[100];
    input_handler_read_string(input);

    if (!strcmp(input, "ALL")) {
         app_manager_select_all(image_workspace);
    } else {
        image_workspace->selection_point_a.x =
                utils_string_to_int64(input);
        input_handler_read_size(&image_workspace->selection_point_a.y);

        input_handler_read_vector2(&image_workspace->selection_point_b);
    }

    return 0;
}

error_type_t app_manager_select_all(image_workspace_t *image_workspace)
{
    image_workspace->selection_point_a.x = 0;
    image_workspace->selection_point_a.y = 0;
    image_workspace->selection_point_b.x = image_workspace->
            image->image_data.width;
    image_workspace->selection_point_b.y = image_workspace->
            image->image_data.height;

    return 0;
}

error_type_t app_manager_histogram(image_workspace_t *image_workspace)
{
    vector2_t histogram_resolution;
    input_handler_read_vector2(&histogram_resolution);

    if (image_workspace->image->image_data.format != IFT_P2 &&
        image_workspace->image->image_data.format != IFT_P5) {
        return ET_IMAGE_NOT_GRAYSCALE;
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

    return 0;
}

uint8_t app_manager_tick(image_workspace_t *image_workspace)
{
    command_type_t command_type = input_handler_read_command();
    switch (command_type) {
        case CT_LOAD:
            return app_manager_load(image_workspace);
            break;
        case CT_SELECT:
            return app_manager_select(image_workspace);
            break;
        case CT_HISTOGRAM:
            return app_manager_histogram(image_workspace);
            break;
        case CT_EQUALIZE:
            break;
        case CT_ROTATE:
            break;
        case CT_CROP:
            break;
        case CT_APPLY:
            break;
        case CT_SAVE:
            break;
        case CT_EXIT:
            return 1;
            break;
        default:
            break;
    }

    return 0;
}

uint8_t app_manager_main_loop()
{
    image_workspace_t image_workspace;
    while (!app_manager_tick(&image_workspace));

    return 0;
}
