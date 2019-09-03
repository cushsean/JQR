#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    int num[100];
    if(sizeof(num)/sizeof(int) != 100){
        goto term;
    }

    for(int i=0;i<100;i++){
        num[i] = i*2;
    }

    int i = 0;

    while(num[i] != 16){
        i++;
    }

    do{
        i++;
    }
    while(num[i] != 100);

    if(num[i] == 65){
        //Do this
    }
    else{
        //Do this
    }

    if(num[i] != 14){
        //Do this
    }
    else if(num[i] != 16){
        //Do this
    }
    else{
        //Do this
    }

    switch(num[i]%2){
    case 0:
        printf("False\n");
        break;
    case 1:
        printf("True\n");
        break;
    }

    term:
    return 0;
}
