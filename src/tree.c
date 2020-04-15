#include "tree.h"


/**
 * Local Function for printing the contents of a BST.
 */
static void print_bst(leaf_t *root, size_t num, void (*printLeaf)(leaf_t*));


/**
 * Local function for comparing two leafs.
 */
static int cmp_leaf(tree_t *tree, leaf_t *leaf1, leaf_t *leaf2);


static void rm_2_children_bst(tree_t *tree, leaf_t *leaf);
static void rm_1_child(tree_t *tree, leaf_t *leaf, leaf_t *parent);
static void rm_no_children(tree_t *tree, leaf_t *leaf, leaf_t *parent);


tree_t* createTree(int type, int (*cmp_data)(void*, void*), 
					void (*printLeaf)(leaf_t*)){
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
		// size_t depth = 0;
		int new_leaf = 0;
		if(tree->root == NULL){
			tree->root = calloc(1, sizeof(leaf_t));
			curr = tree->root;
			curr->parent = NULL;
			curr->children = curr->count = 0;
		}
		else{
			while(curr != NULL){
				int cmp_int = tree->cmp_data(data, curr->data);
				parent = curr;
				if(cmp_int > 0){
					curr = curr->right;
					new_leaf = 1;
				}
				else if(cmp_int < 0){
					curr = curr->left;
					new_leaf = -1;
				}
				else{
					curr->count++;
					tree->size++;
					new_leaf = 0;
					if(curr == tree->root)
						tree->root->parent = NULL;
					return;
				}
				// depth++;
			}
			parent->children++;
			if(parent->child == NULL)
				parent->child = mkList(2, DOUBLY);
			if(new_leaf == 1){
				parent->right = calloc(1, sizeof(leaf_t));
				parent->child->next->data = parent->right;
				curr = parent->right;
			}
			else if(new_leaf == -1){
				parent->left = calloc(1, sizeof(leaf_t));
				parent->child->data = parent->left;
				curr = parent->left;
			}
		}
		if(new_leaf != 0)
			curr->children = curr->count = 0;
		curr->parent = parent;
		curr->data = malloc(size);
		memcpy(curr->data, data, size);
		curr->data_size = size;
		
		tree->size++;
		// if(depth > tree->depth)
		// 	tree->depth = depth;
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


static void print_bst(leaf_t *root, size_t num, void (*printLeaf)(leaf_t*)){
	// Navigates the tree in "REVERSE-INORDER"
	if(root == NULL)
		return;
	
	num++;
	
	print_bst(root->right, num, printLeaf);
	
	printf("\n\n");
	for(int i=0; i<num; i++)
		printf("\t");
	(*printLeaf)(root);
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

leaf_t* findLeaf(tree_t *tree, void *data){
	if(tree->root == NULL)
		return NULL;
	if(tree->type == BST){
		leaf_t *curr = tree->root;
		while(curr->data != NULL){
			int cmp_int = tree->cmp_data(data, curr->data);
			if(cmp_int > 0)
				curr = curr->right;
			else if(cmp_int < 0)
				curr = curr->left;
			else
				return curr;
		}
	}
	return NULL;
}


node_t* findChild(tree_t *tree, leaf_t *parent, void *data){
	node_t *curr = parent->child;
	while(curr->data == NULL)
		curr = curr->next;
	while(tree->cmp_data(data, ((leaf_t*)curr->data)->data) != 0){
		curr = curr->next;
		if(curr == NULL){
			fprintf(stderr, "Data not found in a child of the parent\n");
			return NULL;
		}
	}
	return curr;
}


static void rm_no_children(tree_t *tree, leaf_t *leaf, leaf_t *parent){
	if(parent == NULL){
		free(leaf->data);
		leaf->data = NULL;
		free(leaf);
		leaf = NULL;
		return;
	}
	node_t *kid = findChild(tree, parent, leaf->data);
	if(kid == NULL)
		return;
	if(tree->type == BST){
		if(kid == parent->child)
			parent->left = NULL;
		else
			parent->right = NULL;
	}
	parent->children--;
	
	// Free the leaf's data
	free(leaf->data);
	leaf->data = NULL;

	// // Free child node_t
	// if(tree->type = BST){
	// 	free(leaf->child->next);
	// 	leaf->child->next = NULL;
	// 	free(leaf->child);
	// 	leaf->child = NULL;
	// }
	
	// Free the leaf from the parent's child node
	free(kid->data);
	kid->data = NULL;

	if(parent->children == 0){
		// Free parent's other child nodes
		if(kid->next != NULL){
			free(kid->next);
			kid->next = NULL;
		}
		else if(kid->prev != NULL){
			free(kid->prev);
			kid->prev = NULL;
		}
		// Free the kid node
		free(kid);
		kid = NULL;
	}
	else if(tree->type != BST){
		// Unlink kid node
		node_t *tmp = kid->prev;
		if(kid->next != NULL)
			kid->next->prev = tmp;
		if(tmp == NULL)
			parent->child = kid->next;
		else
			tmp->next = kid->next;
		// Free the kid node
		free(kid);
		kid = NULL;
	}
	
	
	return;
}
static void rm_1_child(tree_t *tree, leaf_t *leaf, leaf_t *parent){
	node_t *leafs_kid = leaf->child;

	while(leafs_kid->data == NULL){
		leafs_kid = leafs_kid->next;
	}
	if(parent == NULL){
		tree->root = leafs_kid->data;
		tree->root->parent = NULL;
	}
	else{
		node_t *parents_kid = findChild(tree, parent, leaf->data);
		parents_kid->data = leafs_kid->data;
		if(tree->type == BST){
			if(leaf == parent->left)
				parent->left = leafs_kid->data;
			else
				parent->right = leafs_kid->data;
		}
		((leaf_t*)leafs_kid->data)->parent = parent;
	}


	// Free leaf's other child nodes
	if(leafs_kid->next != NULL){
		free(leafs_kid->next);
		leafs_kid->next = NULL;
	}
	else if(leafs_kid->prev != NULL){	
		free(leafs_kid->prev);
		leafs_kid->prev = NULL;
	}

	// Free the leaf's child node
	free(leafs_kid);
	leafs_kid = NULL;

	// Free the leaf's data
	free(leaf->data);
	leaf->data = NULL;

	// Free the leaf
	free(leaf);
	leaf = NULL;

	return;
}

static void rm_2_children_bst(tree_t *tree, leaf_t *leaf){
	leaf_t *shift_leaf = leaf->right;
	while(shift_leaf->left != NULL)
		shift_leaf = shift_leaf->left;
	memset(leaf->data, '\0', leaf->data_size);
	leaf->data_size = shift_leaf->data_size;
	memcpy(leaf->data, shift_leaf->data, shift_leaf->data_size);
	leaf->count = shift_leaf->count;
	rmLeaf(tree, shift_leaf);
	// rmLeaf will reduce tree size; need to counter for recursion.
	tree->size++;

	return;
}

void rmLeaf(tree_t *tree, leaf_t *leaf){
	if(leaf->count > 0){
		leaf->count--;
		tree->size--;
		return;
	}
	
	leaf_t *parent = leaf->parent;

	if(leaf->children == 0)
		rm_no_children(tree, leaf, parent);
	else if(leaf->children == 1)
		rm_1_child(tree, leaf, parent);
	else if(tree->type == BST)
		rm_2_children_bst(tree, leaf);

	tree->size--;

	return;
}


void rmTree(tree_t **tree){
	while((*tree)->size != 0){
		rmLeaf(*tree, (*tree)->root);
		ptTree(*tree);
	}
	free(*tree);
	tree = NULL;
}