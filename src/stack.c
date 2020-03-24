#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

node_t* mkStack(int num){
    if(num < 1){
        fprintf(stderr, "Stack size less than 1. Returned NULL.\n");
        return NULL;
    }
    return mkList(num, SINGLY);
}

node_t* push(node_t *top, void *value){
    node_t *new_node = mkNode(SINGLY);
    new_node->data = value;
    new_node->next = top;
    return new_node;
}

node_t* pop(node_t *top){
    if(top == NULL){
        fprintf(stderr, "Can't POP top is NULL\n");
        return NULL;
    }
    node_t *tmp;
    tmp = top->next;
    free(top->data);
    top->data = NULL;
    free(top);
    top = NULL;
    return tmp;
}

int get_stack_size(node_t *top){
    int size = 0;
    for(; top != NULL; size++)
        top = top->next;
    return size;
}

void rmStack(node_t *top){
    int size = get_stack_size(top);
    for(int i = 0; i<size; i++)
        top = pop(top);
    return;
}