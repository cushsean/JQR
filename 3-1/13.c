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
		unsigned long key = hash(argv[1], strlen(argv[1]));
		printf("%020lu\n", key);
	}
	else{
		FILE *dict;
		char word[128];
		
		dict = fopen("/usr/share/dict/words", "r");
		if (dict == NULL){
			printf("Failed to retrieve file\n");
			return 0;
		}
		printf("Words in Dictionary: 102305\n");
		while(fgets(word, 128, dict)){
			word[strlen(word)-1] = '\0'; // Strips off trailling newline
			printf("%s: ", word);
			for(int i = 18-strlen(word); i>0; i--)
				printf(" ");
			printf("\t%020lu\n", hash(word, strlen(word)));
		}
		fclose(dict);
	}
	return 0;
}