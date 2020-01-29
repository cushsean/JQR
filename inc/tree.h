#ifndef TREE_H_CUHSMAN
#define TREE_H_CUSHMAN

typedef struct tree{
	void* data;
	struct tree *parent;
	struct tree *child;
}tree_t;

typedef struct bst_tree{
	void* data;
	struct bst_tree *parent;
	struct bst_tree *left;
	struct bst_tree *right;
}tree_b;

tree_t* mkTree(int);
tree_b* mkTree_bst(int);
void mkLeaf(tree_t*, int);
tree_b* mkLeaf_bst(void*);
void insert_leaf_bst(tree_b**, void*);
tree_b* find_leaf_bst(tree_b*, void*);
void rmLeaf_bst(tree_b*, void*);
void ptTree(tree_t*);
void ptTree_bst_int(tree_b*);
void ptTree_bst_util_int(tree_b*, int);
tree_b* find_min_bst(tree_b*);
tree_b* find_max_bst(tree_b*);

#endif /* TREE_H_CUSHMAN */