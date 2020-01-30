#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "list.h"
#include "hash.h"

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
		char word[128];
		int word_count = 0;
		int collisions = 0;
		
		dict = fopen("/usr/share/dict/words", "r");
		if (dict == NULL){
			printf("Failed to retrieve file\n");
			return 0;
		}
		node_t** outputs = hash_table();
		printf("Words in Dictionary: 102305\n");
		while(fgets(word, 128, dict)){
			printf("Current Word: %d\r",word_count);
			hash_insert(outputs, word, &collisions);
			word_count++;
		}
		printf("Current Word: 102305\n");
		printf("Collisions: %d\n", collisions);
		char* str = "apples";
		void* ptr = str;
		char* tmp = (char*)ptr;
		printf("%s\n",(char*)ptr);
		printf("%s\n", tmp);
		unsigned long hex = hash("apples\0");
		//hash_find_byValue(outputs, str, 1);
		printf("close\n");
		if (fclose(dict) != 0)
			printf("Failed to close file\n");
		hash_free(outputs);
	}
	return 0;
}