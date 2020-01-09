#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "tree.h"

int main(){
	
	tree_b* root = mkTree_bin(4);
	ptTree_bin(root);
	//printf("DEPTH: %d\n", get_depth_bin(root));
	return 0;
}