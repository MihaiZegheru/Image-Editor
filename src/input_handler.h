#ifndef INPUT_HANDLER_H__
#define INPUT_HANDLER_H__

#include <command_type.h>
#include <vector2.h>
#include <inttypes.h>
#include <stddef.h>
#include <command_data.h>

command_data_t input_handler_read_command_data();
command_type_t input_handler_read_command();

command_data_t input_handler_read_load();
command_data_t input_handler_read_select();
command_data_t input_handler_read_histogram();
command_data_t input_handler_read_equalize();
command_data_t input_handler_read_rotate();
command_data_t input_handler_read_crop();
command_data_t input_handler_read_apply();
command_data_t input_handler_read_save();
command_data_t input_handler_read_exit();

void input_handler_read_string(char *str);
void input_handler_read_vector2(vector2_t *coords);
void input_handler_read_int64(int64_t *int64);
void input_handler_read_size(size_t *size);
void input_handler_read_line(char *str);


#endif // INPUT_HANDLER_H__