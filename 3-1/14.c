#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void sort_bubble(int *arr){
	for(int i=0; i<20; i++){
		for(int n=0; n<19; n++){
			if(arr[i] < arr[n]){
				int temp = arr[n];
				arr[n] = arr[i];
				arr[i] = temp;
			}
		}
	}
}

void sort_merge(int *arr){
	int size = sizeof(arr);
	while (size > 1){
		size /= 2;
	}
	
	
}

int main(){

	int arr[20];
	int list[20];

	srand(time(NULL));

	for(int i=0; i<20; i++){
		arr[i] = rand()%100;
		list[i] = arr[i];
	}
	
	sort_bubble(arr);
	//sort_merge(arr);
	

	for(int i=0; i<20; i++){
		printf("%d\t%d\n",list[i],arr[i]);
	}

	return 0;
} 