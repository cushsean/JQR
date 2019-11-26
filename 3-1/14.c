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
void rm_all_nodes(node_t*);
void insert_node(node_t*, int, int);
node_t* insert_at_head(node_t*, node_t*);
node_t* mknode(int);
node_t* arr_to_list(int*);
void ptList(node_t*);

void sort_bubble(int*);
void sort_merge(int*);

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


void sort_merge(int *arr){
	printf("THE MERGE\n");
	node_t *list = arr_to_list(arr);
	ptList(list);
	
	printf("\n\n");
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

node_t* mknode(int num){
	node_t *fn_node = (node_t*)malloc(sizeof(node_t));
	fn_node->id = num;
	fn_node->next = NULL;
	fn_node->prev = NULL;
	return fn_node;
}

node_t* arr_to_list(int *arr){
	//makes a list of n nodes
	//nodes id is sequental
	//node data set by arr
	//NOTE: DOES INVERT THE LIST
	node_t *head = NULL;
	for (int i = 0; i < sizeof(arr); i++){
		head = insert_at_head(head, mknode(i));
		head->data = arr[i];
	}
	return head;
}

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
	
	sort_bubble(arr);
	sort_merge(arr);
	

	for(int i=0; i<20; i++){
		printf("%d\t%d\n",list[i],arr[i]);
	}

	return 0;
} 