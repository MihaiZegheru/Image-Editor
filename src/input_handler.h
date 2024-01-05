#ifndef INPUT_HANDLER_H__
#define INPUT_HANDLER_H__

#include <linux/types.h>
#include <stddef.h>

#include <vector2.h>
#include <command_data.h>
#include <command_type.h>

#define COMMAND_MAX_BUFFER 255

/**
 * @brief Read command data from stdin
 *
 * @return u_command_data_t
 */
u_command_data_t input_handler_read_command_data(void);

/**
 * @brief Read a line from stdin
 *
 * @param str
 * @note Performs no checks for overflow
 */
void input_handler_read_line(char *str);

#endif // INPUT_HANDLER_H__
