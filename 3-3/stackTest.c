#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "stack.h"
#include "util.h"

#define STACK_SIZE (10)

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

void stack_grow(stack_t* stack){
    if(stack_size(stack) < STACK_SIZE/2)
        for(int i = 0; i < STACK_SIZE; i++){
            int num = rand()%5;
            stack_push(stack, &num, sizeof(int));
        }
    stack_print(stack, data_print);
    return;
}

int main(void){
    srand(time(NULL));

    stack_t *stack = stack_create(datacpy, cmp_int, datafree);
    stack_grow(stack);

    stack_pop(stack);
    stack_grow(stack);

    int num = 3;
    printf("Find the 4th item...\n");
    data_print(stack_find(stack, TRUE, &num, 1));
    printf("\n");
    stack_grow(stack);

    printf("Find the first instance of the value 3...\n");
    data_print(stack_find(stack, FALSE, &num, 1));
    printf("\n");
    stack_grow(stack);

    num = 1;
    printf("Find the second instance of the value 1...\n");
    data_print(stack_find(stack, FALSE, &num, 2));
    printf("\n");
    stack_grow(stack);

    stack_destroy(&stack);

    return 0;
}