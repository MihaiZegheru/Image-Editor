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
	command_type_t command_type;
	e_command_status_t command_status;
} s_cd_default_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
	char file_path[100];
} s_cd_load_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
	s_vector2_t point_a;
	s_vector2_t point_b;
} s_cd_select_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
} s_cd_select_all_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
	s_vector2_t resolution;
} s_cd_histogram_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
} s_cd_equalize_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
	__s16 angle;
} s_cd_rotate_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
} s_cd_crop_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
	image_kernel_type_t image_kernel_type;
} s_cd_apply_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
	char file_path[100];
	__u8 save_as_ascii;
} s_cd_save_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
} s_cd_exit_t;

typedef union {
	s_cd_default_t base;
	s_cd_load_t load;
	s_cd_select_t select;
	s_cd_select_all_t select_all;
	s_cd_histogram_t histogram;
	s_cd_equalize_t equalize;
	s_cd_rotate_t rotate;
	s_cd_crop_t crop;
	s_cd_apply_t apply;
	s_cd_save_t save;
	s_cd_exit_t exit;
} u_command_data_t;

#endif // COMMAND_DATA_H__
