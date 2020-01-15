#ifndef TREE_H_CUHSMAN
#define TREE_H_CUSHMAN

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "util.h"
#include "list.h"

typedef struct tree{
	int data;
	struct tree *parent;
	struct tree *child;
}tree_t;

typedef struct bin_tree{
	int data;
	struct bin_tree *parent;
	struct bin_tree *left;
	struct bin_tree *right;
}tree_b;

tree_t* mkTree(int);
tree_b* mkTree_bin(int);
void mkLeaf(tree_t*, int);
tree_b* mkLeaf_bin(int);
void insert_leaf_bin(tree_b*, int);
void ptTree(tree_t*);
void ptTree_bin(tree_b*);
void ptTree_bin_util(tree_b*, int);
int get_depth_bin(tree_b*);

tree_t* mkTree(int num){
	tree_t* root;
	mkLeaf(root, num--);
	while(num > 0){
		mkLeaf(root, num--);
	}
	return root;
}

tree_b* mkTree_bin(int num){
	tree_b* root = NULL;
	for(int i = 0; i < num; i++)
		insert_leaf_bin(root, i);
	return root;
}

void mkLeaf(tree_t* root, int value){
	
	return;
}

tree_b* mkLeaf_bin(int value){
	tree_b* leaf = (tree_b*)malloc(sizeof(tree_b*));
	leaf->left = NULL;
	leaf->right = NULL;
	leaf->parent = NULL;
	leaf->data = value;
	return leaf;
}

void insert_leaf_bin(tree_b* root, int value){
	if(root == NULL)
		root = mkLeaf_bin(value);
		return;
	int cmp = cmp_int(value, root->data);
	switch(cmp){
		case 1:
			//value > root->data
			return insert_leaf_bin(root->right, value);
			break;
		case -1:
			//value < root->data
			return insert_leaf_bin(root->left, value);
			break;
		default:
			//value == root->data
			printf("No leaf created.\n");
			break;
	}
	return;
}

//Utils

void ptTree(tree_t* root){
	
	return;
}

void ptTree_bin(tree_b* root){
	printf("\nPrinting Tree...");
	ptTree_bin_util(root, 0);
	return;
}

void ptTree_bin_util(tree_b* root, int num){	
	if(root == NULL)
		return;
	
	num += 1;
	
	ptTree_bin_util(root->right, num);
	
	printf("\n");
	for(int i=0; i<num; i++)
		printf("\t");
	printf("%d\n", root->data);
	
	ptTree_bin_util(root->left, num);
	
	return;
}

int get_depth(){
	int depth = 1;	
	return depth;
}

int get_depth_bin(tree_b* root){
	tree_b* curr = root;
	int depth = 0;
	for(depth; curr->left != NULL; depth++, curr = curr->left);
	return depth;
}


/*
tree_b* find_emptyLeaf(tree_b* root){
	tree_b* parent = root;
	if(root->left != NULL){
		tree_b* child = root->left;
	}
	while(parent
	return parent;
}
*/

#endif /* TREE_H_CUSHMAN */