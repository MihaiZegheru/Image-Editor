#ifndef OPERATION_STATUS_HANDLER_H__
#define OPERATION_STATUS_HANDLER_H__

#include <operation_status.h>
#include <command_data.h>

/**
 * @brief Feed an operation_status for a command_data for it to get interpreted
 *		  and prints on stdout the coresponding response
 *
 * @param command
 * @param status
 */
void operation_status_handler_forward(u_command_data_t command,
									  e_operation_status_t status);

#endif // OPERATION_STATUS_HANDLER_H__
