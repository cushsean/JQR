#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct llist stack_t;


/**
 * Creates a stack.
 * 
 * Returns a pointer to type stack_t.
 * 
 * datacpy: User defined function to copy data from src to dest.
 * 
 * datacmp: User defined function to compare data1 and data2.
 
 * 			Return:
 * 				 1 if data1 > data2
 * 				 0 if data1 == data2
 * 				-1 if data1 < data2
 * 
 * datafree: User defined fucntion to free data stored in linked list.f
 */
stack_t* stack_create(void (*datacpy)(void *dest, void *src), 
					    int (*datacmp)(void *data1, void *data2),
					    void (*datafree)(void **data));


/**
 * Pushes an item onto the stack.
 * 
 * Size is size of data.
 */
void stack_push(stack_t *stack, void *data, size_t size);


/**
 * Poppes an item off the stack.
 * 
 * Returns 0 on Success.
 * Returns 1 on Failure.
 */
int stack_pop(stack_t *stack);


/**
 * Poppes all items off the stack and frees the stack itself.
 */
void stack_destroy(stack_t **stack);


/**
 * Prints the contents of the stack.
 */
void stack_print(stack_t *stack, void (*data_print)(void *data));


/**
 * Returns the number of items in the stack.
 */
size_t stack_size(stack_t *stack);


/**
 * Finds item in the stack. 
 * 
 * If nth_mode is TRUE, item will be an int pointer of the nth item that should 
 * be returned. Items are zero based, therefore HEAd will be item 0. Tail can be 
 * referenced as item -1.
 * 
 * If nth_mode is FALSE, the nth_instance of a match to item will be returned.
 */
void* stack_find(stack_t *stack, int nth_mode, void *item, size_t nth_instance);