/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#include <utils.h>

__s64 utils_max_int64(__s64 a, __s64 b)
{
	return (a < b) ? b : a;
}

double utils_clamp(double value, double min, double max)
{
	if (value < min)
		return min;

	if (value > max)
		return max;

	return value;
}

void utils_swap_pointers(void **a, void **b)
{
	void *aux = *a;
	*a = *b;
	*b = aux;
}

void utils_swap_int64(__s64 *a, __s64 *b)
{
	__s64 aux = *a;
	*a = *b;
	*b = aux;
}

size_t utils_count_words(char *str)
{
	size_t count = 0;
	size_t index = 0;
	while (str[index] != '\0') {
		if (str[index] != ' ' && (str[index - 1] == ' ' || index == 0))
			count++;

		index++;
	}

	return count;
}

void utils_get_word_by_index(size_t index, char *out, char *str)
{
	size_t count = 0;
	size_t str_index = 0;
	size_t word_index = 0;
	while (str[str_index] != '\0') {
		if (str[str_index] != ' ' && (str[str_index - 1] == ' ' ||
									  str_index == 0)) {
			count++;
		}

		if (str[str_index] != ' ' && count - 1 == index)
			out[word_index++] = str[str_index];

		str_index++;
	}

	out[word_index] = '\0';
}

__s64 utils_string_to_int64(char *str)
{
	__s64 value = 0;
	size_t index = 0;

	while (str[index] >= '0' && str[index] <= '9') {
		value *= 10;
		value += str[index] - '0';
		index++;
	}

	return value;
}

__s8 utils_word_to_int64(__s64 *out, char *word)
{
	*out = 0;
	size_t index = 0;

	__s8 is_negative = 0;
	if (word[index] == '-') {
		is_negative = 1;
		index++;
	}

	while (word[index] != '\0') {
		if (word[index] > '9' || word[index] < '0')
			return 0;

		*out *= 10;
		*out += word[index++] - '0';
	}

	if (is_negative)
		*out = -(*out);

	return 1;
}
