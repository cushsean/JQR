#include "tree.h"


/**
 * Local Function for printing the contents of a BST.
 */
static void print_bst(leaf_t *root, size_t num, void (*printLeaf)(leaf_t*));


/**
 * Local Function for printing the contents of a non-BST tree.
 */
static void print_tree(leaf_t *root, size_t num, void (*printLeaf)(leaf_t*));


/**
 * Local Function for finding a child in a non-BST tree. findLeaf acts as
 * wrapper function.
 */
static leaf_t* findLeaf_nonBST(leaf_t *root, void *data, 
								int (*cmp_leaf)(void*, void*));


/**
 * Local Function for comparing two leafs.
 */
static int cmp_leaf(tree_t *tree, leaf_t *leaf1, leaf_t *leaf2);


/**
 * Local Function to perform a LR rotation.
 */
static void rotation_LR(tree_t *tree, leaf_t *root);


/**
 * Local Function to perform a LL rotation.
 */
static void rotation_LL(tree_t *tree, leaf_t *root);


/**
 * Local Function to perform a RL rotation.
 */
static void rotation_RL(tree_t *tree, leaf_t *root);


/**
 * Local Function to perform a RR rotation.
 */
static void rotation_RR(tree_t *tree, leaf_t *root);


/**
 * Local Function used prior to rotation in AVL trees to update height and BF 
 * from the newly inserted leaf to root only.
 */
static void updateBF(tree_t *tree, leaf_t *leaf);


/**
 * Local Function used after rotation in AVL trees to update height and BF 
 * from root through the entire tree.
 */
static int updateHeight(tree_t *tree, leaf_t *root);


/**
 * Local Function for removing a leaf with 2 children.
 */
static void rm_2_children_bst(tree_t *tree, leaf_t *leaf);


/**
 * Local Function for removing a leaf with 1 child.
 */
static void rm_1_child(tree_t *tree, leaf_t *leaf, leaf_t *parent);


/**
 * Local Function for removing a leaf with no children.
 */
static void rm_no_children(tree_t *tree, leaf_t *leaf, leaf_t *parent);


/**
 * Local Function for removing a leaf with 2 or more children from a non-BST.
 * Child leaf is the child of the leaf that will take the place of its parent
 * and adopt its siblings. If NULL is passed for "child" all children and their 
 * subtree's will be removed as well.
 */
static void rm_multi_children(tree_t *tree, leaf_t *leaf, leaf_t *parente,
								leaf_t *child);


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


void addLeaf_BST(tree_t *tree, void *data, size_t size){
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
	curr->bf = 0;
	curr->height = 1;
	balanceTree(tree, curr);
	
	tree->size++;
	// if(depth > tree->depth)
	// 	tree->depth = depth;

	return;
}

void addLeaf(tree_t *tree, leaf_t *parent, void *data, size_t size){
	
	// // Debugging tool; Remove before release.
	// printf("NOTE: Adding leaf ");
	// print_str(data);
	// printf(" with parent ");
	// tree->printLeaf(parent);
	// printf("\n");
	// //////////////////////////////////////////

	leaf_t *leaf = NULL;

	if(tree->root == NULL){
		tree->root = calloc(1, sizeof(leaf_t));
		leaf = tree->root;
	}
	
	else if(parent == NULL){
		fprintf(stderr, "Parent leaf NULL, cannot add new leaf to tree.\n");
		return;
	}

	else{
		parent->child = insert_at_head(parent->child, 
										get_tail(parent->child), 
										mkNode(DOUBLY));
		parent->child->data = calloc(1, sizeof(leaf_t));
		leaf = parent->child->data;
		// Must set parent before ending else statment since tree->root
		// maintains NULL as parent.
		leaf->parent = parent;
		parent->children++;
	}

	// Used for both tree->root and other children
	leaf->data = malloc(size);
	memcpy(leaf->data, data, size);
	leaf->data_size = size;
	tree->size++;

	return;
}


void ptTree(tree_t *tree){
	switch(tree->type){
		case BST:
			print_bst(tree->root, 0, tree->printLeaf);
			break;
		default:
			print_tree(tree->root, 0, tree->printLeaf);
			// printf("Currently no print method for this type of tree.\n");
			break;
	}
	printf("\n\n");
	return;
}


