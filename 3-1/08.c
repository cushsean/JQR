#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void fun_b(){
    printf("This function returns a void.\n");
    return;
}

void fun_c(int num){
    printf("This function is passed the value %d.\n", num);
    return;
}

void fun_d(int *num){
    printf("This function is passed the reference of %d.\n", num[0]);
    return;
}

int fun_e(int a, int b){
    return a+b;
}

void fun_f(int *ptr, int *ptr2){
    *ptr += *ptr2;
    return;
}

void fun_g(){
    int a = 0;
    int b = 0;
    printf("Please enter the first number you want to add: ");
    scanf("%d", &a);
    printf("Please enter the second number you want to add: ");
    scanf("%d", &b);
    printf("Answer: %d\n", a+b);
    return;
}

void fun_h(){
    printf("This function is call by a function pointer.\n");
    return;
}
typedef void (*func_t)();

void recursion(int i, int end){
    if (i > end){
        int tmp = i;
        i = end;
        end = tmp;
    }
    if (i++ == end){
        printf("End of recursion\n");
        return;
    }
    else return recursion(i, end);
    //For a more practical application refer to 3.3.2
}

int main()
{
    fun_b();
    int num = 5;
    fun_c(num);
    fun_d(&num);
    int num2 = 4;
    printf("This function adds %d and %d and returns the answer %d.\n", num, num2, fun_e(num,num2));
    printf("This function receives the value %d, adds %d to it and return the answer, ", num, num2);
    fun_f(&num, &num2);
    printf("%d, by reference.\n", num);
    fun_g();
    func_t fun_ptr = &fun_h;
    fun_ptr();
    recursion(0, 20);
    return 0;
}
