#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "list.h"
#include "tree.h"

void print_bst_leaf(leaf_t *leaf){
	if(leaf == NULL)
		printf("\"NULL\"");
	else
		print_str(leaf->data);
	return;
}

void print_leaf(leaf_t *leaf){
	if(leaf == NULL)
		printf("\"NULL\"");
	else{
		print_str(leaf->data);
		if(leaf->children > 0){
			printf("\n\tChildren:\n");
			node_t *curr = leaf->child;
			while(curr != NULL){
				printf("\t");
				print_str(((leaf_t*)curr->data)->data);
			}
		}
	}
}


int main(){
	// BST TREES
	tree_t *tree = createTree(BST, cmp_str, print_bst_leaf);
	addLeaf_BST(tree, "SEAN", strlen("SEAN"));
	addLeaf_BST(tree, "WILLIAM", strlen("WILLIAM"));
	addLeaf_BST(tree, "Brad", strlen("Brad"));
	addLeaf_BST(tree, "Ben", strlen("Ben"));
	addLeaf_BST(tree, "Chelsea", strlen("Chelsea"));
	addLeaf_BST(tree, "Julie", strlen("Julie"));
	addLeaf_BST(tree, "Zac", strlen("Zac"));
	addLeaf_BST(tree, "Wilma", strlen("Wilma"));
	addLeaf_BST(tree, "Ben", strlen("Ben"));
	addLeaf_BST(tree, "SEAN", strlen("SEAN"));
	addLeaf_BST(tree, "SEAN", strlen("SEAN"));


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

	rmLeaf(tree, tree->root->right);

	printf("Printing Tree...\n");
	printf("size: %d\n", tree->size);
	ptTree(tree);

	printf("Destroy the tree...\n");
	rmTree(&tree);
	printf("DONE\n\n");

	
	// NON-BST TREES
	printf("Starting non-BST Trees...\n");

	tree = createTree(NORMAL, cmp_str, print_bst_leaf);
	
	char *parent = NULL;
	char *child = "Grandma & Papa";
	addLeaf(tree, NULL, child, strlen(child));
	parent = "Grandma & Papa";
	child = "Uncle Randy & Aunt Mary";
	addLeaf(tree, findLeaf(tree, parent), child, strlen(child));
	child = "Uncle Dan & Aunt Christie";
	addLeaf(tree, findLeaf(tree, parent), child, strlen(child));
	child = "Mom & Dad";
	addLeaf(tree, findLeaf(tree, parent), child, strlen(child));
	parent = "Uncle Randy & Aunt Mary";
	child = "Jordan & Lina";
	addLeaf(tree, findLeaf(tree, parent), child, strlen(child));
	child = "Bethany & Devon";
	addLeaf(tree, findLeaf(tree, parent), child, strlen(child));
	parent = "Bethany & Devon";
	child = "Ellery";
	addLeaf(tree, findLeaf(tree, parent), child, strlen(child));
	child = "Lyla";
	addLeaf(tree, findLeaf(tree, parent), child, strlen(child));
	parent = "Uncle Dan & Aunt Christie";
	child = "Rachell";
	addLeaf(tree, findLeaf(tree, parent), child, strlen(child));
	child = "Tyler";
	addLeaf(tree, findLeaf(tree, parent), child, strlen(child));
	parent = "Mom & Dad";
	child = "Chelsea & Cody";
	addLeaf(tree, findLeaf(tree, parent), child, strlen(child));
	child = "Sean & Will";
	addLeaf(tree, findLeaf(tree, parent), child, strlen(child));
	child = "Zac";
	addLeaf(tree, findLeaf(tree, parent), child, strlen(child));
	
	printf("\nPrinting Tree...\n\n");
	ptTree(tree);

	printf("Destroy the tree...\n");
	rmTree(&tree);
	printf("DONE\n\n");
	return 0;
}

/**
 * METHODS OF TRAVERSING A TREE.
 * 
 * 1.	PREORDER	- ROOT, LEFT, RIGHT
 * 2.	INORDER		- LEFT, ROOT, RIGHT
 * 3.	POSTORDER	- LEFT, RIGHT, ROOT
 */

/**
 * METHODS OF BALANCING BINARY SEARCH TREES.
 * 
 * 1.	YOU CAN TAKE A NON-BALANCED BST, STORE ITS CONTENTS IN AN ARRAY IN
 * 		INORDER TRANSVERSAL. THIS WILL GIVE YOU AN ARRAY THAT CONTAINS THE
 * 		CONTENTS OF THE BST IN ORDER FROM LEAST TO GREATEST. THEN TAKE THAT 
 * 		ARRAY AND USING RECURSION CREATE ANOTHER BST THAT IS BALANCED.
 * 		THIS METHOD WILL BE O(n) IN TIME.
 * 
 * 2.	USE OF AVL TREE. A HEIGHT-BALANCING TREE, YOU CALCULATE A 
 * 		BALANCE-FACTOR. BALANCE-FACTOR(BF) = HEIGHT OF LEFT SUBTREE(HL) - 
 * 		HEIGHT OF RIGHT SUBTREE(HR). IF TREE IS BALANCED THE BF SHOULD BE
 * 		{-1,0,1}. IF THE TREE BECOMES UNBALANCED, YOU CAN DETERMINE WHICH SIDE
 * 		IS THE HEAVY SIDE BASED ON THE BF AND THUS DETERMINE THE TYPE OF 
 * 		ROTATION NEEDED TO BALANCE THE TREE. DEPENDING ON WHERE THE NEW NODE WAS 
 * 		INSERTED AT, A DOUBLE ROTATION MIGHT HAVE TO BE PERFORMED TO BALLANCE 
 * 		THE TREE. THE TIME TO SEARCH A AVL TREE IS O(log(n)) OPPOSED TO THE O(n) 
 * 		OF STANDARD BST TREES. THIS IS BECAUSE THE HIGHEST A AVL TREE CAN BE IS 
 * 		1.44log(n) OPPOSED TO n.
 */