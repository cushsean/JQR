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
 * Inserts a leaf in a BST containing "data".
 */
void addLeaf_BST(tree_t *tree, void *data, size_t size);


/**
 * Insert a leaf in a tree as a child to the given parent containing "data".
 */
void addLeaf(tree_t *tree, leaf_t *parent, void *data, size_t size);


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
 * count is greater than 0, the count will only be reduce by 1 and the leaf 
 * will remain in the tree. For non-BST leafs that contain more then 1 child, 
 * use rmLeaf_Extended, unless your desire is to remove the all the leafs 
 * children including their subtrees.
 */
void rmLeaf(tree_t *tree, leaf_t *leaf);


/**
 * An extended varient of rmLeaf designed for non-BST leaves that contain more 
 * than 1 child. "Child" will be the leaf's child that will assume the parental
 * role and adopt their siblings.
 * 
 * The extended varient can be used for all tree types and leaves. For all 
 * leaves, other than non-BST leaves containing more the 1 child, passing NULL 
 * for "child" will simulate the functions of the standard variant, rmLeaf.
 * 
 * Passing NULL for the child on a non-BST leaf with more than 1 child will 
 * remove the leaf and all its children, including their subtrees.
 */
void rmLeaf_Extended(tree_t *tree, leaf_t *leaf, leaf_t *child);


/**
 * Removes the entire tree and frees all memory.
 */
void rmTree(tree_t **tree);

#endif /* TREE_H_CUSHMAN */