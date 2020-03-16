#include "list.h"
#include "util.h"

node_t* mkNode(int l_type){
	node_t* fn_node = (node_t*)malloc(sizeof(node_t));
	fn_node->data = NULL;
	fn_node->type = l_type;
	fn_node->next = NULL;
	fn_node->prev = NULL;
	return fn_node;
}

node_t* mkList(int num, int type){
	node_t* head = NULL;
	node_t* tail = NULL;
	for (int i=0; i<num; i++){
		if(head == NULL){
			head = mkNode(type);
		}
		else
			head = insert_at_head(head, tail, mkNode(type));
		if(tail == NULL && type == CIRCULARLY)
			tail = head;
	}
	
	return head;
}

void ptList(node_t *head, void (*print_ptr)(void*)){
	node_t* curr = head;
	printf("Printing List...\n");
	if(curr != NULL){
		printf("\t");
		do{
			(*print_ptr)(curr->data);
			// printf("%d", *((int*)curr->data));
			printf(" -> ");
			curr = curr->next;
		}while(curr != NULL && curr != head);
	}
	printf("\n");
	return;	
}

node_t* find_node(node_t *head, void *value, int (*cmp_ptr)(void*, void*)){
	node_t* curr = head;
	if (curr != NULL)
		do{
			if((*cmp_ptr)(curr->data, value) == 0)
				return curr;
			curr = curr->next;
		}while(curr != NULL && curr != head);
	return NULL;	
}


void insert_node(node_t *list, void *after, void *value){
	node_t *insert_after = find_node(list, after, cmp_int);
	if(insert_after != NULL){
		node_t* new_node = mkNode(insert_after->type);
		new_node->data = value;
		new_node->next = insert_after->next;
		if(insert_after->next != NULL)
			insert_after->next->prev = new_node;
		insert_after->next = new_node;
		new_node->prev = insert_after;
	}
	else
		printf("ERROR: Failed to locate valid node\n");
	return;
}


node_t* insert_at_head(node_t *head, node_t *tail, node_t *insert){
	insert->next = head;
	if(head->type != SINGLY)
		insert->prev = tail;
	if(head != NULL)
		head->prev = insert;
	if(tail != NULL)
		tail->next = insert;
	return insert;
}


node_t* rmNode(node_t *head, void *value, int all){
	//Removes node with data equal to value
	//Non-zero all will remove all nodes with value
	if(head == NULL){
		printf("ERROR: Passed Pointer is NULL, NO ACTION\n");
		return NULL;
	}
	
	node_t* tail = get_tail(head);
	if(tail == head){
		rm_all_nodes(head);
		return NULL;
	}
	
	do{
		node_t* rm_node = find_node(head, value, cmp_int);
		if(rm_node == NULL)
			break;
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
			if(rm_node->next->prev != NULL)
				rm_node->next->prev = rm_node->prev;
		if(rm_node == tail)
			all = 0;
		free_node(rm_node);
	}while(all);
		
	return head;
}


void rm_all_nodes(node_t *head){
	if(head == NULL){
		printf("ERROR: Passed Pointer is NULL, NO ACTION\n");
		return;
	}

	//node_t* tail = get_tail(head);
	int size = countList(head);
	// do{
	for(; size > 0; size--){
		node_t* tmp = head->next;
		free_node(head);
		head = tmp;
	}
	// }while(head != NULL && head != tail);
	printf("ALL NODES REMOVED. LIST IS DESTROYED!\n");
	return;
}

node_t* get_tail(node_t* head){
	node_t* curr = head;
	if (curr != NULL)
		while(curr->next != NULL && curr->next != head)
			curr = curr->next;
		return curr;
	printf("ERROR: Passed Pointer is NULL, NO ACTION\n");
}

int countList(node_t *head){
	int size = 1;
	node_t* curr = head;
	if (curr != NULL)
	for(; curr->next != NULL && curr->next != head; ++size)
		curr = curr->next;
	return size;
}

void free_node(node_t *head){
	free(head->data);
	head->data = NULL;
	free(head);
	head = NULL;
	return;
}