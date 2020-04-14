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
	size_t data_size;
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
	void (*printLeaf)(leaf_t*);
}tree_t;


/**
 * Create the metadata for a new tree.
 * Type:
 * "BST" = Binary Search Tree
 * "NORMAL" = Normal Tree
 */
tree_t* createTree(int type, int (*cmp_leaf)(void*, void*), 
					void (*printLeaf)(leaf_t*));


/**
 * Inserts a leaf on the tree containing "data".
 */
void addLeaf(tree_t *tree, void *data, size_t size);
// void addLeaf2(tree_t *tree, void *data, size_t size);


/**
 * Prints the contents of a tree based on it's type.
 */
void ptTree(tree_t *tree);


/**
 * Returns a leaf with the data given. Returns NULL if leaf cannot be found.
 */
leaf_t* findLeaf(tree_t *tree, void *data);


/**
 * Returns the child of a leaf with the data give. Returns NULL if no child
 * contains the data given.
 */
node_t* findChild(tree_t *tree, leaf_t *parent, void *data);


/**
 * Removes a leaf from the tree and frees all reltive addresses. If the leaf's 
 * count is greater than 0, * the count will only be reduce by 1 and the leaf 
 * will remain in the tree.
 */
void rmLeaf(tree_t *tree, leaf_t *leaf);


/**
 * Removes the entire tree and frees all memory.
 */
void rmTree(tree_t **tree);

#endif /* TREE_H_CUSHMAN */