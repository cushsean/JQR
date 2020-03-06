#include "util.h"

int cmp_int(void *var1, void *var2){
	int num1 = *((int*)var1);
	int num2 = *((int*)var2);
	if(num1 == num2)
		return 0;
	else if(num1 > num2)
		return 1;
	else if(num1 < num2)
		return -1;
	else{
		fprintf(stderr, "ERROR: Compare Failed\n");
		return 0;
	}
}

int cmp_ulong(void *var1, void *var2){
	unsigned long num1 = *((unsigned long*)var1);
	unsigned long num2 = *((unsigned long*)var2);
	if(num1 == num2)
		return 0;
	else if(num1 > num2)
		return 1;
	else if(num1 < num2)
		return -1;
	else{
		fprintf(stderr, "ERROR: Compare Failed\n");
		return 0;
	}
}

int cmp_str(void *var1, void *var2){
	return strcmp((char*)var1, (char*)var2);
}

void swap(void **a, void **b){
	void *tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}

void print_bin(char* buf, size_t len){
	for(size_t i=0; i < len; i++){
		printf("%x", buf[i]);
	}
	printf("\n");
	return;
}