#include "hash.h"

unsigned long hash(char *input){
	const int MULT = 97;
	unsigned long h = 5;
	unsigned char* str = malloc(128);
	strcpy(str, (unsigned char*)input);
	for(int flag=0; flag < 2; flag++){
		while(*str != '\0'){\
			h = h * MULT + *str;
			str++;
		}
		
		if(flag == 0){
			sprintf(str, "%lu", h);
		}
	}
	h = h%LIMITER; //limits output LIMITER defined in hash.h
	return h;
}

char** hash_table(){
	char** table = (char**)malloc(LIMITER*sizeof(char*));
	for(int i=0; i<LIMITER; i++)
		table[i] = (char*)malloc(WORD_SIZE);
	return table;
}

char** hash_insert(char** table, void* input, int* collisions){
	char* str = malloc(128);
	strcpy(str, (char*)input);
	int len = strlen(str);
	if(len > 0 && str[len-1] == '\n')
		str[len-1] = '\0';
	
	unsigned long index = hash(str);
	if(strcmp(table[index], "") == MATCH)
		strcpy(table[index], str);
	else{
		(*collisions)++;
		while(strcmp(table[index], "") != MATCH)
			index++;
		strcpy(table[index], str);
	}
	
	free(str);
	return table;
}

void hash_free(char** table){
	for(int i=0; i<LIMITER; i++)
		free(table[i]);
	free(table);
	return;
}

long hash_find_byValue(char** table, void* input){
	char* str = malloc(128);
	strcpy(str, (char*)input);
	int len = strlen(str);
	if(len > 0 && str[len-1] == '\n')
		str[len-1] = '\0';
	
	unsigned long index = hash(str);
	while(table[index] == NULL)
		index++;
	if(strcmp(table[index], str) == MATCH){
		free(str);
		return index;
	}
	else{
		while(strcmp(table[index], str) != MATCH){
			if(++index == LIMITER){
				printf("%s not found in hash table.\n", str);
				free(str);
				return -1;
			}
		}
		free(str);
		return index;
	}
}

long hash_find_byNumber(char** table, unsigned long input){
	for(int i=0; i<LIMITER && input > 0; i++){
		if(strcmp(table[i], "") != MATCH)
			if(--input == 0)
				return i;
	}
	return -1;
}

char** hash_rmItem(char** table, void* input){
	long item_index = hash_find_byValue(table, input);
	if(item_index != -1){
		table[item_index] = NULL;
		printf("%s has been removed from hash table.\n", (char*)input);
	}
	return table;
}