#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "list.h"
#include "util.h"

#define LIST_SIZE (18)

void datacpy(void *dest, void *src){
	*(int*)dest = *(int*)src;
	return;
}

void datafree(void **data){
	free(*data);
	*data = NULL;
	return;
}

void data_print(void *data){
	if(data == NULL)
		printf("(null)");
	else
		printf("%d", *(int*)data);
	return;
}

int main(void){
	srand(time(NULL));

	// Create a new list
	llist *list = llist_create(SINGLY, FALSE, datacpy, cmp_int, datafree);

	// Fill the list
	for(int i = 0; i < LIST_SIZE; i++){
		int *num = malloc(sizeof(int));
		*num = rand()%10;
		llist_insert(list, FALSE, NULL, num, sizeof(int));
		free(num);
		num = NULL;
	}

	llist_print(list, data_print);

	int num = 4;
	printf("Find the value %d in the list...\n", num);
	printf("Found ");
	data_print(llist_find(list, FALSE, &num, 1));
	printf("\n");

	printf("Sorting the list...\n");
	llist_sort(list);

	llist_print(list, data_print);

	num = 1;
	while(llist_delete(list, FALSE, &num))
		num++;

	printf("Delete first instance of %d from list...\n", num);

	llist_print(list, data_print);

	printf("Now put it back...\n");
	int tmp = num-1;
	llist_insert(list, FALSE, &tmp, &num, sizeof(int));
	
	llist_print(list, data_print);

	printf("Place a 15 at head and a 20 at tail...\n");
	num = 15;
	llist_insert(list, FALSE, NULL, &num, sizeof(int));
	
	llist_print(list, data_print);

	num = 20;
	tmp = -1;
	llist_insert(list, TRUE, &tmp, &num, sizeof(int));

	llist_print(list, data_print);

	llist_delete(list, FALSE, NULL);

	num = -1;
	llist_insert(list, TRUE, &num, &num, sizeof(int));

	llist_print(list, data_print);

	llist_destroy(&list);

	return 0;
}