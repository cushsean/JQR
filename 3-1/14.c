#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "util.h"
#include "sort.h"

int main(){

	int arr[20];
	int list[20];

	srand(time(NULL));

	for(int i=0; i<20; i++){
		arr[i] = rand()%100;
		list[i] = arr[i];
	}
	
	sort_bubble(arr, sizeof(arr)/sizeof(int), cmp_int);

	for(int i=0; i<20; i++){
		printf("%d\t%d\n",list[i],arr[i]);
	}

	return 0;
}