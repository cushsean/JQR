#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct node{
	int id;
	int data;
	struct node *next;
	struct node *prev;
}node_t;

node_t* find_node(node_t*, int);
node_t* find_node_by_id(node_t*, int);
void rm_all_nodes(node_t*);
void insert_node(node_t*, int, int);
node_t* insert_at_head(node_t*, node_t*);
node_t* insert_at_tail(node_t*, node_t*);
node_t* mknode(int);
node_t* arr_to_list(int*, int);
void ptList(node_t*);
void mvNode_after(node_t*, node_t*);

void sort_bubble(int*);
void sort_merge(int*, int);
void sort_quick(int*, int);

void sort_bubble(int *arr){
	printf("THE BUBBLE\n");
	for(int i=0; i<20; i++){
		for(int n=0; n<19; n++){
			if(arr[i] < arr[n]){
				int temp = arr[n];
				arr[n] = arr[i];
				arr[i] = temp;
			}
		}
	}
	printf("\n\n");
	return;
}


void sort_merge(int *arr, int size){
	printf("THE MERGE\n");
	node_t *list = arr_to_list(arr, size);
	ptList(list);
	
	printf("\n\n");
	return;
}

void sort_quick(int *arr, int size){
	printf("THE QUICK\n");
	node_t *list = arr_to_list(arr, size);
	ptList(list);
	
	//Generate first pivot
	int pivot_id = rand()%size;
	printf("PIVOT ID: %d\n", pivot_id);
	
	//Get the Pivot node by id
	node_t *pivot = find_node_by_id(list, pivot_id);
	printf("PIVOT VALUE: %d\n", pivot->data); 
	
	//Establish comparison node and set to id 0
	node_t *cmp = list;
	node_t *tmp;
	if(cmp->id != 0)
		cmp = find_node_by_id(list, 0);
	for(int i=0; i<pivot_id; i++){
		//compare cmp node and pivot node
		if(cmp->data > pivot->data){
			tmp = cmp->next;
			mvNode_after(cmp, pivot);
		}
		else
			tmp = cmp->next;
		cmp = tmp;
	}
	
	//#####################################
	// Moving high numbers to right of 
	// pivot works. Need to do the same
	// for small numbers to the left of
	// pivot. Will need to create fn
	// void mvNode_before(node_t*, node_t*)
	// be mindful of edge cases and check
	// for NULL values.
	//#####################################
	
	ptList(list);
	printf("\n\n");
	return;
}

void mvNode_after(node_t *mv, node_t *anchor){
	if(mv->prev == NULL)
		mv->next->prev = NULL;
	else{
		mv->prev->next = mv->next;
		mv->next->prev = mv->prev;
	}
	mv->next = anchor->next;
	if(anchor->next != NULL)
		anchor->next->prev = mv;
	anchor->next = mv;
	mv->prev = anchor;
	return;
}

node_t* find_node(node_t *head, int value){
	node_t *tmp = head;
	if (tmp == NULL)
		return NULL;
	else if (tmp->data == value)
		return tmp;
	else return find_node(tmp->next, value);
}

node_t* find_node_by_id(node_t *head, int value){
	node_t *tmp = head;
	if (tmp == NULL)
		return NULL;
	else if (tmp->id == value)
		return tmp;
	else return find_node_by_id(tmp->next, value);
}

void rm_all_nodes(node_t *head){
	node_t *tmp;
	tmp = head->next;
	free(head);
	if (tmp != NULL)
		return rm_all_nodes(tmp);
	printf("ALL NODES REMOVED. LIST IS DESTROYED!\n");
	return;
}

void insert_node(node_t *list, int after, int value){
	node_t *insert_after = find_node(list, after);
	node_t *new_node = mknode(value);
	new_node->next = insert_after->next;
	insert_after->next->prev = new_node;
	insert_after->next = new_node;
	new_node->prev = insert_after;
	return;
}

node_t* insert_at_head(node_t *head, node_t *insert){
	insert->next = head;
	if (head != NULL)
		head->prev = insert;
	return insert;
}

node_t* insert_at_tail(node_t *tail, node_t *insert){
	insert->prev = tail;
	if (tail != NULL)
		tail->next = insert;
	return insert;
}

node_t* mknode(int num){
	node_t *fn_node = (node_t*)malloc(sizeof(node_t));
	fn_node->id = num;
	fn_node->next = NULL;
	fn_node->prev = NULL;
	return fn_node;
}

node_t* arr_to_list(int *arr, int size){
	//makes a list of size nodes
	//nodes id is sequental
	//node data set by 'arr'
	if(size < 1)
		return NULL;
	node_t *head = NULL;
	node_t *tail = NULL;
	node_t *tmp = insert_at_head(head, mknode(0));
	tmp->data = arr[0];
	head = tail = tmp;
	for (int i = 1; i < size; i++){
		tail = insert_at_tail(tail, mknode(i));
		tail->data = arr[i];
	}
	return head;
}

void ptList(node_t *head){
	node_t *tmp = head;
	node_t *tail;
	int i = 0;
	for (i; tmp != NULL; i++){
		printf("node %d\t%d\n", tmp->id, tmp->data);
		tail = tmp;
		tmp = tmp->next;
	}
	printf("\n");
	return;	
}

int main(){

	int arr[20];
	int list[20];

	srand(time(NULL));

	for(int i=0; i<20; i++){
		arr[i] = rand()%100;
		list[i] = arr[i];
	}
	
	int size = (int)(sizeof(arr)/sizeof(arr[0]));
	
	//sort_bubble(arr);
	//sort_merge(arr, size);
	sort_quick(arr, size);
	

	for(int i=0; i<20; i++){
		printf("%d\t%d\n",list[i],arr[i]);
	}

	return 0;
} 