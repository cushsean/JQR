#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void fun1(int *arr1){
    arr1[0] = 1;
    arr1[1] = 2;
    arr1[2] = 3;
    return;
}

void fun2(int arr2[3][3]){
    int k = 0;
    for(int i=0;i<3;i++)
        for(int n=0;n<3;n++)
            arr2[i][n] = ++k;
    return;
}

int main()
{

    int arr1[3];
    int arr2[3][3];

    fun1(arr1);
    printf("Contents of arr1:\n");
    for(int i=0;i<3;i++){
        printf("%d\n", arr1[i]);
    }
    printf("\n");
    fun2(arr2);
    printf("Contents of arr2:\n");
    for(int i=0;i<3;i++)
        for(int n=0;n<3;n++)
            printf("%d\n", arr2[i][n]);

    return 0;
}
