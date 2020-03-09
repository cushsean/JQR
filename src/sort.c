#include "sort.h"

void sort_bubble(int *arr, size_t nmemb, int (*cmp_ptr)(void*, void*)){
	printf("THE BUBBLE\n");
	
	for(int i=0; i<nmemb-1; i++){
		for(int n=0; n<nmemb-i-1; n++){
			printf("n%d: %d\t%d\n", n, arr[n], arr[n+1]);
			if(1 == (*cmp_ptr)(arr+n, arr+n+1)){
                //void **a = &arr+i;
                //void **b = &arr+n;
                swap((void**)&arr+n, (void**)&arr+n+1);
            }
		}
	}
	printf("\n\n");
	return;
}