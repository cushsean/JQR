#ifndef QUE_H_CUSHMAN
#define QUE_H_CUSHMAN

#include <stdlib.h>
#include <stdio.h>

#include "list.h"

/**
 * Type declaration for Queues.
 */
typedef struct llist que_t;


/**
 * Creates a que.
 * 
 * Returns a pointer to type que_t.
 * 
 * datacpy: User defined function to copy data from src to dest.
 * 
 * datacmp: User defined function to compare data1 and data2.
 
 * 			Return:
 * 				 1 if data1 > data2
 * 				 0 if data1 == data2
 * 				-1 if data1 < data2
 * 
 * datafree: User defined fucntion to free data stored in linked list.
 */
que_t* que_create(void (*datacpy)(void *dest, void *src), 
					int (*datacmp)(void *data1, void *data2),
					void (*datafree)(void **data));


/**
 * Pushes an item on the end of the que.
 * 
 * Size is size of data.
 */
void que_push(que_t *que, void *data, size_t size);


/**
 * Finds an item in the que that matches the void* passed.
 * 
 * All items before the matched item will be popped (d qued).
 */
void que_find_item(que_t *que, void *item);


/**
 * Finds the nth item in the que.
 * 
 * All items before the nth item will be popped (d qued).
 */
void que_find_nth(que_t *que, size_t n);


/**
 * Pops (d ques) the first item in the que.
 * 
 * Returns 0 on success.
 * Returns 1 on failure.
 */
int que_pop(que_t *que);


/**
 * Destroys the entire que, popping (d queing) all items in the que.
 */
void que_destroy(que_t** que);


/**
 * Prints the que.
 */
void que_print(que_t *que, void (*data_print)(void *data));


/**
 * Get the size of the que.
 */
size_t que_size(que_t *que);

#endif /* QUE_H_CUSHMAN */