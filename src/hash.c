#include "hash.h"

unsigned long hash(char *input){
	const int MULT = 97;
	unsigned long h = 5;
	unsigned char* str = (unsigned char*)input;
	for(int flag=0; flag < 2; flag++){
		while(*str != '\0'){\
			h = h * MULT + *str;
			str++;
		}
		
		if(flag == 0){
			sprintf(str, "%lu", h);
		}
	}
	h = h%LIMITER; //limits output LIMITER defined in hash.h
	return h;
}

node_t** hash_table(){
	node_t** table = (node_t**)malloc(LIMITER * sizeof(node_t*));
	for(int i=0; i<LIMITER; i++)
		table[i] = (node_t*)malloc(sizeof(node_t));
	return table;	
}

node_t** hash_insert(node_t** table, void* str, int* collisions){
	unsigned long index = hash((char*)str);
	if(table[index]->data == NULL)
		table[index]->data = str;
	else{
		(*collisions)++;
		node_t* curr = table[index];
		while(curr->next != NULL)
			curr = curr->next;
		curr->next = mkNode(str);
		curr->next->prev = curr;
	}
	return table;
}

void hash_free(node_t** table){
	for(int i=0; i<LIMITER; i++)
		free(table[i]);
	free(table);
	return;
}

node_t* hash_find_byValue(node_t** table, void* str, int loud){
	printf("String to hash: %s\n", (char*)str);
	unsigned long index = hash((char*)str);
	printf("Hash: %lu\n", index);
	int level = 0;
	node_t* curr = table[index];
	while(!cmp_str(curr->data, str)){
		if(curr->next != NULL)
			curr = curr->next;
		else{
			curr = NULL;
			break;
		}
	}
	if(loud){
		printf("Find by Value...\n");
		if(curr == NULL)
			printf("Key not found in table\n");
		else{
			printf("Key: %s\n", (char*)str);
			printf("Hash: %08lu\n", index);
			printf("Level: %d\n", level);
		}
	}
	return NULL;
}

node_t* hash_find_byNumber(node_t** table, unsigned long num){
	node_t* curr = table[0];
	node_t* hold = NULL;
	for(num; num>0; num--){
		while(curr->data == NULL){
			curr = curr++;
		}
		if(curr->next != NULL){
			if(hold == NULL)
				hold = curr;
			curr = curr->next;
		}
		else if(curr->next == NULL && hold != NULL){
			curr = hold++;
			hold = NULL;
		}
		else
			curr = curr++;
	}
	return NULL;
}