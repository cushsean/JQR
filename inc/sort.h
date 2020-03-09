#include <stdlib.h>
#include <stdio.h>

#include "util.h"

void sort_bubble(int *arr, size_t nmemb, int (*cmp_ptr)(void*, void*));