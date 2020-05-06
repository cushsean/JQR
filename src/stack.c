#include <stdlib.h>
#include <stdio.h>

#include "stack.h"


// PRIVATE FUNCTIONS


static void* find_nth(stack_t *stack, void *nth){
    int n = *(int*)nth;
    if(n > stack_size(stack)){
        fprintf(stderr, "n is greater than the number of items in the stack.\n");
        return NULL;
    }
    for(; n > 0; n--)
        stack_pop(stack);

    return llist_find(stack, TRUE, &n, 0);
}

static void* find_item(stack_t *stack, void *item, size_t nth){
    int num = 0;
    for(; nth > 0; nth--, stack_pop(stack)){
        while(llist_cmp(stack, llist_find(stack, TRUE, &num, 0), item) != 0 && 
                stack_size(stack))
            stack_pop(stack);
    }

    return llist_find(stack, TRUE, &num, 0);
}

// PUBLIC FUNCTIONS


stack_t* stack_create(void (*datacpy)(void *dest, void *src), 
					    int (*datacmp)(void *data1, void *data2),
					    void (*datafree)(void **data)){
    stack_t *stack = llist_create(SINGLY, FALSE, datacpy, datacmp, datafree);
    return stack;
}

void stack_push(stack_t *stack, void *data, size_t size){
    return llist_insert(stack, FALSE, NULL, data, size);
}

int stack_pop(stack_t *stack){
    int num = 0;
    return llist_delete(stack, TRUE, &num);
}

void stack_destroy(stack_t **stack){
    return llist_destroy(stack);
}

void stack_print(stack_t *stack, void (*data_print)(void *data)){
    return llist_print(stack, data_print);
}

size_t stack_size(stack_t *stack){
    return llist_size(stack);
}

void* stack_find(stack_t *stack, int nth_mode, void *item, size_t nth_instance){
    if(nth_mode == TRUE)
        return find_nth(stack, item);
    else
        return find_item(stack, item, nth_instance);
}