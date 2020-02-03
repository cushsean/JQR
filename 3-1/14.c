#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../inc/util.h"

void sort_bubble(void*, size_t, void (*cmp_ptr)(void*, void*));
//int (*dfgdhgfd)(void*, void*);

void sort_bubble(void *arr, size_t nmemb, void (*cmp_ptr)(void*, void*)){
	printf("THE BUBBLE\n");
	//int* array = (int *)arr;
	
	for(int i=0; i<nmemb; i++){
		for(int n=0; n<nmemb-1; n++){
			(*cmp_ptr)((arr+i), (arr+n));
		}
	}
	printf("\n\n");
	return;
}

int main(){

	int arr[20];
	int list[20];

	srand(time(NULL));

	for(int i=0; i<20; i++){
		arr[i] = rand()%100;
		list[i] = arr[i];
	}
	
	sort_bubble(arr, sizeof(arr), cmp_int);

	for(int i=0; i<20; i++){
		printf("%d\t%d\n",list[i],arr[i]);
	}

	return 0;
}