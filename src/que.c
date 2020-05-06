#include "que.h"
#include "list.h"


struct queue{
	void *data; // The data of the first item in the que.
	llist *list; // A linked list of the ites in the que.
};


que_t* que_create(void (*datacpy)(void *dest, void *src),
					int (*datacmp)(void *data1, void *data2),
					void (*datafree)(void **data)){
	que_t *que = llist_create(SINGLY, FALSE, datacpy, datacmp, datafree);
	return que;
}


void que_push(que_t *que, void *data, size_t size){
	int num = -1;
	return llist_insert(que, TRUE, &num, data, size);
}


void que_find_item(que_t *que, void *item){
	if(item == NULL){
		fprintf(stderr, "item is NULL\n");
		return;
	}
	int num = 0;
	while(llist_cmp(que, llist_find(que, TRUE, &num, 0), item) != 0)
		que_pop(que);

	return;
}


void que_find_nth(que_t *que, size_t n){
	int num = 0;
	for(; n > 0 && llist_find(que, TRUE, &num, 0) != NULL; n--)	
		que_pop(que);
	return;
}	

int que_pop(que_t *que){
	int num = 0;
	return llist_delete(que, TRUE, &num);
}

void que_destroy(que_t **que){
	return llist_destroy(que);
}

void que_print(que_t *que, void (*data_print)(void *data)){
	return llist_print(que, data_print);
}

size_t que_size(que_t *que){
	return llist_size(que);
}