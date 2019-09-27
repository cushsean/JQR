#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void fun1(){
    printf("fun1\n");
}

int main()
{
    int *ptr;
    int num = 16;

    ptr = &num;

    printf("%d\n", *ptr);
    printf("%d\n", &ptr);
    printf("%d\n", ++ptr[0]);

    void (*fun_ptr)(void) = &fun1;
    (*fun_ptr)();

    int arr[100];
    for(int i=0;i<100;i++){
        arr[i] = i;
    }

    ptr = &arr[0];
    printf("%d\n", *ptr);
    ptr+=50;
    printf("%d\n", *ptr);


    return 0;
}
