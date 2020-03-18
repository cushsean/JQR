#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"
#include "tree.h"

int main(){
	srand(time(NULL));
	tree_b* root = mkTree_bst(15);
	ptTree_bst_int(root);
	int tmp = rand()%20;
	printf("finding %d...\n", tmp);
	void* ptr = &tmp;
	tree_b* leaf = find_leaf_bst(root, ptr);
	if(leaf != NULL)
		printf("The node with value %d has children %d(l) and %d(r)\n",
			*((int*)leaf->data),
			(leaf->left == NULL ? -1 : *((int*)leaf->left->data)),
			(leaf->right == NULL ? -1 : *((int*)leaf->right->data))
		);
	rmLeaf_bst(root, leaf->data);
	ptTree_bst_int(root);
	return 0;
}