#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "list.h"
#include "util.h"

int keycmp(void *key1, void *key2){
	return strcmp((char*)key1, (char*)key2);
}

void datafree(void *data){
	free(data);
	data = NULL;
	return;
}

void keycpy(void **dest, void *src){
	*dest = strdup(src);
	return;
}


void print_data(void *data){
	if(data == NULL)
		printf("null");
	else
		printf("%s", (char*)data);
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
		
		char *data;
		data = strdup(word);
		hashTable_insert(table, word, data, strlen(word));
	}
	fclose(dict);

	return;
}


int main(void){

	hash_table *table = hashTable_create(hash, keycpy, keycmp, 
										datafree);
	char *key = "CUSHMAN";
	char *name = "SEAN";
	char *data;
	data = strdup(name);
	hashTable_insert(table, key, data, strlen(key));
	key = "Ballon";
	name = "HOT AIR";
	free(data);
	data = strdup(name);
	hashTable_insert(table, key, data, strlen(key));
	free(data);
	data = NULL;

	hashTable_print(table, print_data);
	
	// Expand the table
	fill_hashTable(table, 46);
	printf("Size: %ld\n\n", hashTable_size(table));

	hashTable_print(table, print_data);

	// Find an key
	printf("Find the item \"Ballon\"...\n");
	key = "Ballon";
	print_data(hashTable_find(table, FALSE, key));
	printf("\n");

	// Find the nth item
	int num = 16;
	printf("Find item #%d...\n", num);
	print_data(hashTable_find(table, TRUE, &num));
	printf("\n");

	// Remove the previously found item
	printf("Size: %ld\n\n", hashTable_size(table));
	printf("Removing the previously found item...\n");
	hashTable_delete(table, TRUE, &num);
	printf("Size: %ld\n\n", hashTable_size(table));

	hashTable_print(table, print_data);

	hashTable_destroy(&table);
	return 0;
}