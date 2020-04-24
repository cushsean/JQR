#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


int main(void){

	// Formatting string vulnerabilites

		char *buf = "%p %p %p %p %p \n";
		
		// Wrong
		printf(buf);

		// Right
		printf("%s", buf);


	// Safe buffer size allocation

		char buffer[8];
		memset(buffer, '\0', 8); // Clearing the buffer before use.

		// Wrong
		for(int i = 0; (buffer[i] = getchar()) != '\n'; i++){
			if (i == 7){
				fprintf(stderr, "You just overflowed the buffer, ");
				fprintf(stderr, "preventing in oreder to continue\n\n");
				buffer[7] = '\0';
				while((getchar()) != '\n'); // Clear stdin
				break;
			}
		}

		printf("%s\n", buffer);

		// Right
		int n = 8;
		char *safe_buffer = calloc(n, sizeof(char));
		for(int i = 0; (safe_buffer[i] = getchar()) != '\n'; i++){
			if(i == n-1){
				n += 8;
				safe_buffer = realloc(safe_buffer, n);
			}
		}

		printf("%s\n", safe_buffer);


	// Input sanitation


	// Input validation
	n = 8;
	safe_buffer = realloc(safe_buffer, n);
	printf("Please enter a positive whole number: ");
	for(int i = 0; (safe_buffer[i] = getchar()) != '\n'; i++){
		if(safe_buffer[i] < '0' || safe_buffer[i] > '9'){
			if(safe_buffer[i] == '.')
				printf("Enter a whole number: ");
			else if ((safe_buffer[i] >= 'A' && safe_buffer[i] <= 'Z') ||
						(safe_buffer[i] >= 'a' && safe_buffer[i] <= 'z'))
				printf("Enter a number: ");
			else if (safe_buffer[0] == '-')
				printf("Enter a positive number: ");
			else
				printf("Entry not reconized. Enter a positive whole number: ");
			while((getchar()) != '\n'); // Clear stdin
		}
		if(i == n-1){
			n += 8;
			safe_buffer = realloc(safe_buffer, n);
		}
	}
	printf("Thank You.\n");


	// Modeling complex functionality as state-machines
		// Refer to 3-1/15.c

	
	// Establish a secure communications channel using an SLL library


	// Securely zeroing-out memory

	return 0;
}