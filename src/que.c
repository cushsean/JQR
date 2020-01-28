#include <stdlib.h>
#include <stdio.h>

#include "que.h"
#include "list.h"


//3.3.5.a
node_t* mkQue(int num){
	if(num < 1){
		fprintf(stderr, "ERROR: Que length less than 1. NO QUE FORMED.\n");
		return NULL;
	}
	node_t* front = mkNode(0);
	node_t* end = front;
	front->next = end;
	for(int i=1; i<num; i++){
		node_t* new_node = mkNode(i);
		new_node->prev = end;
		end->next = new_node;
		end = new_node;
	}
	front->prev = end;
	end->next = front;
	return front;
}

node_t* que_find_by_elem(node_t* first, int num){
	if(que_get_size(first) < num || num < 1){
		fprintf(stderr, "ERROR: Desired elem is invalid.\n");
		return NULL;
	}
	for(int i=0; i<num; i++){
		first = dQue(first);
	}
	return first;
}

node_t* que_find_by_val(node_t* first, int num){
	if(first != NULL){
		do{
			if(first->data == num)
				return first;
			first = dQue(first);
		}while(first->next != first && first->next != NULL);
	}
	printf("Value not found.\n");
	return NULL;
}

node_t* rm_que_item(node_t* first, int num){
	while(first->data != num){
		first = dQue(first);
	}
	first = dQue(first);
	return first;
}

void rmQue(node_t* first){
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
	free(head);
	end->next = tmp;
	tmp->prev = end;
		
	return tmp;
}