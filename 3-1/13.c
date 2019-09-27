#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char* argv[]){

	const int MULT = 97;
	unsigned long h = 5;
	unsigned const char* str = (unsigned const char*)argv[1];

	while(*str != '\0'){
		h = h * MULT + *str;
		str++;
	}

	printf("%lu\n", h);

	return 0;
}