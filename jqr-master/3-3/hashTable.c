#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "list.h"
#include "util.h"


/**
 * Wrapper for the first level of printing sets.
 */
void print_set(bucket set);


/**
 * Prints the set with a determined level for tabing.
 */
void print_set_util(bucket set, int level);


/**
 * Fills the hash table with "num" number of words from the dictionary.
 * Pass 0 as num for entire dictionary.
 */
void fill_hashTable(hash_table *table, int num);


/**
 * User defined function for coping a key.
 */
void cpykey(void **dest, void *src);


/**
 * User defined function for freeing data.
 */
void free_data(void *data);

/**
 * User defined function to get size of the key.
 */
size_t sizeof_key(void *key);


/**
 * User defined function to compare keys.
 */
int cmpkey(void *key1, void *key2);


int cmpkey(void *key1, void *key2){
	return strcmp((char*)key1, (char*)key2);
}


size_t sizeof_key(void *key){
	return strlen((char*)key);
}

void free_data(void *data){
	free(data);
	data = NULL;
	return;
}

void cpykey(void **dest, void *src){
	memcpy(*dest, src, strlen((char*)src));
	return;
}


void print_set(bucket set){
	print_set_util(set, 1);
	printf("\n");
	return;
}

void print_set_util(bucket set, int level){
	if(set.key == NULL){
		for(int i=0; i<level; i++)
			printf("\t");
		printf("EMPTY\n");
	}
	else{
		char* key = (char*)set.key;
		char *data = (char*)set.data;
		for(int n=0; n<2; n++){
			for(int i=0; i<level; i++)
				printf("\t");
			if(n==0)
				printf("key  : %s\n", key);
			else if(n==1)
				printf("data : %s\n", data);
		}
		if(set.next != NULL){
			for(int i=0; i<level; i++)
				printf("\t");
			printf("Next :\n");
			print_set_util(*(set.next), level+1);
		}
	}
	return;
}

void fill_hashTable(hash_table *table, int num){

	FILE *dict;
	dict = fopen("/usr/share/dict/words", "r");
	if(dict == NULL){
		fprintf(stderr, "Failed to retrieve file\n");
		return;
	}

	if(num == 0){
		num = 102305; // Size of dictionary being used.
	}

	for(; num > 0; num--){
		char word[128];
		fgets(word, 127, dict);
		word[strlen(word)-1] = '\0'; // Strips the newline off the word
		
		char *data = calloc(strlen(word), sizeof(char));
		memcpy(data, word, strlen(word));
		insertHashSet(table, word, data);
	}
	fclose(dict);

	return;
}


int main(void){

	hash_table *table = newHashTable(hash, cpykey, cmpkey, sizeof_key,
										free_data, print_set);
	char *key = "CUSHMAN";
	char *name = "SEAN";
	char *data = calloc(strlen(name), sizeof(char));
	memcpy(data, name, strlen(name));
	insertHashSet(table, key, data);
	key = "Ballon";
	name = "HOT AIR";
	data = calloc(strlen(name), sizeof(char));
	memcpy(data, name, strlen(name));
	insertHashSet(table, key, data);
	
	// Expand the table
	fill_hashTable(table, 46);
	printf("Size: %ld\nElem: %ld\n\n", table->tSize, table->nElem);

	// Find an key
	printf("Find the item \"Ballon\"...\n");
	key = "Ballon";
	bucket *set_ptr = find_key(table, key);
	if(set_ptr == NULL)
		printf("Item not found.\n");
	else
		print_set(*set_ptr);

	// Find the nth item
	int num = 16;
	printf("Find item #%d...\n", num);
	set_ptr = find_nth_hashItem(table, num);
	if(set_ptr == NULL)
		printf("Item not found.\n");
	else
		print_set(*set_ptr);

	// Remove the previously found item
	printf("Size: %ld\nElem: %ld\n", table->tSize, table->nElem);
	printf("Removing set with item \"%s\"...\n\n", (char*)set_ptr->data);
	freeSet(table, set_ptr);
	printf("Size: %ld\nElem: %ld\n\n", table->tSize, table->nElem);

	printf("Find item #%d...\n", num);
	set_ptr = find_nth_hashItem(table, num);
	if(set_ptr == NULL)
		printf("Item not found.\n");
	else
		print_set(*set_ptr);
	
	printf("Size: %ld\nElem: %ld\n", table->tSize, table->nElem);

	freeTable(&table);
	return 0;
}