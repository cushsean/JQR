#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

void handle_sigabrt(int sig){
	if(sig == 6){
		printf("ABORT is failure! Simply exit please.\n");
		exit(1);
	}
}

void handle_sigint(int sig){
	printf("Caught signal %d\n", sig);
	abort();
}

int main(void){

	signal(SIGINT, handle_sigint);
	signal(SIGABRT, handle_sigabrt);
	while(1==1){
		printf("hello world\n");
		sleep(1);
	}


	return 0;
}