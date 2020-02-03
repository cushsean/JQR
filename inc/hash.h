#ifndef HASH_H_CUSHMAN
#define HASH_H_CUSHMAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "util.h"

#define MATCH 0
#define LIMITER 99999999
#define WORD_SIZE 128

unsigned long hash(char*);
char** hash_table();
char** hash_insert(char**, void*, int*);
void hash_free(char**);
long hash_find_byValue(char**, void*);
long hash_find_byNumber(char**, unsigned long);
char** hash_rmItem(char**, void*);
#endif /* HASH_H_CUSHMAN */