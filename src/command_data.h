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
} cd_default_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
	char file_path[100];
} cd_load_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
	s_vector2_t point_a;
	s_vector2_t point_b;
} cd_select_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
} cd_select_all_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
	s_vector2_t resolution;
} cd_histogram_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
} cd_equalize_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
	__s16 angle;
} cd_rotate_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
} cd_crop_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
	image_kernel_type_t image_kernel_type;
} cd_apply_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
	char file_path[100];
	__u8 save_as_ascii;
} cd_save_t;

typedef struct {
	command_type_t command_type;
	e_command_status_t command_status;
} cd_exit_t;

typedef union {
	cd_default_t base;
	cd_load_t load;
	cd_select_t select;
	cd_select_all_t select_all;
	cd_histogram_t histogram;
	cd_equalize_t equalize;
	cd_rotate_t rotate;
	cd_crop_t crop;
	cd_apply_t apply;
	cd_save_t save;
	cd_exit_t exit;
} command_data_t;

#endif // COMMAND_DATA_H__
