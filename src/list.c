#include <stdlib.h>
#include <stdio.h>

#include "list.h"

node_t* mkNode(void* num){
	node_t* fn_node = (node_t*)malloc(sizeof(node_t));
	fn_node->data = num;
	fn_node->next = NULL;
	fn_node->prev = NULL;
	return fn_node;
}

node_t* mkList(int num, int circle){
	node_t* head = NULL;
	node_t* tail = NULL;
	for (int i=0; i<num; i++){
		void* ptr = &i;
		head = insert_at_head(head, tail, mkNode(ptr));
		if(tail == NULL && circle)
			tail = head;
	}
	
	ptList(head);
	return head;
}

void ptList(node_t *head){
	node_t* tmp = head;
	printf("Printing List...\n");
	do{
		printf("\t%d\n", *((int*)tmp->data));
		tmp = tmp->next;
	}while(tmp != head && tmp != NULL);
	printf("\n");
	return;	
}

node_t* find_node(node_t *head, void* value){
	node_t* tmp = head;
	if (tmp != NULL)
		do{
			if(tmp->data == value)
				return tmp;
			tmp = tmp->next;
		}while(tmp != head && tmp != NULL);
	printf("ERROR: FOUND NULL; NO ACTION.\n");
	return NULL;	
}

node_t* sort_node(node_t *head){
	node_t *curr = head;
	node_t *last = get_tail(head);
	node_t *NX = NULL;
	int swapped;
		
	//reassign curr to head
	curr = head;
	
	//sort
	do{
		swapped = 0;
		while(curr->next != last){
			NX = curr->next;
			if(curr->data > NX->data){
				if(curr->prev != NULL)
					curr->prev->next = NX;
				NX->prev = curr->prev;
				if(NX->next != NULL)
					NX->next->prev = curr;
				curr->next = NX->next;
				NX->next = curr;
				curr->prev = NX;
				if(head == curr)
					head = curr->prev;
				swapped = 1;
			}
			else
				curr = curr->next;
		}
		last = curr;
		curr = head;
	}while(swapped);
	return head;	
}

node_t* rmNode(node_t *head, void* value, int all){
	//Removes node with data equal to value
	//Non-zero all will remove all nodes with value
	node_t* tail = get_tail(head);
	if(tail == head){
		rm_all_nodes(head);
		return NULL;
	}
	node_t* rm_node = find_node(head, value);
	if(rm_node != NULL){
		do{
			if(rm_node == head){
				head = rm_node->next;
				if(tail->next != NULL){
					tail->next = head;
					head->prev = tail;
				}
				else
					head->prev = NULL;
			}
			else
				rm_node->prev->next = rm_node->next;
			if(rm_node->next != NULL)
				rm_node->next->prev = rm_node->prev;
			if(rm_node == tail)
				break;
			free(rm_node);
		}while(rm_node != tail && all);
	}
	else
		printf("ERROR: Value not found, no node removed.\n");
	return head;
}

node_t* insert_at_head(node_t* head, node_t* tail, node_t* insert){
	insert->next = head;
	insert->prev = tail;
	if(head != NULL)
		head->prev = insert;
	if(tail != NULL)
		tail->next = insert;
	return insert;
}

void insert_node(node_t *list, void* after, void* value){
	node_t* insert_after = find_node(list, after);
	if(insert_after != NULL){
		node_t* new_node = mkNode(value);
		new_node->next = insert_after->next;
		if(insert_after->next != NULL)
			insert_after->next->prev = new_node;
		insert_after->next = new_node;
		new_node->prev = insert_after;
	}
	return;
}

void rm_all_nodes(node_t *head){
	node_t* tail = get_tail(head);
	if(head == NULL)
		printf("ERROR: Passed Pointer is NULL, NO ACTION\n");

	do{
		node_t* tmp = head->next;
		free(head);
		head = tmp;
	}while(head != NULL && head != tail);
	printf("ALL NODES REMOVED. LIST IS DESTROYED!\n");
		
	return;
}

node_t* get_tail(node_t* head){
	node_t* curr = head;
	if(curr->next == NULL)
		goto TERM;
	do{
		curr = curr->next;
	}while(curr->next != NULL && curr->next != head);
	TERM: return curr;
}