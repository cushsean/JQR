#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

unsigned int hash(char *input){
	const int MULT = 97;
	unsigned long h = 5;
	unsigned char* str = (unsigned char*)input;
	for(int flag=0; flag < 2; flag++){
		while(*str != '\0'){
			h = h * MULT + *str;
			str++;
		}
		
		if(flag == 0)
			sprintf(str, "%lu", h);
	}
	h = h%99999999; //limits output to 8 digits
	return (int)h;
}