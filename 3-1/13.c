#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

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
		unsigned int hex = hash(argv[1]);
		printf("%08u\n", hex);
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
		unsigned int outputs[102305];
		printf("Words in Dictionary: 102305\n");
		while(fgets(word, 128, dict)){
			outputs[word_count] = hash(word);
			printf("Current Word: %d\r",word_count);
			for(int i=0; i<word_count; i++){
				if(outputs[i] == outputs[word_count]){
					collisions++;
					break;
				}
			}
			word_count++;
		}
		printf("Current Word: 102305\n");
		printf("Collisions: %d\n", collisions);
		if (fclose(dict) != 0)
			printf("Failed to close file\n");
	}
	return 0;
}