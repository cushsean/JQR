#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/**
 * Creates a stack with num number of elements to be filled later.
 */
node_t* mkStack(int num);


/**
 * Adds an element to the top of the stack with value pointed to by value.
 */
node_t* push(node_t *top, void *value);


/**
 * Removed and frees the element on the top of the stack.
 */
node_t* pop(node_t *top);


/**
 * Iterates throght the stack and returns the number of elements in the stack.
 */
int get_stack_size(node_t *top);


/**
 * Removes and frees every element in the stack.
 */
void rmStack(node_t *top);