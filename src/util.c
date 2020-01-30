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

void swap_int(void *num1, void* num2){
	if(cmp_int(num1, num2)){
		int tmp = *(int*)num1;
		*(int*)num1 = *(int*)num2;
		*(int*)num2 = tmp;
	}
	return;
}