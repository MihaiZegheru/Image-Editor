#ifndef APP_MANAGER_H__
#define APP_MANAGER_H__

#include <inttypes.h>

#include <image_workspace.h>
#include <status_types.h>
#include <command_data.h>

uint8_t app_manager_main_loop();
uint8_t app_manager_tick();

status_type_t app_manager_load(command_data_t command_data,
                               image_workspace_t *image_workspace);
status_type_t app_manager_select(command_data_t command_data,
                                 image_workspace_t *image_workspace);
status_type_t app_manager_select_all(command_data_t command_data,
                                     image_workspace_t *image_workspace);
status_type_t app_manager_histogram(command_data_t command_data,
                                    image_workspace_t *image_workspace);
status_type_t app_manager_equalize(command_data_t command_data,
                                   image_workspace_t *image_workspace);
status_type_t app_manager_rotate(command_data_t command_data,
                                 image_workspace_t *image_workspace);
status_type_t app_manager_crop(command_data_t command_data,
                               image_workspace_t *image_workspace);
status_type_t app_manager_save(command_data_t command_data,
                               image_workspace_t *image_workspace);

#endif // APP_MANAGER_H__
