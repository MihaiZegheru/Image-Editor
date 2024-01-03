#ifndef STATUS_HANDLER_H__
#define STATUS_HANDLER_H__

#include <status_types.h>
#include <command_data.h>

void status_handler_forward(command_data_t command, status_type_t status);

#endif // STATUS_HANDLER_H__