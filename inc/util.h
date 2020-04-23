#ifndef UTIL_H_CUSHMAN
#define UTIL_H_CUSHMAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int cmp_int(void*, void*);
int cmp_ulong(void*, void*);
int cmp_str(void*, void*);
void swap(void*, void*, size_t);
void print_bin(char*, size_t);

/**
 * Prints the interger contained in the void*
 * Does not include a newline or any spacing
 **/
void print_int(void *num);

node_t* swap_node(node_t *head, node_t *a, node_t *b);

node_t* swap_node_singly(node_t *head, node_t *curr, node_t *NX, node_t *PR);


/**
 * Hashing scheme that returns an unsigned long.
 */
unsigned long hash(void *input, size_t size);


/**
 * Prints the contents of a leaf.
 */
void print_str(void* data);


#endif /* UTIL_H_CUSHMAN */