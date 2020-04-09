#include "tree.h"


/**
 * Local Function for printing the contents of a BST.
 */
static void print_bst(leaf_t *root, size_t num, void (*printLeaf)(void*));


tree_t* createTree(int type, int (*cmp_leaf)(void*, void*), 
					void (*printLeaf)(void*)){
	tree_t *tree = malloc(sizeof(tree_t));
	tree->root = NULL;
	tree->size = 0;
	tree->depth = 0;
	tree->type = type;
	tree->cmp_leaf = cmp_leaf;
	tree->printLeaf = printLeaf;
	return tree;
}


void addLeaf(tree_t *tree, void *data, size_t size){
	if(tree->type == BST){
		leaf_t *curr = tree->root;
		size_t depth = 0;
		while(curr != NULL){
			if(tree->cmp_leaf(data, curr->data) > 0){
				if(curr->right == NULL){
					curr->right = malloc(sizeof(leaf_t));
					curr = curr->right;
					break;
				}
				curr = curr->right;
			}
			else if(tree->cmp_leaf(data, curr->data) < 0){
				if(curr->left == NULL){
					curr->left = malloc(sizeof(leaf_t));
					curr = curr->left;
					break;
				}
				curr = curr->left;
			}
			else{
				curr->count++;
				return;
			}
			depth++;
		}
		if(curr == NULL)
			curr = malloc(sizeof(leaf_t));
		curr->child = calloc(2, sizeof(leaf_t*));
		curr->left = curr->child[0];
		curr->right = curr->child[1];
		curr->children = curr->count = 0;
		curr->data = malloc(size);
		memcpy(curr->data, data, size);

		tree->size++;
		if(depth > tree->depth)
			tree->depth = depth;
		if(tree->root == NULL)
			tree->root = curr;
		return;
	}
}


void ptTree(tree_t *tree){
	switch(tree->type){
		case BST:
			print_bst(tree->root, 0, tree->printLeaf);
			break;
		default:
			printf("Currently no print method for this type of tree.\n");
			break;
	}
	printf("\n\n");
	return;
}


static void print_bst(leaf_t *root, size_t num, void (*printLeaf)(void*)){	
	if(root == NULL)
		return;
	
	num++;
	
	print_bst(root->right, num, printLeaf);
	
	printf("\n");
	for(int i=0; i<num; i++)
		printf("\t");
	(*printLeaf)(root->data);
	
	print_bst(root->left, num, printLeaf);
	
	return;
}