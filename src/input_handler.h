#ifndef INPUT_HANDLER_H__
#define INPUT_HANDLER_H__

#include <command_type.h>
#include <vector2.h>
#include <stddef.h>
#include <command_data.h>
#include <linux/types.h>

command_data_t input_handler_read_command_data(void);
command_type_t input_handler_read_command(char *command_text);

command_data_t input_handler_read_load(char *command_text);
command_data_t input_handler_read_select(char *command_text);
command_data_t input_handler_read_histogram(char *command_text);
command_data_t input_handler_read_equalize(char *command_text);
command_data_t input_handler_read_rotate(char *command_text);
command_data_t input_handler_read_crop(char *command_text);
command_data_t input_handler_read_apply(char *command_text);
command_data_t input_handler_read_save(char *command_text);
command_data_t input_handler_read_exit(char *command_text);

void input_handler_read_string(char *str);
void input_handler_read_vector2(vector2_t *coords);
void input_handler_read_int64(__s64 *int64);
void input_handler_read_size(size_t *size);
void input_handler_read_line(char *str);

#endif // INPUT_HANDLER_H__
