#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void fun1(){
    printf("fun1\n");
}
typedef void (*func_t)(void);

int main()
{
    void *mem = malloc(sizeof(int));
    int *ptr = (int *)mem;
    *ptr = 16;
    
    printf("%d\n", *ptr);
    printf("%p\n", &ptr);
    printf("%d\n", ++ptr[0]);

    func_t fun_ptr = &fun1;
    (*fun_ptr)();

    int arr[100];
    for(int i=0;i<100;i++){
        arr[i] = i;
    }

    ptr = &arr[0];
    printf("%d\n", *ptr);
    ptr+=50;
    printf("%d\n", *ptr);

    free(mem);
    return 0;
}
