#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "util.h"
#include "sort.h"

#define size_arr (200)

int main(){

	int arr[size_arr];
	int list[size_arr];

	srand(time(NULL));

	for(int i=0; i<size_arr; i++){
		arr[i] = rand()%100;
		list[i] = arr[i];
	}

	sort_bubble_array(arr, size_arr, sizeof(arr[0]), cmp_int);

	for(int i=0; i<size_arr; i++){
		printf("%d\t%d\n",list[i],arr[i]);
	}

	return 0;
}