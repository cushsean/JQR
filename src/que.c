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

node_t* que_find_by_val(node_t *first, void *value){
	if(first != NULL){
		do{
			if(first->data == value)
				return first;
			first = dQue(first);
		}while(first->next != first && first->next != NULL);
	}
	printf("Value not found.\n");
	return NULL;
}

node_t* rm_que_item(node_t *first, void *value){
	while(first->data != value){
		first = dQue(first);
	}
	first = dQue(first);
	return first;
}

void rmQue(node_t *first){
	while(first->next != first && first->next != NULL){
		first = rm_que_item(first, first->data);
	}
	printf("Que has been destroyed\n");
	return;
}

int que_get_size(node_t* head){
	node_t* curr = head;
	int size = 0;
	do{
		size++;
		if(curr!=NULL)
			curr = curr->next;
	}while(curr != NULL && curr != head);
	
	return size;
}

node_t* dQue(node_t* head){
	node_t* tmp = head->next;
	node_t* end = head->prev;
	free(head->data);
	head->data = NULL;
	free(head);
	head = NULL;
	end->next = tmp;
	tmp->prev = end;
		
	return tmp;
}