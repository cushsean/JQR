#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "list.h"
#include "hash.h"
#include "util.h"

//////////////////////////////////////////////
//	DICTIONARY USED: /usr/share/dict/words	//
//	TOTAL WORD COUNT: 102305				//
//	HASH LENGTH: 16 DIGITS 					//
//	TOTAL COLLISIONS: 0						//
//	HASH LENGTH: 08 DIGITS 					//
//	TOTAL COLLISIONS: 39					//
//////////////////////////////////////////////

int main(int argc, char* argv[]){

	if (argc == 2){
		unsigned long hex = hash(argv[1]);
		printf("%08lu\n", hex);
	}
	else{
		FILE *dict;
		char* word = malloc(WORD_SIZE);
		int word_count = 0;
		int collisions = 0;
		
		dict = fopen("/usr/share/dict/words", "r");
		if (dict == NULL){
			printf("Failed to retrieve file\n");
			return 0;
		}
		//char** table = hash_table();
		meta_h* table = hash_new_table();
		printf("Words in Dictionary: 102305\n");
		while(fgets(word, 128, dict)){
			printf("Current Word: %d\r",word_count);
			//table = hash_insert(table, word, &collisions);
			word_count++;
		}
		printf("Current Word: 102305\n");
		printf("Collisions: %d\n", collisions);
		////////////////////////////
		/*
		printf("Find by Value...\n");
		char* hstr = malloc(WORD_SIZE);
		hstr = "hos";
		unsigned long hstr_hash = hash(hstr);
		long index = hash_find_byValue(table, hstr);
		if(index != -1){
			printf("Key: %s\n", hstr);
			printf("Hash: %08lu\n", hstr_hash);
			printf("Index: %08ld\n", index);
		}
		/////////////////////////////
		printf("Find by Number...\n");
		index = hash_find_byNumber(table, 13);
		if(index != -1){
			char* key = table[index];
			hstr_hash = hash(key);
			printf("Key: %s\n", table[index]);
			printf("Hash: %08lu\n", hstr_hash);
			printf("Index: %08ld\n", index);
		}
		////////////////////////////
		hstr = "algebras";
		table = hash_rmItem(table, hstr);
		////////////////////////////
		printf("Find by Value...\n");
		hstr = "hos";
		hstr_hash = hash(hstr);
		index = hash_find_byValue(table, hstr);
		if(index != -1){
			printf("Key: %s\n", hstr);
			printf("Hash: %08lu\n", hstr_hash);
			printf("Index: %08ld\n", index);
		}
		*/
		////////////////////////////
		if (fclose(dict) != 0)
			printf("Failed to close file\n");
		//hash_free(table);
	}
	return 0;
}