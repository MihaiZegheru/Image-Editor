#include <utils.h>

int64_t utils_string_to_int64(char *str)
{   
    int64_t value = 0;
    size_t index = 0;

    while (str[index] != ' ' && str[index] != '\n' && str[index] != '\0') {
        value *= 10;
        value += str[index] - '0';
        index++;
    }

    return value;
}

int64_t utils_max_int64(uint64_t a, uint64_t b)
{
    return (a < b) ? b : a;
}

double utils_clamp(double value, double min, double max)
{
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

void utils_swap_pointers(void **a, void **b)
{
    void *aux = *a;
    *a = *b;
    *b = aux;
}

size_t utils_count_words(char *str)
{
    size_t count = 0;
    size_t index = 0;
    while (str[index] != '\n') {
        if (str[index] != ' ' && (str[index - 1] == ' ' || index == 0)) {
            count++;
        }
        index++;
    }

    return count;
}