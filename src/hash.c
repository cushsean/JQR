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
	table->set = calloc(table->size, sizeof(hash_set));
	table->nElem = 0;
	table->hash = hash;
	table->cmp_key = cmp_key;
	table->print_set = print_set;
	return table;
}


static void shiftSet(hash_table *table, size_t index){
	hash_set *tmp = malloc(sizeof(hash_set));
	tmp->key = table->set[index].key;
	tmp->data = table->set[index].data;
	tmp->size = table->set[index].size;
	tmp->next = table->set[index].next;
	table->set[index].next = tmp;

	return;
}


void insertHashSet(hash_table *table, void *user_data, size_t size){
	if(table->nElem >= table->size*.75)
		growTable(table);
	void *data = malloc(size);
	memcpy(data, user_data, size);
	size_t *key = malloc(sizeof(size_t));
	*key = table->hash(data, size);
	size_t index = *key % table->size;
	if(table->set[index].key != NULL)
		shiftSet(table, index);
	table->set[index].key = key;
	table->set[index].data = data;
	table->set[index].size = size;
	table->nElem++;
	return;
}

void growTable(hash_table *table){
	// printf("The table needs to grow.\n");
	table->size *= 2;
	hash_set *old = table->set;
	table->set = calloc(table->size, sizeof(hash_set));
	for(int i=0; i<table->size/2; i++){
		hash_set *tmp = old+i;
		do{
			if(tmp->key != NULL){
				size_t index = *(size_t*)tmp->key % table->size;
				if(table->set[index].key != NULL)
					shiftSet(table, index);
				table->set[index].key = tmp->key;
				table->set[index].data = tmp->data;
				table->set[index].size = tmp->size;
			}
			tmp = tmp->next;
		}while(tmp != NULL);
		tmp = old[i].next;
		while(tmp != NULL){
			hash_set *tmp_next = tmp->next;
			free(tmp);
			tmp = tmp_next;
		}

	}
	free(old);
	old = NULL;

	return;
}

hash_set* find_nth_hashItem(hash_table *table, int n){
	if(table->nElem < n){
		fprintf(stderr, "Table contains less than %d elements\n", n);
		return NULL;
	}
	hash_set *target = NULL;
	for(int i=0; n>0 && i<table->size; i++){
		target = table->set+i;
		while(target != NULL){
			if(target->key != NULL)
				if(--n == 0)
					break;
			target = target->next;
		}
	}
	return target;
}

hash_set* find_hashItem(hash_table *table, void *item, size_t size){
	size_t key = table->hash(item, size);
	hash_set *target = table->set + key % table->size;
	while(target != NULL){
		if(table->cmp_key(target->key, &key))
			target = target->next;
		else
			break;
	}
	return target;

}



int freeSet(hash_table *table, hash_set *set){
	if(set->key == NULL)
		return 0;

	table->nElem -= 1;
	free(set->key);
	free(set->data);
	if(set->next == NULL){
		set->key = NULL;
		set->data = NULL;
		return 0;
	}
	else{
		set->key = set->next->key;
		set->data = set->next->data;
		hash_set *tmp = set->next->next;
		free(set->next);
		set->next = tmp;
		return 1;
	}
}

void freeTable(hash_table **table){
	for(int i=0; i<(*table)->size; i++)
		while(freeSet((*table), (*table)->set+i));
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