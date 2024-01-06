/**
 *	Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb
*/

#ifndef UTILS_H__
#define UTILS_H__

#include <linux/types.h>
#include <stddef.h>

/**
 * @brief Maximum value between a and b
 *
 * @param a
 * @param b
 * @return __s64
 */
__s64 utils_max_int64(__s64 a, __s64 b);

/**
 * @brief Clamp value between min and max
 *
 * @param value
 * @param min
 * @param max
 * @return double
 */
double utils_clamp(double value, double min, double max);

/**
 * @brief Swap pointer a with pointer b
 *
 * @param a
 * @param b
 * @note Should cast to (void **) before use
 */
void utils_swap_pointers(void **a, void **b);

/**
 * @brief Swap value a with value b
 *
 * @param a
 * @param b
 */
void utils_swap_int64(__s64 *a, __s64 *b);

/**
 * @brief Count words from a given string
 *
 * @param str
 * @return size_t
 */
size_t utils_count_words(char *str);

/**
 * @brief Get word by index from given string
 *
 * @param index
 * @param word
 * @param str
 */
void utils_get_word_by_index(size_t index, char *out, char *str);

/**
 * @brief Translates a string into __s64
 *
 * @param str
 * @return __s64
 * @note Performs no check
 * @note DEVELOPMENT: This should migrate from the project into
 *					  utils_word_to_int64 and it is considered deprecated
 */
__s64 utils_string_to_int64(char *str);

/**
 * @brief Translates a word into __s64 if possible
 *
 * @param out
 * @param str
 * @return __s8 - 1 if the word is a number, 0 if not
 */
__s8 utils_word_to_int64(__s64 *out, char *word);

#endif // UTILS_H__
