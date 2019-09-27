#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int testConnection(FILE *fptr){
    if(fptr == NULL)
        return 0;
    else
        return 1;
}

void send(FILE *fptr){
    char c;
    while((c = fgetc(fptr)) != EOF){
        printf("%c", c);
    }
    printf("\n");
    return;
}

int main()
{
    FILE *fptr;
    char arr[50] = "This is a new file.";

    fptr = fopen("txt.txt", "w");

    if(testConnection(fptr)){
        printf("The file opened.\n");
        fputs(arr, fptr);
        fputs("\n", fptr);
        fclose(fptr);
    }

    fptr = fopen("txt.txt", "r");

    if(testConnection(fptr)){
        printf("The file contatins:\n");
        fgets(arr, 50, fptr);
        printf("%s\n", arr);
        fclose(fptr);
    }

    fptr = fopen("txt.txt", "a");

    if(testConnection(fptr)){
        printf("The file has been appended.\n");
        fputs("This is a new line.\n", fptr);
        fclose(fptr);
    }

    fptr = fopen("txt.txt", "r");

    if(testConnection(fptr)){
        printf("\nThe file now contains:\n");
        send(fptr);
        fclose(fptr);
    }

    fptr = fopen("txt.txt", "r+");

    if(testConnection(fptr)){
        fseek(fptr, 29, SEEK_SET);
        //fseek(fptr, 0, 29);
        //ftell(fptr);
        fputs("not a new line.\n", fptr);
        //send(fptr);
        fclose(fptr);
    }

    fptr = fopen("txt.txt", "r");

    if(testConnection(fptr)){
        printf("And now it reads:\n");
        send(fptr);
        //printf("%d\n", ftell(fptr));
        fseek(fptr, 0, SEEK_END);
        printf("The files size is %d\n", ftell(fptr));
        fclose(fptr);
    }

    printf("The file has been deleted.\n");
    remove("txt.txt");

    fprintf(stdout, "\nDONE!\n");

    return 0;
}
