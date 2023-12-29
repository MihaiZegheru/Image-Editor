#ifndef APP_MANAGER_H__
#define APP_MANAGER_H__

#include <inttypes.h>

#include <image_workspace.h>
#include <error_types.h>

uint8_t app_manager_main_loop();
uint8_t app_manager_tick();

error_type_t app_manager_load(image_workspace_t *image_workspace);
error_type_t app_manager_select(image_workspace_t *image_workspace);
error_type_t app_manager_select_all(image_workspace_t *image_workspace);
error_type_t app_manager_histogram(image_workspace_t *image_workspace);

#endif // APP_MANAGER_H__
