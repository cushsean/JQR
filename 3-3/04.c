#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "list.h"
#include "sort.h"
#include "util.h"

#define LIST_SIZE (20)

node_t* fill_list(node_t *head, int n){
	srand(time(NULL));
	node_t* curr = head;
	for(int i = 0; i < n; i++){
		int *num = malloc(sizeof(int));
		*num = rand()%10;
		curr->data = num;
		curr = curr->next;
	}
	return head;
}

int main(){
	node_t* list;
	list = mkList(LIST_SIZE, DOUBLY);
	list = fill_list(list, LIST_SIZE);
	ptList(list, print_int);
	int num = 3;
	printf("Find Node...\n");
	node_t* tmp = find_node(list, &num, cmp_int);
	if(tmp == NULL)
		printf("ERROR: Value not found in list.\n");
	else{
		printf("Found: %p contains: ", tmp);
		print_int(tmp->data);
		printf("\n");
	}
	num = 5;
	list = rmNode(list, &num, 0);
	ptList(list, print_int);
	list = rmNode(list, &num, 1);
	ptList(list, print_int);
	int *value = malloc(sizeof(int));
	num = 3;
	*value = 19;
	insert_node(list, &num, value);
	ptList(list, print_int);
	list = sort_bubble_list(list, cmp_int);
	ptList(list, print_int);
	rm_all_nodes(list);
	return 0;	
}