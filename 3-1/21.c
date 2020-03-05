#include <stdio.h>
#include <stdlib.h>

#define inc(x) ++x
#define sqr(x) x*x
#define add(x,y) (x+y)

int main(void){

    int num = 5;
    printf("num: %d\n", num);
    //increment num
    num = inc(num);
    printf("inc: %d\n", num);
    //square num
    num = sqr(num);
    printf("square: %d\n", num);
    //add num with 10
    num = add(num, 10);
    printf("add 10: %d\n", num);

    return 0;
}