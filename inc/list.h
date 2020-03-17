#ifndef LIST_H_CUSHMAN
#define LIST_H_CUSHMAN

#include <stdlib.h>
#include <stdio.h>

#define CIRCULARLY (0)
#define DOUBLY (1)
#define SINGLY (2)

typedef struct node{
	void* data;
	int type;
	struct node *next;
	struct node *prev;
}node_t;

typedef node_t* (*func_t)(node_t*);
// typedef void (*free_data)(void*);

node_t* mkNode(int);
node_t* mkList(int, int);
void ptList(node_t*, void (*print_ptr)(void*));
node_t* find_node(node_t*, void*, int (*cmp_ptr)(void*, void*));
node_t* sort_node(node_t*);
node_t* rmNode(node_t*, void*, int);
node_t* insert_at_head(node_t*, node_t*, node_t*);
void insert_node(node_t*, void*, void*);
void rm_all_nodes(node_t*);
node_t* get_tail(node_t*);

int countList(node_t *head);


/**
 * Frees the address held by void* that
 * contains an int.
 * Sets address to NULL after freeing
 **/
void free_node(node_t *head);


#endif /* LIST_H_CUHSMAN */