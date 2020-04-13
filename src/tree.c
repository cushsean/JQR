#include "tree.h"


/**
 * Local Function for printing the contents of a BST.
 */
static void print_bst(leaf_t *root, size_t num, void (*printLeaf)(void*));


/**
 * Local function for comparing two leafs.
 */
static int cmp_leaf(tree_t *tree, leaf_t *leaf1, leaf_t *leaf2);


tree_t* createTree(int type, int (*cmp_data)(void*, void*), 
					void (*printLeaf)(void*)){
	tree_t *tree = malloc(sizeof(tree_t));
	tree->root = NULL;
	tree->size = 0;
	tree->depth = 0;
	tree->type = type;
	tree->cmp_data = cmp_data;
	tree->printLeaf = printLeaf;
	return tree;
}


void addLeaf(tree_t *tree, void *data, size_t size){
	if(tree->type == BST){
		leaf_t *curr = tree->root;
		leaf_t *parent = NULL;
		size_t depth = 0;
		while(curr != NULL){
			if(tree->cmp_data(data, curr->data) > 0){
				if(curr->right == NULL){
					parent = curr;
					parent->right = malloc(sizeof(leaf_t));
					parent->child->next->data = parent->right;
					parent->children++;
					curr = parent->right;
					curr->parent = parent;
					depth++;
					break;
				}
				curr = curr->right;
			}
			else if(tree->cmp_data(data, curr->data) < 0){
				if(curr->left == NULL){
					parent = curr;
					parent->left = malloc(sizeof(leaf_t));
					parent->child->data = parent->left;
					parent->children++;
					curr = parent->left;
					curr->parent = parent;
					depth++;
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
		curr->child = mkList(2, DOUBLY);
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


void addLeaf2(tree_t *tree, void *data, size_t size){
	if(tree->type == BST){
		leaf_t *curr = tree->root;
		leaf_t *parent = NULL;
		size_t depth = 0;
		while(curr != NULL){
			int cmp_int = tree->cmp_data(data, curr->data);
			parent = curr;
			if(cmp_int > 0)
				curr = curr->right;
			else if(cmp_int < 0)
				curr = curr->left;
			else{
				curr->count++;
				break;
			}
			depth++;
		}
		if(curr == NULL){
			if(curr == tree->root)
				curr = malloc(sizeof(leaf_t));
			else
				parent->children++;
			curr->child = mkList(2, DOUBLY);
			curr->child->data = calloc(1, sizeof(leaf_t));
			curr->child->next->data = calloc(1, sizeof(leaf_t));
			curr->left = curr->child->data;
			curr->right = curr->child->next->data;
			curr->children = curr->count = 0;
			curr->parent = parent;
			curr->data = malloc(size);
			memcpy(curr->data, data, size);
			
			tree->size++;
			if(depth > tree->depth)
				tree->depth = depth;
			if(tree->root == NULL)
				tree->root = curr;
		}
	}
	return;
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
	// Navigates the tree in "REVERSE-INORDER"
	if(root == NULL)
		return;
	
	num++;
	
	print_bst(root->right, num, printLeaf);
	
	printf("\n\n");
	for(int i=0; i<num; i++)
		printf("\t");
	(*printLeaf)(root->data);
	if(root->count > 0)
		printf("(%ld)", root->count);
	
	print_bst(root->left, num, printLeaf);
	
	return;
}


static int cmp_leaf(tree_t *tree, leaf_t *leaf1, leaf_t *leaf2){
	if(leaf1 == NULL || leaf2 == NULL)
		return 1;
	return tree->cmp_data(leaf1->data, leaf2->data);
}


void rmLeaf(tree_t *tree, leaf_t **leaf){
	leaf_t *parent = (*leaf)->parent;
	node_t *child = parent->child->next;
	*leaf = NULL;
	// while(1==1);
	// if(leaf->count > 0){
	// 	leaf->count--;
	// 	return;
	// }
	// if(leaf != tree->root){
	// 	leaf_t *parent = leaf->parent;
	// 	printf("parent: %s\n", (char*)parent->data);
	// 	printf("leaf: %s\n", (char*)leaf->data);
	// 	node_t *curr_child = parent->child;
	// 	for(; curr_child != NULL; curr_child = curr_child->next){	
	// 		if(cmp_leaf(tree, curr_child->data, leaf) == 0)
	// 			break;
	// 	}
	// 	if(tree->type == BST){
	// 		if(tree->cmp_data(leaf->data, parent->data))
	// 			parent->right = NULL;
	// 		else
	// 			parent->left = NULL;
	// 		// free(curr_child->data);
	// 		curr_child->data = NULL;
	// 	}
	// 	else{
	// 		rmNode(parent->child, curr_child);
	// 	}
	// }
	// free(leaf->data);
	// leaf->data = NULL;

	// // No children only
	// rm_all_nodes(leaf->child);
	
	// free(leaf);
	// leaf = NULL;

	
	return;
}


void rmTree(tree_t **tree){
	while((*tree)->root != NULL)
		// rmLeaf(*tree, (*tree)->root);
	free(*tree);
	tree = NULL;
}