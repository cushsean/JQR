#ifndef TREE_H_CUHSMAN
#define TREE_H_CUSHMAN

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "list.h"
#include "util.h"

#define BST (0)
#define NORMAL (1)

typedef struct leaf{
	void *data;
	node_t *child;
	size_t children;
	struct leaf *parent;
	struct leaf *left;
	struct leaf *right;
	size_t count;
}leaf_t;

typedef struct tree{
	leaf_t *root;
	int size;
	int depth;
	int type;
	int (*cmp_data)(void*, void*);
	void (*printLeaf)(void*);
}tree_t;


/**
 * Create the metadata for a new tree.
 * Type:
 * "BST" = Binary Search Tree
 * "NORMAL" = Normal Tree
 */
tree_t* createTree(int type, int (*cmp_leaf)(void*, void*), 
					void (*printLeaf)(void*));


/**
 * Inserts a leaf on the tree containing "data".
 */
void addLeaf(tree_t *tree, void *data, size_t size);


/**
 * Prints the contents of a tree based on it's type.
 */
void ptTree(tree_t *tree);


/**
 * Removes a leaf from the tree and frees all reltive addresses.
 */
void rmLeaf(tree_t *tree, leaf_t **leaf);


/**
 * Removes the entire tree and frees all memory.
 */
void rmTree(tree_t **tree);

#endif /* TREE_H_CUSHMAN */