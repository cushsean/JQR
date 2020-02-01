#ifndef HASH_H_CUSHMAN
#define HASH_H_CUSHMAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "util.h"

#define LIMITER 99999999

unsigned long hash(char*);
node_t** hash_table();
node_t** hash_insert(node_t**, void*, int*);
void hash_free(node_t**);
node_t* hash_find_byValue(node_t**, void*, int);
node_t* hash_find_byNumber(node_t**, unsigned long);

#endif /* HASH_H_CUSHMAN */