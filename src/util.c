#include "util.h"

int cmp_int(void *var1, void *var2){
	if(var1 == NULL || var2 == NULL){
		fprintf(stderr, "ERROR: Compare Failed\n");
		return 0;
	}
	int num1 = *((int*)var1);
	int num2 = *((int*)var2);
	// printf("cmp %d with %d\n", num1, num2);
	if(num1 == num2)
		return 0;
	else if(num1 > num2)
		return 1;
	else if(num1 < num2)
		return -1;
}

int cmp_ulong(void *var1, void *var2){
	if(var1 == NULL || var2 == NULL){
		fprintf(stderr, "ERROR: Compare Failed\n");
		return 0;
	}
	unsigned long num1 = *((unsigned long*)var1);
	unsigned long num2 = *((unsigned long*)var2);
	if(num1 == num2)
		return 0;
	else if(num1 > num2)
		return 1;
	else if(num1 < num2)
		return -1;
}

int cmp_str(void *var1, void *var2){
	// if(var1 == NULL || var2 == NULL){
	// 	fprintf(stderr, "ERROR: Compare Failed\n");
	// 	return 0;
	// }
	if(var1 == NULL){
		if(var2 == NULL)
			return 0;
		return -1;
	}
	else if(var2 == NULL)
		return 1;
	else
		return strcmp((char*)var1, (char*)var2);
}

void swap(void *a, void *b, size_t size){
    void *temp = malloc(size);
    memcpy(temp, a   , size);
    memcpy(a   , b   , size);
    memcpy(b   , temp, size);
    free(temp);
}

void print_bin(char* buf, size_t len){
	for(size_t i=0; i < len; i++){
		printf("%x", buf[i]);
	}
	printf("\n");
	return;
}
void print_int(void *num){
	printf("%d", *((int*)num));
	return;
}

// node_t* swap_node(node_t *head, node_t *curr, node_t *NX){

// 	if(curr->prev != NULL)
// 		curr->prev->next = NX;
// 	NX->prev = curr->prev;
// 	if(NX->next != NULL && NX->type != SINGLY)
// 		NX->next->prev = curr;
// 	curr->next = NX->next;
// 	NX->next = curr;
// 	if(curr->type != SINGLY)
// 		curr->prev = NX;
// 	if(head == curr)
// 		head = NX;
		
// 	return head;
// }


// node_t* swap_node_singly(node_t *head, node_t *curr, node_t *NX, node_t *PR){

// 	if(PR != NULL)
// 		PR->next = NX;
// 	curr->next = NX->next;
// 	NX->next = curr;
// 	if(head == curr)
// 		head = NX;
		
// 	return head;
// }

unsigned long hash(void *input, size_t size){
	
	unsigned long key = 0;
	int c;

	char *str = (char*)input;

	while(c = *str++)
		key = c + (key << 6) + (key << 16) - key;

	// Double hash
	char buf[21];
	sprintf(buf, "%020lu", key);
	buf[20] = '\0';
	for(int i=0; i<20; i++)
		key = buf[i] + (key << 6) + (key << 16) - key;

	return key;
}


void print_str(void *data){
	printf("\"%s\"", (char*)data);
	return;
}