#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

void handle_sigabrt(int sig){
	if(sig == 6){
		printf("ABORT is failure! Simply exit please.\n");
		exit(EXIT_SUCCESS);
	}
}

void handle_sigint(int sig){
	printf("My parent wants me gone, he sent me sig %d\n", sig);
	abort();
}

void handle_sigchld(int sig){
	printf("My child has died, either naturally, or was killed\n");
}


int main(void){

	int pid;

	if((pid = fork()) > 0){
		// Parent does this
		// SIGABRT is set in parent process, therefore will only affect the 
		// parent aborting.
		signal(SIGABRT, handle_sigabrt);
		signal(SIGCHLD, handle_sigchld);
		while(pid > 0){
			printf("My Child is %d\n", pid);
			sleep(1);
			kill(pid, SIGINT);
			pid = 0;
			sleep(1);
		}
	}
	else if(pid == 0){
		// Child does this
		signal(SIGINT, handle_sigint);
		sleep(10); // Exits (or aborts really) prior to sleep completing
		// Never reaches this exit since the parent sends SIGINT which, through 
		// the handler, causes the process to abort.
		exit(EXIT_SUCCESS);
	}
	else{
		fprintf(stderr, "Error creating child\n");
	}


	return EXIT_SUCCESS;
}