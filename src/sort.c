#include "sort.h"

void sort_bubble_array(void *arr, size_t nmemb, size_t e_size, 
	int (*cmp_ptr)(void*, void*)){
	for(int i=0; i<nmemb-1; i++){
		for(int n=0; n<nmemb-1-i; n++){
			void *a = (char*)arr + n * e_size;
			void *b = (char*)arr + (n+1) * e_size;
			if(1 == (*cmp_ptr)(a, b))
                swap(a, b, e_size);
		}
	}
	printf("\n\n");
	return;
}

node_t* sort_bubble_list(void *head, int (*cmp_ptr)(void*, void*)){
	
	// printf("SORTING...\n");

	node_t *curr = head;
	int size = countList(head);
	node_t *NX = NULL;
	node_t *PR = NULL;
	int swapped;

	for(int i=0; i<size-1; i++){
		for(int n=0; n<size-1-i; n++){

			NX = curr->next;
			if((*cmp_ptr)(curr->data, NX->data) == 1){
				if(curr->type == SINGLY){
					head = swap_node_singly(head, curr, NX, PR);
					PR = NX;
				}
				else
					head = swap_node(head, curr, NX);
				swapped = 1;
			}
			else{
				PR = curr;
				curr = curr->next;
			}
		}
		curr = head;
		PR = NULL;

	}

	/**
	 * Below is a sort that does not need he size of the list.
	 * For SINGLY and DOUBLy it works perfectly.
	 * For CIRCULARLY it breaks with the first value in the
	 * 	list is greater than the second. 
	 **/
	
	/*
	// printf("\n\nSORTING\n\n");
	node_t *curr = head;
	node_t *last = get_tail(head)->next;
	printf("Last is ");
	print_int(last->data);
	printf("\n");
	node_t *NX = NULL;
	int swapped;

	do{
		ptList(head, print_int);
		swapped = 0;
		while(curr->next != last){
			NX = curr->next;
			if((*cmp_ptr)(curr->data, NX->data) == 1){
				head = swap_node(head, curr, NX);
				swapped = 1;
			}
			else
				curr = curr->next;
		}
		last = curr;
		printf("Last is ");
		print_int(last->data);
		printf("\n");
		curr = head;
		// printf("Head is ");
		// //print_int(head->data);
		// printf("\n");
	}while(swapped);
	printf("Done");
	*/


	return head;
}

