#ifndef COMMAND_TYPE_H__
#define COMMAND_TYPE_H__

/**
 * @brief The command_type defines the command that can be applied on an image
 *
 */
typedef enum {
	CT_NONE,
	CT_LOAD,
	CT_SELECT,
	CT_SELECT_ALL,
	CT_HISTOGRAM,
	CT_EQUALIZE,
	CT_ROTATE,
	CT_CROP,
	CT_APPLY,
	CT_SAVE,
	CT_EXIT,
} e_command_type_t;

#endif // COMMAND_TYPE_H__
