#ifndef UTIL_H_CUSHMAN
#define UTIL_H_CUSHMAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_int(void*, void*);
int cmp_ulong(void*, void*);
int cmp_str(void*, void*);
void swap(void**, void**);
void print_bin(char*, size_t);

#endif /* UTIL_H_CUSHMAN */