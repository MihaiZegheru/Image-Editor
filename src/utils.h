#ifndef UTILS_H__
#define UTILS_H__

#include <inttypes.h>
#include <stddef.h>

int64_t utils_string_to_int64(char *str);
int64_t utils_max_int64(uint64_t a, uint64_t b);
double utils_clamp(double value, double min, double max);
void utils_swap_pointers(void **a, void **b);
size_t utils_count_words(char *str);

#endif // UTILS_H__