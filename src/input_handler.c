#include <input_handler.h>

#include <stdio.h>
#include <string.h>

#include <utils.h>

// TO DO: Add a word object as struct and migrate methods

command_data_t input_handler_read_command_data(void)
{
	const size_t MAX_BUFFER = 255;
	char command_text[MAX_BUFFER];
	input_handler_read_line(command_text);
	command_type_t command_type = input_handler_read_command(command_text);

	command_data_t command_data;
	command_data.base.command_type = CT_NONE;

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

command_type_t input_handler_read_command(char *command_text)
{
	const size_t MAX_BUFFER = 255;
	char opperation[MAX_BUFFER];
	utils_get_word_by_index(0, opperation, command_text);

	command_type_t command_type;
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

command_data_t input_handler_read_load(char *command_text)
{
	command_data_t command_data;
	command_data.load.command_type = CT_LOAD;

	command_data.apply.command_status = CST_INVALID;
	if (utils_count_words(command_text) == 2)
		command_data.apply.command_status = CST_VALID;

	utils_get_word_by_index(1, command_data.load.file_path, command_text);

	return command_data;
}

command_data_t input_handler_read_select(char *command_text)
{
	command_data_t command_data;

	char word[25];
	utils_get_word_by_index(1, word, command_text);

	if (!strcmp(word, "ALL")) {
		command_data.select_all.command_type = CT_SELECT_ALL;
	} else {
		command_data.select.command_type = CT_SELECT;
		__s64 x1, y1, x2, y2;
		if (!utils_word_to_int64(&y1, word)) {
			command_data.apply.command_type = CT_NONE;
			return command_data;
		}
		utils_get_word_by_index(2, word, command_text);
		if (!utils_word_to_int64(&x1, word)) {
			command_data.apply.command_type = CT_NONE;
			return command_data;
		}
		utils_get_word_by_index(3, word, command_text);
		if (!utils_word_to_int64(&y2, word)) {
			command_data.apply.command_type = CT_NONE;
			return command_data;
		}
		utils_get_word_by_index(4, word, command_text);
		if (!utils_word_to_int64(&x2, word)) {
			command_data.apply.command_type = CT_NONE;
			return command_data;
		}

		if (x1 > x2)
			utils_swap_int64(&x1, &x2);
		if (y1 > y2)
			utils_swap_int64(&y1, &y2);

		command_data.select.point_a.x = x1;
		command_data.select.point_a.y = y1;
		command_data.select.point_b.x = x2;
		command_data.select.point_b.y = y2;
	}

	size_t word_count = utils_count_words(command_text);
	command_data.apply.command_status = CST_INVALID;
	if (word_count == 2 || word_count == 5)
		command_data.apply.command_status = CST_VALID;

	return command_data;
}

command_data_t input_handler_read_histogram(char *command_text)
{
	command_data_t command_data;
	command_data.histogram.command_type = CT_HISTOGRAM;

	command_data.apply.command_status = CST_INVALID;
	if (utils_count_words(command_text) == 3)
		command_data.apply.command_status = CST_VALID;

	char word[25];
	utils_get_word_by_index(1, word, command_text);
	utils_word_to_int64((__s64 *)&command_data.histogram.resolution.x, word);
	utils_get_word_by_index(2, word, command_text);
	utils_word_to_int64((__s64 *)&command_data.histogram.resolution.y, word);

	return command_data;
}

command_data_t input_handler_read_equalize(char *command_text)
{
	command_data_t command_data;
	command_data.equalize.command_type = CT_EQUALIZE;

	command_data.apply.command_status = CST_INVALID;
	if (utils_count_words(command_text) == 1)
		command_data.apply.command_status = CST_VALID;

	return command_data;
}

command_data_t input_handler_read_rotate(char *command_text)
{
	command_data_t command_data;
	command_data.rotate.command_type = CT_ROTATE;

	command_data.apply.command_status = CST_INVALID;
	if (utils_count_words(command_text) == 2)
		command_data.apply.command_status = CST_VALID;

	char word[25];
	utils_get_word_by_index(1, word, command_text);
	utils_word_to_int64((__s64 *)&command_data.rotate.angle, word);

	return command_data;
}

command_data_t input_handler_read_crop(char *command_text)
{
	command_data_t command_data;
	command_data.crop.command_type = CT_CROP;

	command_data.apply.command_status = CST_INVALID;
	if (utils_count_words(command_text) == 1)
		command_data.apply.command_status = CST_VALID;

	return command_data;
}

command_data_t input_handler_read_apply(char *command_text)
{
	command_data_t command_data;
	command_data.apply.command_type = CT_APPLY;

	command_data.apply.command_status = CST_INVALID;
	if (utils_count_words(command_text) == 2)
		command_data.apply.command_status = CST_VALID;

	char word[25];
	word[0] = '\0';
	utils_get_word_by_index(1, word, command_text);

	if (!strcmp(word, "EDGE"))
		command_data.apply.image_kernel_type = IKT_EDGE;
	else if (!strcmp(word, "SHARPEN"))
		command_data.apply.image_kernel_type = IKT_SHARPEN;
	else if (!strcmp(word, "BLUR"))
		command_data.apply.image_kernel_type = IKT_BOX_BLUR;
	else if (!strcmp(word, "GAUSSIAN_BLUR"))
		command_data.apply.image_kernel_type = IKT_GAUSSIAN_BLUR;
	else
		command_data.apply.image_kernel_type = IKT_NONE;

	return command_data;
}

command_data_t input_handler_read_save(char *command_text)
{
	command_data_t command_data;
	command_data.save.command_type = CT_SAVE;

	size_t word_count = utils_count_words(command_text);
	command_data.apply.command_status = CST_INVALID;
	if (word_count == 2 || word_count == 3)
		command_data.apply.command_status = CST_VALID;

	utils_get_word_by_index(1, command_data.save.file_path, command_text);

	command_data.save.save_as_ascii = 0;
	char word[25];
	utils_get_word_by_index(2, word, command_text);
	if (!strcmp(word, "ascii"))
		command_data.save.save_as_ascii = 1;

	return command_data;
}

command_data_t input_handler_read_exit(char *command_text)
{
	command_data_t command_data;
	command_data.exit.command_type = CT_EXIT;

	command_data.apply.command_status = CST_INVALID;
	if (utils_count_words(command_text) == 1)
		command_data.apply.command_status = CST_VALID;

	return command_data;
}

void input_handler_read_string(char *str)
{
	scanf("%s[\n]", str);
}

void input_handler_read_vector2(vector2_t *coords)
{
	scanf("%lld%lld", &coords->x, &coords->y);
}

void input_handler_read_int64(__s64 *int64)
{
	scanf("%lld", int64);
}

void input_handler_read_size(size_t *size)
{
	scanf("%zu", size);
}

void input_handler_read_line(char *str)
{
	char c;
	scanf("%[^\n]%c", str, &c);
}
