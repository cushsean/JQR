#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "list.h"
#include "tree.h"


int main(){
	tree_t *tree = createTree(BST, cmp_str, print_str);
	addLeaf(tree, "SEAN", strlen("SEAN"));
	addLeaf(tree, "WILLIAM", strlen("WILLIAM"));
	addLeaf(tree, "HAPPY BIRTHDAY BABE!!!!", strlen("HAPPY BIRTHDAY BABE!!!!"));
	

	printf("size  : %d\ndepth : %d\n\n", tree->size, tree->depth);
	ptTree(tree);

	printf("root  : %s\n", (char*)tree->root->data);
	printf("right : %s\n", (char*)tree->root->right->data);
	printf("left : %s\n", (char*)tree->root->left);
	return 0;
}