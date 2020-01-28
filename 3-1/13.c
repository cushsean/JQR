#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//////////////////////////////////////////////
//	DICTIONARY USED: /usr/share/dict/words	//
//	TOTAL WORD COUNT: 102305				//
//	TOTAL COLLISIONS: 0						//
//////////////////////////////////////////////
void padding(char* s){
	memmove(s + 1, s, strlen(s) + 1);
	memcpy(s, "0", 1);
}

char* hash(char *input){
	const int MULT = 97;
	unsigned long h = 5;
	unsigned char* str = (unsigned char*)input;
	int flag = 0;
	doubleHash:
	while(*str != '\0'){
		h = h * MULT + *str;
		str++;
	}
	
	char* hex = (char*)malloc(16*sizeof(char*));
	sprintf(hex, "%lx", h);
	while(strlen(hex)<16)
		padding(hex);
	if(flag == 0){
		flag = 1;
		strcpy(str,hex);
		goto doubleHash;
	}
	
	return hex;
}

int main(int argc, char* argv[]){

	if (argv[1] != NULL){
		printf("%s\n", hash(argv[1]));
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
		char **outputs = (char**)malloc(sizeof(char*) * 102305);
		for(int i=0;i<102305;i++)
			outputs[i] = (char*)malloc(sizeof(char) * 128);
		printf("Words in Dictionary: 102305\n");
		while(fgets(word, 128, dict)){
			outputs[word_count] = hash(word);
			printf("Current Word: %d\r",word_count);
			for(int i=0; i<word_count; i++){
				if(!strcmp(outputs[i], outputs[word_count])){
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
		
		for(int i=0;i<102305;i++)
			free(outputs[i]);
		free(outputs);
	}
	return 0;
}