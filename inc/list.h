#ifndef LIST_H_CUSHMAN
#define LIST_H_CUSHMAN

#include <stdlib.h>
#include <stdio.h>

#define CIRCULARLY (0)
#define DOUBLY (1)
#define SINGLY (2)

typedef struct node{
	void *data;
	int type;
	struct node *next;
	struct node *prev;
}node_t;

typedef node_t* (*func_t)(node_t*);
// typedef void (*free_data)(void*);


/**
 * Creates a new node for the list of type "l_type".
 * All other values set to NULL.
 * 
 * l_type:
 * 	CIRCULARLY
 * 	DOUBLY
 * 	SINGLY
 * 
 * Returns the created node.
 */
node_t* mkNode(int l_type);


/**
 * Creates a new list with "num" number of elements, all of type "l_type".
 * If the list is to contain data which has been malloced, the nodes in the list
 * will need to be freed using one or more of the free fucntions included in
 * this library.
 * 
 * l_type:
 * 	CIRCULARLY
 * 	DOUBLY
 * 	SINGLY
 * 
 * Returns the head of the list.
 */
node_t* mkList(int num, int type);


/**
 * Prints the list starting at "*head".
 * 
 * Function pointer for printing data.
 */
void ptList(node_t *head, void (*print_ptr)(void*));


/**
 * Finds a node in the list, starting at "*head", that contains the value
 * "*value".
 * 
 * Function pointer for comparing the data of the node with value.
 * 	Return 0 if values are the same.
 * 	Return 1 if first value is greater than second.
 * 	Return -1 if first value is less than second.
 * 
 * Returns NULL if node is not found, else, returns the node that is found.
 */
node_t* find_node(node_t *head, void *value, int (*cmp_ptr)(void*, void*));


/**
 * Finds a node in the list by name
 */
node_t* find_node_by_name(node_t*);


/**
 * Removes the node "*rm_node". If "*rm_node" is "*head", the head of the list 
 * will be updated.
 * 
 * Returns "*head"
 */
node_t* rmNode(node_t *head, node_t *rm_node);


/**
 * Removes a node that contains "*value". If the desire is to remove all nodes 
 * that contain "*value", set "all" to 1, else, set "all" to 0.
 * 
 * Function pointer for comparing the data of the node with value.
 * 	Return 0 if values are the same.
 * 	Return 1 if first value is greater than second.
 * 	Return -1 if first value is less than second.
 * 
 * Returns "*head". If "*head" is removed, the head will be updated.
 */
node_t* rmNode_by_value(node_t *head, void *value, 
	int (*cmp_ptr)(void*, void*), int all);


/**
 * Inserts a node at the head of the list.
 * 
 * Returns "*head".
 */
node_t* insert_at_head(node_t *head, node_t *tail, node_t *insert);


/**
 * Inserts a new node containing the value "*value" after a node that contains 
 * the value "*after".
 * 
 * Returns "*head".
 */
void insert_node(node_t *head, void *after, void *value);


/**
 * Removes all the nodes in the list.
 */
void rm_all_nodes(node_t *head);


/**
 * Returns the last node in the list.
 */
node_t* get_tail(node_t *head);


/**
 * Returns the number of nodes in the list.
 */
int countList(node_t *head);


/**
 * Frees a node that has malloced data. 
 * after freeing.
 **/
void free_node(node_t *head);


#endif /* LIST_H_CUHSMAN */