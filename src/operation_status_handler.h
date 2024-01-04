#ifndef OPERATION_STATUS_HANDLER_H__
#define OPERATION_STATUS_HANDLER_H__

#include <operation_status.h>
#include <command_data.h>

void operation_status_handler_forward(command_data_t command,
									  e_operation_status_t status);

#endif // OPERATION_STATUS_HANDLER_H__
