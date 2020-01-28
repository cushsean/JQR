#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct node{
	int data;
	struct node *next;
	struct node *prev;
}node_t;

node_t* mkNode(int);
node_t* mkList(int);
void ptList(node_t*);
void ptList_rev(node_t*, int);
node_t* find_Node(node_t*, int);
node_t* sort_Node(node_t*);
typedef node_t* (*func_t)(node_t*);
void rmNode(node_t*, int, int);
node_t* insert_at_head(node_t*, node_t*);
void insert_node(node_t*, int, int);
void rm_all_nodes(node_t*);

int main(){
	func_t sort_ptr = &sort_Node;
	node_t *list =	mkList(5);
	insert_node(list, 2, 10);
	ptList(list);
	list = (*sort_ptr)(list);
	ptList(list);
	rmNode(list, 10, 0);
	ptList(list);
	
	rm_all_nodes(list);
	
	return 0;	
}

//3.3.3.a Create d_list with n number of items
node_t* mkNode(int num){
	node_t *fn_node = (node_t*)malloc(sizeof(node_t));
	fn_node->data = num;
	fn_node->next = NULL;
	fn_node->prev = NULL;
	return fn_node;
}

node_t* mkList(int num){
	node_t *head = NULL;
	//node_t *tail = NULL;
	//printf("%s\t%d\t%s\n", head->prev, head->data, head->next);
	for (int i = 0; i < num; i++){
		head = insert_at_head(head, mkNode(i));
		//printf("node %d\t%d\n", i, head->data);
	}
	ptList(head);
	return head;
}

//3.3.3.b Navigate through a d_list
void ptList(node_t *head){
	node_t *tmp = head;
	node_t *tail;
	int i = 0;
	for (i; tmp != NULL; i++){
		printf("node %d\t%d\n", i, tmp->data);
		tail = tmp;
		tmp = tmp->next;
	}
	printf("\n");
	ptList_rev(tail, --i);
	return;	
}

void ptList_rev(node_t *tail, int i){
	node_t *tmp = tail;
	for (i; tmp != NULL; i--){
		printf("node %d\t%d\n", i, tmp->data);
		tmp = tmp->prev;
	}
	printf("\n");
	return;
}

//3.3.3.c Find the first occurance in d_list
node_t* find_node(node_t *head, int value){
	node_t *tmp = head;
	if (tmp == NULL)
		return NULL;
	else if (tmp->data == value)
		return tmp;
	else return find_node(tmp->next, value);
}

//3.3.3.d Sort a d_list alphanumerically with fn_ptr
node_t* sort_Node(node_t *head){
	node_t *curr = head;
	node_t *last = NULL;
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

//3.3.3.e Removing selected items from d_list
void rmNode(node_t *list, int value, int all){
	//Removes node with data equal to value
	//Non-zero all will remove all nodes with value
	node_t *rm_node = find_node(list, value);
	if(rm_node != NULL){
		do{
			if(rm_node->prev == NULL)
				list = rm_node->next;
			else
				rm_node->prev->next = rm_node->next;
			if(rm_node->next != NULL)
				rm_node->next->prev = rm_node->prev;
			free(rm_node);
		}while(rm_node != NULL && all);
	}
	else
		printf("ERROR: Value not found, no node removed.\n");
	return;
}

//3.3.3.f Insert node at secified location
node_t* insert_at_head(node_t *head, node_t *insert){
	insert->next = head;
	if (head != NULL)
		head->prev = insert;
	return insert;
}

void insert_node(node_t *list, int after, int value){
	node_t *insert_after = find_node(list, after);
	node_t *new_node = mkNode(value);
	new_node->next = insert_after->next;
	insert_after->next->prev = new_node;
	insert_after->next = new_node;
	new_node->prev = insert_after;
	return;
}

//3.3.3.g-h Destroy d_list
void rm_all_nodes(node_t *head){
	node_t *tmp;
	tmp = head->next;
	free(head);
	if (tmp != NULL)
		return rm_all_nodes(tmp);
	printf("ALL NODES REMOVED. LIST IS DESTROYED!\n");
	return;
}