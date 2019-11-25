#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct Node{
	int data;
	struct Node *next;
} node_t;

//INSERT AN ITEM INTO A SPECIFIED LOCATION SATISFIES 3.3.2.f
void insert_node(node_t *insert_after, node_t *new_node){
	new_node->next = insert_after->next;
	insert_after->next = new_node;
	return;	
}

void insert_at_head(node_t **head, node_t* insert){
	insert->next = *head;
	*head = insert;
	return;
}

//RETURN FIRST OCCURRENCE OF AN ITEM SATISFIES 3.3.2.c
//THIS FUNCTION ALSO SATISFIES 3.1.8.i (RECURSION)
node_t* find_node(node_t *head, int value){
	node_t *tmp = head;
	if (tmp == NULL)
		return NULL;
	else if (tmp->data == value)
		return tmp;
	else return find_node(tmp->next, value);
}

node_t* mknode(int num){
	node_t *fn_node;
	fn_node = (node_t*)malloc(sizeof(node_t));
	fn_node->data = num;
	fn_node->next = NULL;
	return fn_node;
}

//LINKED LIST WITH n NODES SATISFIES 3.3.2.a
node_t* mklist(int num){
	node_t *list = NULL;
	for(int i=0; i < num; i++){
		insert_at_head(&list, mknode(i));
	}
	return list;
}

//Navigating through a list SATISFIES 3.3.2.b
void ptlist(node_t *list){
	node_t *tmp;
	int i = 0;
	tmp = list;
	while(tmp != NULL){
		printf("node %d\t%d\n",i++, tmp->data);
		tmp = tmp->next;
	}
	printf("\n");
	
	return;	
}

//REMOVE SELECTED NODE SATISFIES 3.3.2.e
void rmnode(node_t *list, int value){
	//Removes node after the node selected
	node_t *node_selected;
	node_t *node_to_remove;
	node_selected = find_node(list, value);
	node_to_remove = node_selected->next;
	node_selected->next = node_to_remove->next;
	free(node_to_remove);
	return;
}

//REMOVES ALL NODES SATISFIES 3.3.2.g-h
//ALSO SATISFIES 3.1.8.i (RECURSION)
void rm_all_nodes(node_t *head){
	node_t *tmp;
	tmp = head->next;
	free(head);
	if (tmp != NULL)
		return rm_all_nodes(tmp);
	printf("ALL NODES REMOVED. LIST IS DESTROYED!\n");
	return;
}

int main(){
	node_t *list;
	list = mklist(10);
	ptlist(list);
	insert_node(find_node(list,5),mknode(64));
	ptlist(list);
	rmnode(list,5);
	ptlist(list);
	rm_all_nodes(list);
	
	return 0;	
}