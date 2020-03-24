#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "list.h"
#include "que.h"
#include "util.h"

#define QUE_SIZE (20)

node_t* fillQue(node_t* front){
	srand(time(NULL));
	node_t* curr = front;
	for(int i = 0; i < QUE_SIZE; i++){
		int *num = malloc(sizeof(int));
		*num = rand()%10;
		curr->data = num;
		curr = curr->next;
	}
	return front;
}


int main(){
	node_t* front = mkQue(QUE_SIZE);
	front = fillQue(front);
	ptList(front, print_int);
	printf("size: %d\n", que_get_size(front));
	int num = 4;
	front = que_find_by_elem(front, num);
	printf("The %dth element is: %d\n", num, *((int*)front->data));
	ptList(front, print_int);
	printf("size: %d\n", que_get_size(front));
	num = 6;
	int *ptr = &num;
	int n = que_get_size(front);
	node_t *tmp = front;
	front = que_find_by_val(front, ptr, cmp_int);
	int m = n - que_get_size(front) + 1;
	printf("The element with value %d is ", num);
	if(m > n){
		printf("not found in the que.\n");
		printf("Que is empty.\n");
		return 0;
	}
	printf("%d in line\n", m);
	ptList(front, print_int);
	printf("size: %d\n", que_get_size(front));
	num = 7;
	ptr = &num;
	printf("Removing node with value %d...\n", num);
	front = rm_que_item(front, ptr, cmp_int);
	if(front == NULL){
		printf("Que is empty.\n");
		return 0;
	}
	ptList(front, print_int);
	printf("size: %d\n", que_get_size(front));
	printf("Remove entire Que.\n");
	front = rmQue(front);
	printf("size: %d\n", que_get_size(front));

	return 0;	
}
