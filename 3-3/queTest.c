#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "list.h"
#include "que.h"
#include "util.h"

#define QUE_SIZE (10)

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
	// int num = 0;
	// void* ptr = &num;
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
	ptr = &num;
	// Need to fix this function
	front = que_find_by_val(front, ptr);
	printf("The element with value %d is: %d\n", num, *((int*)front->data));
	ptList(front, print_int);
	printf("%d\n", que_get_size(front));
	// num = 7;
	// ptr = &num;
	// front = rm_que_item(front, ptr);
	// ptList(front);
	// rmQue(front);
	// //ptList(front);
	
	return 0;	
}
