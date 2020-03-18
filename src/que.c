#include "que.h"
#include "list.h"


//3.3.5.a
node_t* mkQue(int num){ //num is number of elements to create.
	if(num < 1){
		fprintf(stderr, "ERROR: Que length less than 1. NO QUE FORMED.\n");
		return NULL;
	}
	return mkList(num, CIRCULARLY);
}

node_t* que_find_by_elem(node_t *first, int num){
	if(que_get_size(first) < num || num < 1){
		fprintf(stderr, "ERROR: Desired elem is invalid.\n");
		return NULL;
	}
	for(--num; num>0; num--){
		first = dQue(first);
	}
	return first;
}

node_t* que_find_by_val(node_t *first, void *value, 
	int (*cmp_ptr)(void*, void*)){
	if(first != NULL){
		while(first != NULL){
			if((*cmp_ptr)(first->data, value) == 0)
				return first;
			first = dQue(first);
		}
	}
	printf("Value not found.\n");
	return NULL;
}

node_t* rm_que_item(node_t *first, void *value, int (*cmp_ptr)(void*,void*)){
	while((*cmp_ptr)(first->data, value) != 0){
		first = dQue(first);
		if(first == NULL)
			return NULL;
	}
	first = dQue(first);
	return first;
}

node_t* rmQue(node_t *first){
	while(first != NULL){
		first = dQue(first);
	}
	printf("Que has been destroyed\n");
	return NULL;
}

int que_get_size(node_t* head){
	int size = 0;
	if(head == NULL)
		return size;
	node_t* curr = head;

	do{
		size++;
		if(curr!=NULL){
			curr = curr->next;
		}
	}while(curr != NULL && curr != head);
	
	return size;
}

node_t* dQue(node_t* head){
	int safe = 0;
	node_t* tmp = head->next;
	node_t* end = head->prev;
	if(head->next != head)
		safe = 1;
	free(head->data);
	head->data = NULL;
	free(head);
	head = NULL;
	if(safe){
		end->next = tmp;
		tmp->prev = end;
		return tmp;
	}

	return NULL;
}