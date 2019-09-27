#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char* argv[], char* envp[])
{
    printf("This program contains %d command line arguments.\n", argc-1);

    if(argc > 1){
        printf("The arguments are:\n");
        for(int i=1; i < argc; i++){
            printf("%s\n",argv[i]);
        }
    }

    char *home;
    char *host;

    home = getenv("HOME");
    host = getenv("HOSTNAME");

    printf("Your home dir is %s on %s.\n", home, host);



    return 0;
}
