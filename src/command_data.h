#ifndef COMMAND_DATA_H__
#define COMMAND_DATA_H__

#include <stddef.h>
#include <linux/types.h>

#include <command_type.h>
#include <command_status.h>
#include <image_kernel_type.h>
#include <image_format_type.h>
#include <vector2.h>

typedef struct {
	e_command_type_t m_command_type;
	e_command_status_t m_command_status;
} s_cd_default_t;

typedef struct {
	e_command_type_t m_command_type;
	e_command_status_t m_command_status;
	char m_file_path[100];
} s_cd_load_t;

typedef struct {
	e_command_type_t m_command_type;
	e_command_status_t m_command_status;
	s_vector2_t m_point_a;
	s_vector2_t m_point_b;
} s_cd_select_t;

typedef struct {
	e_command_type_t m_command_type;
	e_command_status_t m_command_status;
} s_cd_select_all_t;

typedef struct {
	e_command_type_t m_command_type;
	e_command_status_t m_command_status;
	s_vector2_t resolution;
} s_cd_histogram_t;

typedef struct {
	e_command_type_t m_command_type;
	e_command_status_t m_command_status;
} s_cd_equalize_t;

typedef struct {
	e_command_type_t m_command_type;
	e_command_status_t m_command_status;
	__s16 angle;
} s_cd_rotate_t;

typedef struct {
	e_command_type_t m_command_type;
	e_command_status_t m_command_status;
} s_cd_crop_t;

typedef struct {
	e_command_type_t m_command_type;
	e_command_status_t m_command_status;
	e_image_kernel_type_t image_kernel_type;
} s_cd_apply_t;

typedef struct {
	e_command_type_t m_command_type;
	e_command_status_t m_command_status;
	char m_file_path[100];
	__u8 m_save_as_ascii;
} s_cd_save_t;

typedef struct {
	e_command_type_t m_command_type;
	e_command_status_t m_command_status;
} s_cd_exit_t;

/**
 * @brief The command_data defines the data of a command within an union so that
 *		  all commands cand have a base object type that they can be stored in.
 *
 *		  Later, they will be differentiated upon the command_type from base,
 *		  that is common to all members.
 *
 */
typedef union {
	s_cd_default_t m_base;
	s_cd_load_t m_load;
	s_cd_select_t m_select;
	s_cd_select_all_t m_select_all;
	s_cd_histogram_t m_histogram;
	s_cd_equalize_t m_equalize;
	s_cd_rotate_t m_rotate;
	s_cd_crop_t m_crop;
	s_cd_apply_t m_apply;
	s_cd_save_t m_save;
	s_cd_exit_t m_exit;
} u_command_data_t;

#endif // COMMAND_DATA_H__
