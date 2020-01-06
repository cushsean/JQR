#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct dNode{
	int data;
	struct dNode *next;
	struct dNode *prev;
}dNode_t;

dNode_t* mkdNode(int);
dNode_t* mkdList(int);
void ptdList(dNode_t*);
void ptdList_rev(dNode_t*, int);
dNode_t* find_dNode(dNode_t*, int);
void rmdNode(dNode_t*, int, int);
dNode_t* insert_at_head(dNode_t*, dNode_t*);
void insert_dNode(dNode_t*, int, int);
void rm_all_dNodes(dNode_t*);

int main(){
	dNode_t *list =	mkdList(5);
	insert_dNode(list, 2, 10);
	ptdList(list);
	rmdNode(list, 10, 0);
	ptdList(list);
	rm_all_dNodes(list);
	
	return 0;	
}

//3.3.3.a Create d_list with n number of items
dNode_t* mkdNode(int num){
	dNode_t *fn_node = (dNode_t*)malloc(sizeof(dNode_t));
	fn_node->data = num;
	fn_node->next = NULL;
	fn_node->prev = NULL;
	return fn_node;
}

dNode_t* mkdList(int num){
	dNode_t *head = NULL;
	//dNode_t *tail = NULL;
	//printf("%s\t%d\t%s\n", head->prev, head->data, head->next);
	for (int i = 0; i < num; i++){
		head = insert_at_head(head, mkdNode(i));
		//printf("node %d\t%d\n", i, head->data);
	}
	ptdList(head);
	return head;
}

//3.3.3.b Navigate through a d_list
void ptdList(dNode_t *head){
	dNode_t *tmp = head;
	dNode_t *tail;
	int i = 0;
	for (i; tmp != NULL; i++){
		printf("node %d\t%d\n", i, tmp->data);
		tail = tmp;
		tmp = tmp->next;
	}
	printf("\n");
	ptdList_rev(tail, --i);
	return;	
}

void ptdList_rev(dNode_t *tail, int i){
	dNode_t *tmp = tail;
	for (i; tmp != NULL; i--){
		printf("node %d\t%d\n", i, tmp->data);
		tmp = tmp->prev;
	}
	printf("\n");
	return;
}

//3.3.3.c Find the first occurance in d_list
dNode_t* find_dNode(dNode_t *head, int value){
	dNode_t *tmp = head;
	if (tmp == NULL)
		return NULL;
	else if (tmp->data == value)
		return tmp;
	else return find_dNode(tmp->next, value);
}

//3.3.3.d Sort a d_list alphanumerically

//3.3.3.e Removing selected items from d_list
void rmdNode(dNode_t *list, int value, int all){
	//Removes node with data equal to value
	//Non-zero all will remove all nodes with value
	dNode_t *rm_node = find_dNode(list, value);
	if(rm_node != NULL){
		do{
			rm_node->prev->next = rm_node->next;
			rm_node->next->prev = rm_node->prev;
			free(rm_node);
		}while(rm_node != NULL && all);
	}
	else
		printf("ERROR: Value not found, no node removed.\n");
	return;
}

//3.3.3.f Insert node at secified location
dNode_t* insert_at_head(dNode_t *head, dNode_t *insert){
	insert->next = head;
	if (head != NULL)
		head->prev = insert;
	return insert;
}

void insert_dNode(dNode_t *list, int after, int value){
	dNode_t *insert_after = find_dNode(list, after);
	dNode_t *new_node = mkdNode(value);
	new_node->next = insert_after->next;
	insert_after->next->prev = new_node;
	insert_after->next = new_node;
	new_node->prev = insert_after;
	return;
}

//3.3.3.g-h Destroy d_list
void rm_all_dNodes(dNode_t *head){
	dNode_t *tmp;
	tmp = head->next;
	free(head);
	if (tmp != NULL)
		return rm_all_dNodes(tmp);
	printf("ALL NODES REMOVED. LIST IS DESTROYED!\n");
	return;
}