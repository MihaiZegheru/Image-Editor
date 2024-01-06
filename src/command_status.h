/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#ifndef COMMAND_STATUS_H__
#define COMMAND_STATUS_H__

/**
 * @brief The command_status defines wether the command input is valid or not
 *
 */
typedef enum {
	CST_NONE,
	CST_VALID,
	CST_INVALID,
} e_command_status_t;

#endif // COMMAND_STATUS_H__
