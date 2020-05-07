#ifndef LIST_H_CUSHMAN
#define LIST_H_CUSHMAN

#include <stdlib.h>
#include <stdio.h>

#ifndef TRUE
#define TRUE (1)
#define FALSE (0)
#endif

#define DOUBLY (1)
#define SINGLY (2)

/**
 * Type declaration for Linked Lists
 */
typedef struct llist llist;

/**
 * Creates a linked list.
 * 
 * Returns a pointer to type llist.
 * 
 * type: Specifis if the list is Singly or Doubly.
 * 	DOUBLY
 * 	SINGLY
 * 
 * circularly: Is the list Circularly? TRUE or FALSE
 * 	TRUE
 * 	FALSE
 * 
 * datacpy: User defined function to copy data from src to dest.
 * 
 * datacmp: User defined function to compare data1 and data2.
 *
 * 			Return:
 * 				 1 if data1 > data2
 * 				 0 if data1 == data2
 * 				-1 if data1 < data2
 * 
 * datafree: User defined fucntion to free data stored in linked list.
 */
llist* llist_create(int type, int circularly, 
						void (*datacpy)(void *dest, void *src), 
						int (*datacmp)(void *data1, void *data2),
						void (*datafree)(void **data));


/**
 * Inserts user data into the linked list following insert_point. 
 * 
 * If nth_mode is set to TRUE, insert_point will be an intiger pointer 
 * 	specifiying the nth item the list. The new data will be inserted after 
 * 	the nth item.
 *  Head can be specified by  0.
 *  Tail can be specified by -1.
 * 
 * If nth_mode is set to FALSE, insert_point will be data already in the list 
 * 	that the new data will be inserted after.
 * 
 * To insert at the Head of the list, set nth_mode to FALSE and 
 * 	insert_point to NULL.
 */
void llist_insert(llist *list, int nth_mode, void *insert_point, 
					void *data, size_t size);


/**
 * Finds the stored void *data that matches the passed item.
 * 
 * Returns the nth instance of a match or NULL on Failure.
 */
void* llist_find(llist *list, int nth_mode, void *item, size_t nth_instance);


/**
 * Sorts a linked list using Bubble Sort placing all nodes
 * in alphanumerical order.
 */
void llist_sort(llist *list);


/**
 * Deletes the first instance of the specified data.
 * If data is NULL, the entire list will be removed, however the list will still 
 * exist, with no data, until llist_destroy is called on it.
 * 
 * Returns 0 if a node is deleted.
 * Returns 1 if data is not found and/or a node is not deleted.
 */
int llist_delete(llist *list, int nth_mode, void *data);


/**
 * Destroys the linked list.
 */
void llist_destroy(llist **list);


/**
 * Print the linked list.
 */
void llist_print(llist *list, void (*data_print)(void *data));


/**
 * Get the size of the list.
 */
size_t llist_size(llist *list);


/**
 * Compare an item from the list with the item passed.
 */
int llist_cmp(llist *list, void *data1, void *data2);

#endif /* LIST_H_CUHSMAN */