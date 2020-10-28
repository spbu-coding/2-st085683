#include "utils.h"

int fprintf_array_ll(FILE *stream, long long *list, size_t size_list) {
    if (size_list > 0) {
        if (fprintf(stream, "%lld", list[0]) < 0) return -1;
    }
    for (size_t x = 1; x < size_list; ++x) {
        if (fprintf(stream, " %lld", list[x]) < 0) return -1;
    }

    return 0;
}
