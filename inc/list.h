#ifndef LIST_H_CUSHMAN
#define LIST_H_CUSHMAN

typedef struct node{
	void* data;
	struct node *next;
	struct node *prev;
}node_t;

typedef node_t* (*func_t)(node_t*);

node_t* mkNode(void*);
node_t* mkList(int, int);
void ptList(node_t*);
node_t* find_node(node_t*, void*);
node_t* sort_node(node_t*);
node_t* rmNode(node_t*, void*, int);
node_t* insert_at_head(node_t*, node_t*, node_t*);
void insert_node(node_t*, void*, void*);
void rm_all_nodes(node_t*);
node_t* get_tail(node_t*);

#endif /* LIST_H_CUHSMAN */