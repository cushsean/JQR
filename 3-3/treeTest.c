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
	// addLeaf(tree, "Brad", strlen("Brad"));
	// addLeaf(tree, "Ben", strlen("Ben"));
	// addLeaf(tree, "Chelsea", strlen("Chelsea"));
	// addLeaf(tree, "Julie", strlen("Julie"));
	// addLeaf(tree, "Zac", strlen("Zac"));
	// addLeaf(tree, "Wilma", strlen("Wilma"));
	// addLeaf(tree, "Ben", strlen("Ben"));


	printf("size  : %d\ndepth : %d\n\n", tree->size, tree->depth);
	printf("Printing Tree...\n");
	ptTree(tree);

	// printf("Remove \"Wilma\"...\n");
	// rmLeaf(tree, tree->root->right->right->left);
	printf("Remove \"WILLIAM\"...\n");
	rmLeaf(tree, &tree->root->right);
	printf("Printing Tree...\n");
	ptTree(tree);

	rmTree(&tree);
	return 0;
}