#ifndef APP_MANAGER_H__
#define APP_MANAGER_H__

#include <linux/types.h>

/**
 * @brief Main loop of the app
 *
 * @return __u8
 * @note DEVELOPMENT: might migrate back to main.c
 */
__u8 app_manager_main_loop(void);

#endif // APP_MANAGER_H__
