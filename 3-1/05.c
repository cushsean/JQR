#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    int a = 5;
    int b = 2;
    float c = 5;
    float d = 2;
    int ans = 0;

    printf("The variables at play are set to 5 and 2.\n");

    //Addition
    printf("%d + %d = %d\n", a, b, a+b);

    //Subtraction
    printf("%d - %d = %d\n", a, b, a-b);

    //Multiplication
    printf("%d * %d = %d\n", a, b, a*b);

    //Division
    printf("%.0f / %.0f = %.1f\n", c, d, c/d);

    //Modulus
    printf("%d mod %d = %d\n", a, b, a%b);

    //Increment
    ans = ++a;
    printf("%d incremented by 1 = %d\n", --a, ans);

    //Decrement
    ans = --b;
    printf("%d decremented by 1 = %d\n", ++b, ans);

    //Order of Operation
    ans = --a+b%a*b/b++;
    printf("Lets break down Order of Operations with this line where a and b are 5 and 2 respectively:\n");
    printf("--a+bmod()a*b/b++\n");
    printf("This should return 6.\n");
    printf("1. a is decremented by 1; a is now 4.\n");
    printf("2. bmod()a is 2.\n");
    printf("3. 2*b is 4.\n");
    printf("4. 4/b is 2.\n");
    printf("5. 4+2=6.\n");
    printf("6. b is incremented by 1; b is now 3.\n");
    printf("--a+bmod()a*b/b++=%d; a=%d; b=%d\n", ans, a, b);


    return 0;
}
