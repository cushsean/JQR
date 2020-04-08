#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "list.h"
#include "util.h"


/**
 * Wrapper for the first level of printing sets.
 */
void print_set(hash_set set);


/**
 * Prints the set with a determined level for tabing.
 */
void print_set_util(hash_set set, int level);


/**
 * Fills the hash table with "num" number of words from the dictionary.
 * Pass 0 as num for entire dictionary.
 */
void fill_hashTable(hash_table *table, int num);


void print_set(hash_set set){
	print_set_util(set, 1);
	printf("\n");
	return;
}

void print_set_util(hash_set set, int level){
	if((unsigned long*)set.key == NULL){
		for(int i=0; i<level; i++)
			printf("\t");
		printf("EMPTY\n");
	}
	else{
		unsigned long key = *(unsigned long*)set.key;
		char *data = (char*)set.data;
		for(int n=0; n<3; n++){
			for(int i=0; i<level; i++)
				printf("\t");
			if(n==0)
				printf("key  : %020lu\n", key);
			else if(n==1)
				printf("data : %s\n", data);
			else if(n==2)
				printf("size : %ld\n", set.size);
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
		insertHashSet(table, word, strlen(word));
	}
	fclose(dict);

	return;
}


int main(void){

	hash_table *table = newHashTable(hash, cmp_ulong, print_set);
	char *name = "SEAN";
	insertHashSet(table, name, strlen(name));
	name = "Ballon";
	insertHashSet(table, name, strlen(name));
	
	fill_hashTable(table, 46);
	printf("Size: %ld\nElem: %ld\n\n", table->size, table->nElem);

	printf("Find the item \"Ballon\"...\n");
	hash_set *set_ptr = find_hashItem(table, name, strlen(name));
	if(set_ptr == NULL)
		printf("Item not found.\n");
	else
		print_set(*set_ptr);

	
	int num = 16;
	printf("Find item #%d...\n", num);
	set_ptr = find_nth_hashItem(table, num);
	if(set_ptr == NULL)
		printf("Item not found.\n");
	else
		print_set(*set_ptr);

	printf("Removing set with item \"%s\"...\n\n", (char*)set_ptr->data);
	freeSet(table, set_ptr);

	printf("Find item #%d...\n", num);
	set_ptr = find_nth_hashItem(table, num);
	if(set_ptr == NULL)
		printf("Item not found.\n");
	else
		print_set(*set_ptr);
	
	// for(int i=0; i<table->size; i++){
	// 	if(table->set[i].key != NULL){
	// 		printf("Set %d:\n", i);
	// 		print_set(table->set[i]);	
	// 	}
	// }
	
	printf("Size: %ld\nElem: %ld\n", table->size, table->nElem);

	freeTable(&table);
	return 0;
}