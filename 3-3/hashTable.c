#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "list.h"
#include "encode.h"


/**
 * Prints the set to standard out.
 */
void print_set(hash_set set);

/**
 * Hashing scheme that returns an unsigned long.
 */
unsigned long hash(char *input, size_t size);


/**
 * Fills the hash table with "num" number of words from the dictionary.
 * Pass 0 as num for entire dictionary.
 */
void fill_hashTable(hash_table *table, int num);

void print_set(hash_set set){
	if((unsigned long*)set.key == NULL)
		printf("\tEMPTY\n");
	else{
		unsigned long key = *(unsigned long*)set.key;
		char *data = (char*)set.data;
		printf("\tkey  : %020lu\n\tdata : %s\n", key, data);
		if(set.next != NULL){
			printf("\tNext :\n\n");
			print_set(*(set.next));
		}
		printf("\n");
	}
}

unsigned long hash(char *input, size_t size){
	
	unsigned long key = 0;
	int c;

	while(c = *input++)
		key = c + (key << 6) + (key << 16) - key;
	

	// Double hash
	char buf[21];
	sprintf(buf, "%020lu", key);
	buf[20] = '\0';
	for(int i=0; i<20; i++)
		key = buf[i] + (key << 6) + (key << 16) - key;

	return key;
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
		char *word = calloc(128, sizeof(char));
		fgets(word, 128, dict);
		word[strlen(word)-1] = '\0'; // Strips the newline off the word
		insertHashSet(table, word, strlen(word));
	}

	return;
}

int main(void){

	hash_table *table = newHashTable(hash, cmp_ulong, print_set);
	char *name = calloc(128, sizeof(char));
	name = "SEAN";
	// name[4] = '\0';
	insertHashSet(table, name, strlen(name));
	name = "Ballon";
	// name[6] = '\0';
	insertHashSet(table, name, strlen(name));
	
	fill_hashTable(table, 10);




	for(int i=0; i<table->size; i++){
		printf("Set %d:\n", i);
		table->print_set(table->set[i]);	
	}
	printf("Size: %ld\nElem: %ld\n", table->size, table->nElem);

	freeTable(&table);
	return 0;
}