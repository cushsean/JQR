#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>


int main()
{
    char arr[100];

    printf("Please input a string that only contains letters and NOTHING else. Keep string to less than 100 chars:\n");

    fgets(arr, 100, stdin);

    printf("length: %ld\n%s\n", strlen(arr), arr);

    for(int i=0; i<strlen(arr); i++){
        //printf("%c", arr[i]);
        if(!(arr[i] == ' ' || arr[i] == '\n' || (arr[i] >= 'A' && arr[i] <= 'Z') || (arr[i] >= 'a' && arr[i] <= 'z'))){
            printf("YOU DONT LISTEN! NO SOUP FOR YOU\n");
            return 0;
        }
    }
    printf("You are a good listener.\n");
    return 0;
}
