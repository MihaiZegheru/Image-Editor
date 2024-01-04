#ifndef UTILS_H__
#define UTILS_H__

#include <linux/types.h>
#include <stddef.h>

__s64 utils_max_int64(__s64 a, __s64 b);
double utils_clamp(double value, double min, double max);

void utils_swap_pointers(void **a, void **b);
void utils_swap_int64(__s64 *a, __s64 *b);

size_t utils_count_words(char *str);
void utils_get_word_by_index(size_t index, char *word, char *str);
__s64 utils_string_to_int64(char *str);
__s8 utils_word_to_int64(__s64 *out, char *str);

#endif // UTILS_H__
