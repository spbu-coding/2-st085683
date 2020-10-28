#ifndef TASK_2_UTILS_H
#define TASK_2_UTILS_H

#include <stdio.h>

#define errprintf(...) fprintf(stderr, __VA_ARGS__)

int fprintf_array_ll(FILE *, long long *list, size_t size_list);

#endif
