#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "stack.h"
#include "list.h"
#include "util.h"

#define STACK_SIZE (20)

static node_t* fillStack(node_t *top){
    srand(time(NULL));
    node_t* curr = top;
    for(int i = 0; i < STACK_SIZE; i++){
        int *num = malloc(sizeof(int));
        *num = rand()%10;
        curr->data = num;
        curr = curr->next;
    }
    return top;
}

int main(void){

    node_t *top = mkStack(STACK_SIZE);
    top = fillStack(top);
    ptList(top, print_int);
    printf("\tsize: %d\n", get_stack_size(top));
    int num = 7;
    int *ptr = malloc(sizeof(int));
    *ptr = num;
    printf("\nPush value %d onto stack...\n", num);
    top = push(top, ptr);
    ptList(top, print_int);
    printf("\tsize: %d\n", get_stack_size(top));
    printf("\nThe value of the 3rd element is...\n");
    for(int i = 0; i < 2; i++)
        top = pop(top);
    print_int(top->data);
    printf("\n");
    ptList(top, print_int);
    printf("\tsize: %d\n", get_stack_size(top));
    num = 4;
    printf("\nA node with value of %d is ", num);
    int i = 1;
    for(; cmp_int(top->data, &num); i++){
        top = pop(top);
        if(top == NULL)
            break;
    }
    if(top != NULL)
        printf("the %d node in the stack.\n", i);
    else{
        printf("not found in the stack.\nStack is now empty.\n");
        return 0;
    }
    ptList(top, print_int);
    printf("\tsize: %d\n", get_stack_size(top));
    printf("\nRemoving all nodes destroying stack...\n");
    rmStack(top);
    printf("Stack is destroyed\n");
    return 0;
}