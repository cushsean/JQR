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

#include "hash.h"

hash_table* newHashTable(unsigned long (*hash)(char*, size_t), 
							int (*cmp_key)(void*, void*),
							void (*print_set)(hash_set)){
	hash_table *table = malloc(sizeof(hash_table));
	table->size = 16;
	table->set = malloc(sizeof(hash_set) * table->size);
	table->nElem = 0;
	table->hash = hash;
	table->cmp_key = cmp_key;
	table->print_set = print_set;
	for(int i=0; i<table->size; i++){
		table->set[i].key = NULL;
		table->set[i].data = NULL;
		table->set[i].next = NULL;
	}
	return table;
}


void insertHashSet(hash_table *table, void *data, size_t size){
	if(table->nElem >= table->size*.75)
		growTable(table);
	unsigned long *key = malloc(sizeof(unsigned long));
	*key = table->hash(data, size);
	// printf("key: %lu\n", *key);
	size_t index = *key % table->size;
	// hash_set *tmp = NULL;
	if(table->set[index].key != NULL){
		hash_set *tmp = malloc(sizeof(hash_set));
		tmp->key = table->set[index].key;
		tmp->data = table->set[index].data;
		tmp->next = table->set[index].next;
		table->set[index].next = tmp;
		// printf("table:\n");
		// table->print_set(table->set[index]);
		// printf("tmp:\n");
		// table->print_set(*tmp);
	}
	table->set[index].key = key;
	table->set[index].data = data;
	table->nElem++;
	// printf("New Set at index %ld:\n", index);
	// table->print_set(table->set[index]);
	// if(tmp != NULL){
	// 	table->set[index].next = tmp;
		// printf("Next Set at index %ld:\n", index);
		// table->print_set(*(table->set[index].next));
	// }
	return;
}


void growTable(hash_table *table){
	printf("The table needs to grow.\n");
}

void freeTable(hash_table **table){
	for(int i=0; i<(*table)->size; i++)
		if((*table)->set[i].key != NULL)
			free((*table)->set[i].key);
	free((*table)->set);
	(*table)->set = NULL;
	free(*table);
	*table = NULL;
}

//Old Functions Below
// unsigned long hash(void *input, size_t size){
// 	const int MULT = 97;
// 	unsigned long key = 5;
// 	unsigned char* str = malloc(size);
// 	// strcpy(str, (unsigned char*)input);
// 	str = (unsigned char*)input;
// 	for(int flag=0; flag < 2; flag++){
// 		while(*str != '\0'){\
// 			key = key * MULT + *str;
// 			str++;
// 		}
		
// 		if(flag == 0){
// 			sprintf(str, "%lu", key);
// 		}
// 	}
// 	// h = h%LIMITER; //limits output LIMITER defined in hash.h
// 	// free(str);
// 	return key;
// }

// char** hash_table(){ 
// 	char** table = (char**)malloc(LIMITER*sizeof(char*));
// 	for(int i=0; i<LIMITER; i++)
// 		table[i] = (char*)malloc(WORD_SIZE);
// 	return table;
// }

// char** hash_insert(char** table, void* input, int* collisions){
// 	char* str = malloc(128);
// 	strcpy(str, (char*)input);
// 	int len = strlen(str);
// 	if(len > 0 && str[len-1] == '\n')
// 		str[len-1] = '\0';
	
// 	unsigned long index = hash(str);
// 	if(strcmp(table[index], "") == MATCH)
// 		strcpy(table[index], str);
// 	else{
// 		(*collisions)++;
// 		while(strcmp(table[index], "") != MATCH)
// 			index++;
// 		strcpy(table[index], str);
// 	}
	
// 	free(str);
// 	return table;
// }

// void hash_free(char** table){
// 	for(int i=0; i<LIMITER; i++)
// 		free(table[i]);
// 	free(table);
// 	return;
// }

// long hash_find_byValue(char** table, void* input){
// 	char* str = malloc(128);
// 	strcpy(str, (char*)input);
// 	int len = strlen(str);
// 	if(len > 0 && str[len-1] == '\n')
// 		str[len-1] = '\0';
	
// 	unsigned long index = hash(str);
// 	while(table[index] == NULL)
// 		index++;
// 	if(strcmp(table[index], str) == MATCH){
// 		free(str);
// 		return index;
// 	}
// 	else{
// 		while(strcmp(table[index], str) != MATCH){
// 			if(++index == LIMITER){
// 				printf("%s not found in hash table.\n", str);
// 				free(str);
// 				return -1;
// 			}
// 		}
// 		free(str);
// 		return index;
// 	}
// }

// long hash_find_byNumber(char** table, unsigned long input){
// 	for(int i=0; i<LIMITER && input > 0; i++){
// 		if(strcmp(table[i], "") != MATCH)
// 			if(--input == 0)
// 				return i;
// 	}
// 	return -1;
// }

// char** hash_rmItem(char** table, void* input){
// 	long item_index = hash_find_byValue(table, input);
// 	if(item_index != -1){
// 		table[item_index] = NULL;
// 		printf("%s has been removed from hash table.\n", (char*)input);
// 	}
// 	return table;
// }