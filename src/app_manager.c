#include <app_manager.h>

#include <image_loader.h>
#include <inttypes.h>
#include <input_handler.h>

static uint8_t app_manager_load()
{
    char file_path[100];
    input_handler_read_string(file_path);

    image_t image = image_loader_load(file_path);

    for (size_t i = 0; i < image_get_height(&image); i++) {
        for (size_t j = 0; j < image_get_width(&image); j++) {
            printf("%"SCNu8" ""%"SCNu8" ""%"SCNu8" ", image_get_pixel(i, j, &image).r, image_get_pixel(i, j, &image).g,
                image_get_pixel(i, j, &image).b);
        }
        printf("\n");
    }
    image_delete(&image);

    return 0;
}

uint8_t app_manager_tick()
{
    command_type_t command_type = input_handler_read_command();
    switch (command_type) {
        case CT_LOAD:
            return app_manager_load();
            break;
        case CT_SELECT:
            break;
        case CT_HISTOGRAM:
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