static void print_tree(leaf_t *root, size_t num, void (*printLeaf)(leaf_t*)){
	// Navigates the tree in "PREORDER"
	for(int i=0; i<=num; i++)
		printf("\t");
	(*printLeaf)(root);
	printf("\n\n");
	num++;
	node_t *child = root->child;
	while(child != NULL){
		print_tree(child->data, num, printLeaf);
		child = child->next;
	}
	
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

static leaf_t* findLeaf_nonBST(leaf_t *root, void *data, 
								int (*cmp_leaf)(void*, void*)){
	if((*cmp_leaf)(data, root->data) == 0)
		return root;
	node_t *child = root->child;
	while(child != NULL){
		leaf_t *leaf = findLeaf_nonBST(child->data, data, cmp_leaf);
		if(leaf != NULL)
			return leaf;
		child = child->next;
	}
	return NULL;
}

leaf_t* findLeaf(tree_t *tree, void *data){
	leaf_t *leaf = NULL;
	if(tree->type != BST){
		leaf = findLeaf_nonBST(tree->root, data, tree->cmp_data);
		return leaf;
	}
	leaf = tree->root;
	while(leaf != NULL){
		int cmp_int = tree->cmp_data(data, leaf->data);
		if(cmp_int > 0)
			leaf = leaf->right;
		else if(cmp_int < 0)
			leaf = leaf->left;
		else
			return leaf;
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

static void rotation_LR(tree_t *tree, leaf_t *root){
	ptTree(tree);
	printf("\tLR\n");
	leaf_t *A = root;
	leaf_t *B = root->left;
	leaf_t *C = B->right;
	leaf_t *Cr = C->right;
	leaf_t *Cl = C->left;
	leaf_t *parent = root->parent;

	// Update parent of sub-tree
	if(root->parent != NULL){
		if(parent->left == A)
			parent->left = parent->child->data = C;
		else
			parent->right = parent->child->next->data = C;
	}
	else
		tree->root = C;

	// Update children
	if(C->child == NULL)
		C->child = mkList(2, DOUBLY);
	C->right = C->child->next->data = A;
	A->left = A->child->data = Cr;
	C->left = C->child->data = B;
	B->right = B->child->next->data = Cl;

	// Update parents
	if(Cl != NULL)
		Cl->parent = B;
	if(Cr != NULL)
		Cr->parent = A;
	A->parent = C;
	B->parent = C;
	C->parent = parent;

	ptTree(tree);
	return;
}

static void rotation_LL(tree_t *tree, leaf_t *root){
	ptTree(tree);
	printf("\tLL\n");
	leaf_t *A = root;
	leaf_t *B = root->left;
	leaf_t *Br = B->right;
	leaf_t *parent = root->parent;

	// Update parent of sub-tree
	if(root->parent != NULL){
		if(parent->left == A)
			parent->left = parent->child->data = B;
		else
			parent->right = parent->child->next->data = B;
	}
	else
		tree->root = B;

	// Update children
	B->right = B->child->next->data = A;
	A->left = A->child->data = Br;

	// Update parents
	B->parent = parent;
	A->parent = B;
	if(Br != NULL)
		Br->parent = A;
	
	ptTree(tree);
	return;
}

static void rotation_RL(tree_t *tree, leaf_t *root){
	ptTree(tree);
	printf("\tRL\n");
	leaf_t *A = root;
	leaf_t *B = A->right;
	leaf_t *C = B->left;
	leaf_t *Cl = C->left;
	leaf_t *Cr = C->right;
	leaf_t *parent = root->parent;

	// Update parent of sub-tree
	if(root->parent != NULL){
		if(parent->left == A)
			parent->left = parent->child->data = C;
		else
			parent->right = parent->child->next->data = C;
	}
	else
		tree->root = C;

	// Update children
	if(C->child == NULL)
		C->child = mkList(2, DOUBLY);
	C->left = C->child->data = A;
	C->right = C->child->next->data = B;
	A->right = A->child->next->data = Cl;
	B->left = B->child->data = Cr;

	// Update parents
	C->parent = parent;
	A->parent = C;
	B->parent = C;
	if(Cl != NULL)
		Cl->parent = A;
	if(Cr != NULL)
		Cr->parent = B;

	ptTree(tree);
	return;
}

static void rotation_RR(tree_t *tree, leaf_t *root){
	ptTree(tree);
	printf("\tRR\n");
	leaf_t *A = root;
	leaf_t *B = root->right;
	leaf_t *Bl = B->left;
	leaf_t *parent = root->parent;

	// Update parent of sub-tree
	if(root->parent != NULL){
		if(parent->left == A)
			parent->left = parent->child->data = B;
		else
			parent->right = parent->child->next->data = B;
	}
	else
		tree->root = B;

	// Update children
	B->left = B->child->data = A;
	A->right =  A->child->next->data = Bl;

	// Update parents
	B->parent = parent;
	A->parent = B;
	if(Bl != NULL)
		Bl->parent = A;

	ptTree(tree);
	return;
}

// Update BF prior to rotation to determine if a rotation is necessary.
static void updateBF(tree_t *tree, leaf_t *leaf){
	int left = 0; 
	int right = 0;
	
	if(leaf->left != NULL)
		left = leaf->left->height;
	if(leaf->right != NULL)
		right = leaf->right->height;
	
	leaf->bf = left - right;
	if(abs(leaf->bf) > 1){
		if(leaf->bf == 2){
			if(leaf->left->bf == 1)
				rotation_LL(tree, leaf);
			else
				rotation_LR(tree, leaf);
		}
		else if(leaf->bf == -2){
			if(leaf->right->bf == 1)
				rotation_RL(tree, leaf);
			else
				rotation_RR(tree, leaf);
		}
		return;
	}
	if(leaf->parent == NULL)
		return;
	
	if(leaf->parent->height <= leaf->height)
		leaf->parent->height = leaf->height+1;
	return updateBF(tree, leaf->parent);
}

// Update the height after a rotation from tree->root.
static int updateHeight(tree_t *tree, leaf_t *root){
	int left = 0; 
	int right = 0;

	root->children = 0;
	
	if(root->left != NULL){
		left = updateHeight(tree, root->left);
		if(left == -1)
			return -1;
		root->children++;
	}
	if(root->right != NULL){
		right = updateHeight(tree, root->right);
		if(right == -1)
			return -1;
		root->children++;
	}

	if(left > right)
		root->height = left;
	else
		root->height = right;

	root->bf = left - right;
	if(abs(root->bf) > 1){
		if(root->bf == 2){
			if(root->left->bf == 1)
				rotation_LL(tree, root);
			else
				rotation_LR(tree, root);
		}
		else if(root->bf == -2){
			if(root->right->bf == 1)
				rotation_RL(tree, root);
			else
				rotation_RR(tree, root);
		}
		return -1;
	}
	
	return ++root->height;
}

void balanceTree(tree_t *tree, leaf_t *newLeaf){
	if(tree->type != BST){
		fprintf(stderr, "Cannot balance trees that are not BSTs.\n");
		return;
	}
	if(newLeaf != NULL)
		updateBF(tree, newLeaf);
	int root_height = -1;
	while(root_height == -1){
		root_height = updateHeight(tree, tree->root);
	}

	return;
}


static void rm_no_children(tree_t *tree, leaf_t *leaf, leaf_t *parent){
	while(leaf->child != NULL){
		node_t *tmp = leaf->child->next;
		if(leaf->child->data != NULL)
			rmLeaf(tree, leaf->child->data);
		else{
			free(leaf->child);
			leaf->child = tmp;
		}
	}
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
		parent->child = kid = NULL;
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
	// Get the least right-hand child
	leaf_t *shift_leaf = leaf->right;
	while(shift_leaf->left != NULL)
		shift_leaf = shift_leaf->left;
	
	// Prepare for data transfer
	memset(leaf->data, '\0', leaf->data_size);
	leaf->data_size = shift_leaf->data_size;

	// Transfer data
	memcpy(leaf->data, shift_leaf->data, shift_leaf->data_size);
	leaf->count = shift_leaf->count;

	// Remove original copy
	shift_leaf->count = 0;
	rmLeaf(tree, shift_leaf);
	// rmLeaf will reduce tree size; need to counter for recursion.
	tree->size++;

	return;
}

static void rm_multi_children(tree_t *tree, leaf_t *leaf, 
								leaf_t *parent, leaf_t *child){
	if(child == NULL){
		node_t *kid = leaf->child;
		while(kid != NULL){
			node_t *tmp = kid->next;
			rmLeaf(tree, kid->data);
			kid = tmp;
		}
		// rmLeaf will reduce tree size; need to counter for recursion.
		tree->size++;
		rmLeaf(tree, leaf);

		return;
	}


	//////////////////////////////////////////////
	// FUCNTIONALITY FOR WHEN CHILD IS NOT NULL //
	//////////////////////////////////////////////

	memset(leaf->data, '\0', leaf->data_size);
	leaf->data_size = child->data_size;
	memcpy(leaf->data, child->data, child->data_size);
	leaf->count = child->count;
	// rmLeaf will reduce tree size; need to counter for recursion.
	tree->size++;
	rmLeaf(tree, child);

	return;
}

void rmLeaf(tree_t *tree, leaf_t *leaf){
	rmLeaf_Extended(tree, leaf, NULL);
	return;
}

void rmLeaf_Extended(tree_t *tree, leaf_t *leaf, leaf_t *child){
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
	else
		rm_multi_children(tree, leaf, parent, child);

	tree->size--;
	if(tree->type == BST)
		balanceTree(tree, NULL);

	return;
}


void rmTree(tree_t **tree){
	while((*tree)->size != 0)
		rmLeaf(*tree, (*tree)->root);
	free(*tree);
	tree = NULL;
}