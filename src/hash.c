#include "hash.h"

/*
*	05FEB2020
*	Need to modify hash_table to be an actual table
*	instead of a hash_set as it currently is.
*	The table should include both the KEY and DATA,
*	both of which should be void*. The table should not
*	start at 99999999 (LIMITER) like it is but rather 
*	start small like 16 and grow at a rate of 2^n,
*	n starting at 4 and increasing when num_elem is
*	equal to 3/4 2^n. When the table_size increase,
*	the index for each hash in the table will need to be
*	increased as well. This will be done in the grow_table
*	function. The elements of the table should be a struct
*	that contains the key and any data. ex)
*		struct bucket{
*			void* key;
*			void* data;
*		}
*	A separte struct should be used to hold the tables
*	meta data. ex)
*		struct hash_table{
*			struct bucket* array;
*			size_t table_size;
*			size_t num_elem;
*			ulong (*hash)(void*);
*			void* (*key_cpy)(void*);
*			int (*key_cmp)(void*, void*)
*		}
*	The following functions should be used to perform
*	operations on the hash_table:
*	1)	struct hash_table* new_hash_table(
*			ulong (*hash)(void*),
*			void* (*key_cpy)(void*),
*			int (*key_cmp)(void*,void*)
*		)
*	2)	int insert_hash_table(
*			struct hash_table*,
*			void* key,
*			void* value
*		)
*	3)	void* get_hash_table(
*			struct hash_table*,
*			void* key
*		)
*	4)	int rm_hash_table(
*			struct hash_table*,
*			void* key
*		)
*/

meta_h* hash_new_table(void){
	meta_h* table = (meta_h*)malloc(sizeof(meta_h));
	table->size = 16;
	table->num_elem = 0;
	table->set = (node_h**)malloc(sizeof(node_h*)*table->size);
	for(int i=0;i<table->size;i++){
		table->set[i]->key = "";
		table->set[i]->data = NULL;
		table->set[i]->valid_node = 'y';
	}
	return NULL;
}

int hash_insert_node(meta_h* table, char* key){
	unsigned long index = hash(key);
	while(table->set[index]->key != NULL){
		index = (index+1)%table->size;
	}
	table->set[index]->key = key;
	table->set[index]->data = "some_data";
	return 0;
}

void* hash_get_node(meta_h* table, char* key){
	unsigned long index = hash(key);
	
	return NULL;
}

int hash_rm_node(meta_h* table, char* key){
	unsigned long index = hash(key);
	
	return 0;
}

//Old Functions Below
unsigned long hash(char *input){
	const int MULT = 97;
	unsigned long h = 5;
	unsigned char* str = malloc(128);
	strcpy(str, (unsigned char*)input);
	for(int flag=0; flag < 2; flag++){
		while(*str != '\0'){\
			h = h * MULT + *str;
			str++;
		}
		
		if(flag == 0){
			sprintf(str, "%lu", h);
		}
	}
	//h = h%LIMITER; //limits output LIMITER defined in hash.h
	return h;
}

char** hash_table(){
	char** table = (char**)malloc(LIMITER*sizeof(char*));
	for(int i=0; i<LIMITER; i++)
		table[i] = (char*)malloc(WORD_SIZE);
	return table;
}

char** hash_insert(char** table, void* input, int* collisions){
	char* str = malloc(128);
	strcpy(str, (char*)input);
	int len = strlen(str);
	if(len > 0 && str[len-1] == '\n')
		str[len-1] = '\0';
	
	unsigned long index = hash(str);
	if(strcmp(table[index], "") == MATCH)
		strcpy(table[index], str);
	else{
		(*collisions)++;
		while(strcmp(table[index], "") != MATCH)
			index++;
		strcpy(table[index], str);
	}
	
	free(str);
	return table;
}

void hash_free(char** table){
	for(int i=0; i<LIMITER; i++)
		free(table[i]);
	free(table);
	return;
}

long hash_find_byValue(char** table, void* input){
	char* str = malloc(128);
	strcpy(str, (char*)input);
	int len = strlen(str);
	if(len > 0 && str[len-1] == '\n')
		str[len-1] = '\0';
	
	unsigned long index = hash(str);
	while(table[index] == NULL)
		index++;
	if(strcmp(table[index], str) == MATCH){
		free(str);
		return index;
	}
	else{
		while(strcmp(table[index], str) != MATCH){
			if(++index == LIMITER){
				printf("%s not found in hash table.\n", str);
				free(str);
				return -1;
			}
		}
		free(str);
		return index;
	}
}

long hash_find_byNumber(char** table, unsigned long input){
	for(int i=0; i<LIMITER && input > 0; i++){
		if(strcmp(table[i], "") != MATCH)
			if(--input == 0)
				return i;
	}
	return -1;
}

char** hash_rmItem(char** table, void* input){
	long item_index = hash_find_byValue(table, input);
	if(item_index != -1){
		table[item_index] = NULL;
		printf("%s has been removed from hash table.\n", (char*)input);
	}
	return table;
}