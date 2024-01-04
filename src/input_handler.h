#ifndef INPUT_HANDLER_H__
#define INPUT_HANDLER_H__

#include <linux/types.h>
#include <stddef.h>

#include <vector2.h>
#include <command_data.h>
#include <command_type.h>

command_data_t input_handler_read_command_data(void);

/**
 * @brief Read a line from stdin
 * @note Performs no checks for overflow
 * @param str 
 */
void input_handler_read_line(char *str);

#endif // INPUT_HANDLER_H__
