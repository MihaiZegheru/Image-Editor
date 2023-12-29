#ifndef INPUT_HANDLER_H__
#define INPUT_HANDLER_H__

#include <command_type.h>
#include <vector2.h>
#include <inttypes.h>
#include <stddef.h>

command_type_t input_handler_read_command();
void input_handler_read_string(char *str);
void input_handler_read_vector2(vector2_t *coords);
void input_handler_read_int64(int64_t *int64);
void input_handler_read_size(size_t *size);


#endif // INPUT_HANDLER_H__