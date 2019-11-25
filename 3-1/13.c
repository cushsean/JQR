#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//////////////////////////////////////////////
//	DICTIONARY USED: /usr/share/dict/words	//
//	TOTAL WORD COUNT: 102305				//
//	TOTAL COLLISIONS: 0						//
//////////////////////////////////////////////
unsigned long hash(char *input){
	const int MULT = 97;
	unsigned long h = 5;
	unsigned const char* str = (unsigned const char*)input;

	while(*str != '\0'){
		h = h * MULT + *str;
		str++;
	}
	return h;
}

int main(int argc, char* argv[]){

	if (argv[1] != NULL){
		printf("%lu\n", hash(argv[1]));
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
		fseek(dict, 0, SEEK_END);
		unsigned long *outputs = (unsigned long*) malloc(sizeof(unsigned long) * ftell(dict));
		int memSize = ftell(dict);
		rewind(dict);
		while(fgets(word, 128, dict)){
			outputs[word_count] = hash(word);
			for (int i = 0; i < word_count; i++){
				if (outputs[word_count] == outputs[i])
					collisions++;
			}
			if (memSize == word_count++){
				word_count--;
				break;
			}
		}
		printf("Word Count: %d\n", word_count);
		printf("Collisions: %d\n", collisions);
		if (fclose(dict) != 0)
			printf("Failed to close file\n");
	}
	return 0;
}