/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#ifndef OPERATION_STATUS_H__
#define OPERATION_STATUS_H__

/**
 * @brief The operation_status defines a status that resembles how an operation
 *		  went, if there are any errors or if it was successful
 *
 */
typedef enum {
	OS_NONE,
	OS_DEFAULT_DONE,
	OS_IMAGE_NOT_LOADED,
	OS_IMAGE_NOT_GRAYSCALE,
	OS_LOAD_DONE,
	OS_LOAD_FAILED,
	OS_SELECT_CUSTOM_DONE,
	OS_SELECT_CUSTOM_FAILED,
	OS_SELECT_ALL_DONE,
	OS_ROTATE_DONE,
	OS_ROTATE_SELECTION_INVALID,
	OS_ROTATE_ANGLE_INVALID,
	OS_EQUALIZE_DONE,
	OS_CROP_DONE,
	OS_APPLY_DONE,
	OS_APPLY_GRAYSCALE_IMAGE,
	OS_APPLY_PARAMETER_INVALID,
	OS_HISTOGRAM_PARAMETER_INVALID,
	OS_SAVE_DONE,
	OS_COMMAND_ERROR,
} e_operation_status_t;

#endif // OPERATION_STATUS_H__
