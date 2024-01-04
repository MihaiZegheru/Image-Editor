#ifndef STATUS_HANDLER_H__
#define STATUS_HANDLER_H__

#include <operation_status.h>
#include <command_data.h>

void status_handler_forward(command_data_t command,
							e_operation_status_t status);

#endif // STATUS_HANDLER_H__
