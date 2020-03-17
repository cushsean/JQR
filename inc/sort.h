#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "util.h"


void sort_bubble_array(void *arr, size_t nmemb, size_t e_size, 
    int (*cmp_ptr)(void*, void*));


node_t* sort_bubble_list(void *node, int (*com_ptr)(void*, void*));

