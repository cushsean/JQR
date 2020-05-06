#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "que.h"
#include "util.h"

#define QUE_SIZE (10)

void datacpy(void *dest, void *src){
	*(int*)dest = *(int*)src;
	return;
}

void datafree(void **data){
	free(*data);
	*data = NULL;
	return;
}

void data_print(void *data){
	if(data == NULL)
		printf("null");
	else
		printf("%d", *(int*)data);
	return;
}

static void increase_que(que_t *que){
	for(int i = 0; i < QUE_SIZE; i++){
		int num = rand()%5;
		que_push(que, &num, sizeof(int));
	}

	return;
}	

int main(){

	srand(time(NULL));
	
	que_t *que = que_create(datacpy, cmp_int, datafree);

	increase_que(que);

	que_print(que, data_print);

	int num = 1;
	printf("Find the value %d...\n", num);
	printf("Found the value ");
	data_print(que_find_item(que, &num));
	printf("\n");

	que_print(que, data_print);

	if(que_size(que) < QUE_SIZE/2){
		increase_que(que);
		que_print(que, data_print);
	}

	printf("Find the 3rd item...\n");
	num = 3;
	printf("Found the value ");
	data_print(que_find_nth(que, num));
	printf("\n");
	
	if(que_size(que) < QUE_SIZE/2){
		increase_que(que);
		que_print(que, data_print);
	}

	que_pop(que);

	que_print(que, data_print);

	que_destroy(&que);

	return 0;	
}
