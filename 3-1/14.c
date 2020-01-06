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
void mvNode_before(node_t*, node_t*);
node_t* find_sm(node_t*);
int find_low_pivot(int*, int);
int find_high_pivot(int*, int);

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
	node_t *head = arr_to_list(arr, size);	
	ptList(head);
	
	//Establish comparison node and set to id 0
	node_t *cmp = head;
	node_t *tmp;
	int head_set;
	if(cmp->id != 0)
		cmp = find_node_by_id(head, 0);
	
	//Loop through until all nodes are sorted by value
	int *nodes_sorted = (int *)malloc(size);
	int pivot_id;
	int count = 0;
	while(count < size){
		//Get pivot id that has not been placed
		do{
			pivot_id = rand()%size;
		}while(nodes_sorted[pivot_id]);
		
		//Add pivot to nodes_sorted
		nodes_sorted[pivot_id] = 1;
		count++;
		printf("Sorted: %d\n\n", pivot_id);
		
		fprintf(stderr, "PIVOT ID: %d\n", pivot_id);
		
		//Get the Pivot node by id
		node_t *pivot = find_node_by_id(head, pivot_id);
		fprintf(stderr, "PIVOT VALUE: %d\n\n", pivot->data); 
		
		//send all large values right of pivot
		for(int i=find_low_pivot(nodes_sorted, pivot_id); i<pivot_id; i++){
			//compare cmp node and pivot node
			if(cmp->data > pivot->data){
				tmp = cmp->next;
				mvNode_after(cmp, pivot);
				if(cmp->id == head->id)
					head = tmp;
			}
			else
				tmp = cmp->next;
			cmp = tmp;
		}
		//send all small values left of pivot
		//for loop set in if to check for head position and minimize checks
		if(head->id == pivot_id){
			head_set = 0;
			for(int i=pivot_id; i<find_high_pivot(nodes_sorted, pivot_id); i++){
				if(cmp->data < pivot->data){
					tmp = cmp->next;
					mvNode_before(cmp, pivot);
					if(!head_set){
						head = cmp;
						head_set = 1;
					}
				}
				else
					tmp = cmp->next;
				cmp = tmp;
			}
		}
		else{
			for(int i=pivot_id; i<find_high_pivot(nodes_sorted, pivot_id); i++){
				if(cmp->data < pivot->data){
					tmp = cmp->next;
					mvNode_before(cmp, pivot);
				}
				else
					tmp = cmp->next;
				cmp = tmp;
			}
		}
		ptList(head);
		//Look at adjacent nodes to determine if sorted
		tmp = find_node_by_id(head, pivot_id);
		if(nodes_sorted[tmp->next->next->id] || (tmp->next->next == NULL && tmp->next != NULL)){
			nodes_sorted[tmp->next->id] = 1;
			count++;
			printf("\n\n*Sorted: %d\n\n", tmp->next->id);
		}
		if(nodes_sorted[tmp->prev->prev->id] || (tmp->prev->prev == NULL && tmp->prev != NULL)){
			nodes_sorted[tmp->prev->id] = 1;
			count++;
			printf("\n\n*Sorted: %d\n\n", tmp->prev->id);
		}
	}
	ptList(head);
	printf("\n\n");
	return;
}

int find_high_pivot(int *sorted, int pivot){
	int i;
	for(i=pivot+1; i<(sizeof(sorted)/sizeof(sorted[0])); i++){
		if(sorted[i])
			return i;
	}
	return i-1;
}

int find_low_pivot(int *sorted, int pivot){
	int i;
	for(i=pivot-1; i>=0; i--){
		if(sorted[i])
			return i+1;	
	}
	return i;	
}

node_t* find_sm(node_t *head){
	node_t *sm = head;
	while(head->next != NULL){
		if(head->next->data < head->data && head->next->data < sm->data){
			sm = head->next;
		}
		head = head->next;
	}
	return sm;	
}

void mvNode_after(node_t *mv, node_t *anchor){
	mv->next->prev = mv->prev;
	if(mv->prev != NULL)
		mv->prev->next = mv->next;
	mv->next = anchor->next;
	if(anchor->next != NULL)
		anchor->next->prev = mv;
	anchor->next = mv;
	mv->prev = anchor;
	return;
}

void mvNode_before(node_t *mv, node_t *anchor){
	mv->prev->next = mv->next;
	if(mv->next != NULL)
		mv->next->prev = mv->prev;
	mv->next = anchor;
	mv->prev = anchor->prev;
	if(anchor->prev != NULL)
		anchor->prev->next = mv;
	anchor->prev = mv;
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