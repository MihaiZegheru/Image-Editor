/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#include <input_handler.h>

#include <stdio.h>
#include <string.h>

#include <utils.h>

// TO DO: Add a word object as struct and migrate methods

// TO DO: Add a system to substitude hardcoded values. Create a data asset
//		  object to store the values and initialise them in main

/**
 * @brief Get a command_type based on a given command text
 *
 * @param command_text
 * @return e_command_type_t
 */
static e_command_type_t input_handler_read_command(char *command_text);

/**
 * @brief Computes the parameters of command_type CT_LOAD
 *
 * @param command_text
 * @return u_command_data_t
 */
static u_command_data_t input_handler_read_load(char *command_text);

/**
 * @brief Computes the parameters of command_type CT_SELECT
 *
 * @param command_text
 * @return u_command_data_t
 */
static u_command_data_t input_handler_read_select(char *command_text);

/**
 * @brief Computes the parameters of command_type CT_HISTOGRAM
 *
 * @param command_text
 * @return u_command_data_t
 */
static u_command_data_t input_handler_read_histogram(char *command_text);

/**
 * @brief Computes the parameters of command_type CT_EQUALIZE
 *
 * @param command_text
 * @return u_command_data_t
 */
static u_command_data_t input_handler_read_equalize(char *command_text);

/**
 * @brief Computes the parameters of command_type CT_ROTATE
 *
 * @param command_text
 * @return u_command_data_t
 */
static u_command_data_t input_handler_read_rotate(char *command_text);

/**
 * @brief Computes the parameters of command_type CT_CROP
 *
 * @param command_text
 * @return u_command_data_t
 */
static u_command_data_t input_handler_read_crop(char *command_text);

/**
 * @brief Computes the parameters of command_type CT_APPLY
 *
 * @param command_text
 * @return u_command_data_t
 */
static u_command_data_t input_handler_read_apply(char *command_text);

/**
 * @brief Computes the parameters of command_type CT_SAVE
 *
 * @param command_text
 * @return u_command_data_t
 */
static u_command_data_t input_handler_read_save(char *command_text);

/**
 * @brief Computes the parameters of command_type CT_EXIT
 *
 * @param command_text
 * @return u_command_data_t
 */
static u_command_data_t input_handler_read_exit(char *command_text);

u_command_data_t input_handler_read_command_data(void)
{
	char command_text[COMMAND_MAX_BUFFER];
	input_handler_read_line(command_text);
	e_command_type_t command_type = input_handler_read_command(command_text);

	u_command_data_t command_data;
	command_data.m_base.m_command_type = CT_NONE;

	switch (command_type) {
	case CT_LOAD:
		return input_handler_read_load(command_text);
	case CT_SELECT:
		return input_handler_read_select(command_text);
	case CT_HISTOGRAM:
		return input_handler_read_histogram(command_text);
	case CT_EQUALIZE:
		return input_handler_read_equalize(command_text);
	case CT_ROTATE:
		return input_handler_read_rotate(command_text);
	case CT_CROP:
		return input_handler_read_crop(command_text);
	case CT_APPLY:
		return input_handler_read_apply(command_text);
	case CT_SAVE:
		return input_handler_read_save(command_text);
	case CT_EXIT:
		return input_handler_read_exit(command_text);
	default:
		return command_data;
	}
}

static e_command_type_t input_handler_read_command(char *command_text)
{
	char opperation[COMMAND_MAX_BUFFER];
	utils_get_word_by_index(0, opperation, command_text);

	e_command_type_t command_type;
	if (!strcmp(opperation, "LOAD"))
		command_type = CT_LOAD;
	else if (!strcmp(opperation, "SELECT"))
		command_type = CT_SELECT;
	else if (!strcmp(opperation, "HISTOGRAM"))
		command_type = CT_HISTOGRAM;
	else if (!strcmp(opperation, "EQUALIZE"))
		command_type = CT_EQUALIZE;
	else if (!strcmp(opperation, "ROTATE"))
		command_type = CT_ROTATE;
	else if (!strcmp(opperation, "CROP"))
		command_type = CT_CROP;
	else if (!strcmp(opperation, "APPLY"))
		command_type = CT_APPLY;
	else if (!strcmp(opperation, "SAVE"))
		command_type = CT_SAVE;
	else if (!strcmp(opperation, "EXIT"))
		command_type = CT_EXIT;
	else
		command_type = CT_NONE;

	return command_type;
}

static u_command_data_t input_handler_read_load(char *command_text)
{
	u_command_data_t command_data;
	command_data.m_load.m_command_type = CT_LOAD;

	command_data.m_apply.m_command_status = CST_INVALID;
	if (utils_count_words(command_text) == 2)
		command_data.m_apply.m_command_status = CST_VALID;

	utils_get_word_by_index(1, command_data.m_load.m_file_path, command_text);

	return command_data;
}

