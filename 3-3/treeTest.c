#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "list.h"
#include "tree.h"

void print_leaf(leaf_t* leaf){
	if(leaf == NULL)
		printf("\"NULL\"");
	else
		print_str(leaf->data);
	return;
}


int main(){
	tree_t *tree = createTree(BST, cmp_str, print_leaf);
	addLeaf(tree, "SEAN", strlen("SEAN"));
	addLeaf(tree, "WILLIAM", strlen("WILLIAM"));
	addLeaf(tree, "Brad", strlen("Brad"));
	addLeaf(tree, "Ben", strlen("Ben"));
	addLeaf(tree, "Chelsea", strlen("Chelsea"));
	addLeaf(tree, "Julie", strlen("Julie"));
	addLeaf(tree, "Zac", strlen("Zac"));
	addLeaf(tree, "Wilma", strlen("Wilma"));
	addLeaf(tree, "Ben", strlen("Ben"));
	addLeaf(tree, "SEAN", strlen("SEAN"));
	addLeaf(tree, "SEAN", strlen("SEAN"));


	// printf("size  : %d\ndepth : %d\n\n", tree->size, tree->depth);
	printf("Printing Tree...\n");
	printf("size: %d\n", tree->size);
	ptTree(tree);

	printf("Find \"Ben\"...\n");

	tree->printLeaf(findLeaf(tree, "Ben"));
	printf("\n\n");

	// Declare "leaf" for later use.
	leaf_t *leaf = NULL;

	// Remove leaf with no children
	
	leaf = findLeaf(tree, "Wilma");
	printf("Remove \"%s\"...\n", (char*)leaf->data);
	rmLeaf(tree, leaf);

	printf("Printing Tree...\n");
	printf("size: %d\n", tree->size);
	ptTree(tree);

	// Remove leaf with cound greater than 0
	leaf = findLeaf(tree, "SEAN");
	printf("Remove \"%s\"...\n", (char*)leaf->data);
	rmLeaf(tree, leaf);

	printf("Printing Tree...\n");
	printf("size: %d\n", tree->size);
	ptTree(tree);

	// Remove leaf with 1 child
	leaf = findLeaf(tree, "Chelsea");
	printf("Remove \"%s\"...\n", (char*)leaf->data);
	rmLeaf(tree, leaf);

	printf("Printing Tree...\n");
	printf("size: %d\n", tree->size);
	ptTree(tree);

	// Remove leaf with 2 children
	leaf = findLeaf(tree, "Brad");
	printf("Remove \"%s\"...\n", (char*)leaf->data);
	rmLeaf(tree, leaf);

	printf("Printing Tree...\n");
	printf("size: %d\n", tree->size);
	ptTree(tree);

	rmTree(&tree);
	return 0;
}