static u_command_data_t input_handler_read_select(char *command_text)
{
	u_command_data_t command_data;

	char word[25];
	utils_get_word_by_index(1, word, command_text);

	if (!strcmp(word, "ALL")) {
		command_data.m_select_all.m_command_type = CT_SELECT_ALL;
	} else {
		command_data.m_select.m_command_type = CT_SELECT;
		__s64 x1, y1, x2, y2;
		if (!utils_word_to_int64(&y1, word)) {
			command_data.m_apply.m_command_type = CT_NONE;
			return command_data;
		}
		utils_get_word_by_index(2, word, command_text);
		if (!utils_word_to_int64(&x1, word)) {
			command_data.m_apply.m_command_type = CT_NONE;
			return command_data;
		}
		utils_get_word_by_index(3, word, command_text);
		if (!utils_word_to_int64(&y2, word)) {
			command_data.m_apply.m_command_type = CT_NONE;
			return command_data;
		}
		utils_get_word_by_index(4, word, command_text);
		if (!utils_word_to_int64(&x2, word)) {
			command_data.m_apply.m_command_type = CT_NONE;
			return command_data;
		}

		if (x1 > x2)
			utils_swap_int64(&x1, &x2);
		if (y1 > y2)
			utils_swap_int64(&y1, &y2);

		command_data.m_select.m_point_a.m_x = x1;
		command_data.m_select.m_point_a.m_y = y1;
		command_data.m_select.m_point_b.m_x = x2;
		command_data.m_select.m_point_b.m_y = y2;
	}

	size_t word_count = utils_count_words(command_text);
	command_data.m_apply.m_command_status = CST_INVALID;
	if (word_count == 2 || word_count == 5)
		command_data.m_apply.m_command_status = CST_VALID;

	return command_data;
}

static u_command_data_t input_handler_read_histogram(char *command_text)
{
	u_command_data_t command_data;
	command_data.m_histogram.m_command_type = CT_HISTOGRAM;

	command_data.m_apply.m_command_status = CST_INVALID;
	if (utils_count_words(command_text) == 3)
		command_data.m_apply.m_command_status = CST_VALID;

	char word[25];
	utils_get_word_by_index(1, word, command_text);
	utils_word_to_int64((__s64 *)&command_data.m_histogram.resolution.m_x,
						word);
	utils_get_word_by_index(2, word, command_text);
	utils_word_to_int64((__s64 *)&command_data.m_histogram.resolution.m_y,
						word);

	return command_data;
}

static u_command_data_t input_handler_read_equalize(char *command_text)
{
	u_command_data_t command_data;
	command_data.m_equalize.m_command_type = CT_EQUALIZE;

	command_data.m_apply.m_command_status = CST_INVALID;
	if (utils_count_words(command_text) == 1)
		command_data.m_apply.m_command_status = CST_VALID;

	return command_data;
}

static u_command_data_t input_handler_read_rotate(char *command_text)
{
	u_command_data_t command_data;
	command_data.m_rotate.m_command_type = CT_ROTATE;

	command_data.m_apply.m_command_status = CST_INVALID;
	if (utils_count_words(command_text) == 2)
		command_data.m_apply.m_command_status = CST_VALID;

	char word[25];
	utils_get_word_by_index(1, word, command_text);
	utils_word_to_int64((__s64 *)&command_data.m_rotate.angle, word);

	return command_data;
}

static u_command_data_t input_handler_read_crop(char *command_text)
{
	u_command_data_t command_data;
	command_data.m_crop.m_command_type = CT_CROP;

	command_data.m_apply.m_command_status = CST_INVALID;
	if (utils_count_words(command_text) == 1)
		command_data.m_apply.m_command_status = CST_VALID;

	return command_data;
}

static u_command_data_t input_handler_read_apply(char *command_text)
{
	u_command_data_t command_data;
	command_data.m_apply.m_command_type = CT_APPLY;

	command_data.m_apply.m_command_status = CST_INVALID;
	if (utils_count_words(command_text) == 2)
		command_data.m_apply.m_command_status = CST_VALID;

	char word[25];
	word[0] = '\0';
	utils_get_word_by_index(1, word, command_text);

	if (!strcmp(word, "EDGE"))
		command_data.m_apply.image_kernel_type = IKT_EDGE;
	else if (!strcmp(word, "SHARPEN"))
		command_data.m_apply.image_kernel_type = IKT_SHARPEN;
	else if (!strcmp(word, "BLUR"))
		command_data.m_apply.image_kernel_type = IKT_BOX_BLUR;
	else if (!strcmp(word, "GAUSSIAN_BLUR"))
		command_data.m_apply.image_kernel_type = IKT_GAUSSIAN_BLUR;
	else
		command_data.m_apply.image_kernel_type = IKT_NONE;

	return command_data;
}

static u_command_data_t input_handler_read_save(char *command_text)
{
	u_command_data_t command_data;
	command_data.m_save.m_command_type = CT_SAVE;

	size_t word_count = utils_count_words(command_text);
	command_data.m_apply.m_command_status = CST_INVALID;
	if (word_count == 2 || word_count == 3)
		command_data.m_apply.m_command_status = CST_VALID;

	utils_get_word_by_index(1, command_data.m_save.m_file_path, command_text);

	command_data.m_save.m_save_as_ascii = 0;
	char word[25];
	utils_get_word_by_index(2, word, command_text);
	if (!strcmp(word, "ascii"))
		command_data.m_save.m_save_as_ascii = 1;

	return command_data;
}

static u_command_data_t input_handler_read_exit(char *command_text)
{
	u_command_data_t command_data;
	command_data.m_exit.m_command_type = CT_EXIT;

	command_data.m_apply.m_command_status = CST_INVALID;
	if (utils_count_words(command_text) == 1)
		command_data.m_apply.m_command_status = CST_VALID;

	return command_data;
}

void input_handler_read_line(char *str)
{
	char c;
	scanf("%[^\n]%c", str, &c);
}
