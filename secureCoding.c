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
	// Numbers are no-go. Replace all numbers with they're single digit alpha
	n = 8;
	safe_buffer = realloc(safe_buffer, n);
	for(int i = 0; (safe_buffer[i] = getchar()) != '\n'; i++){
		if(safe_buffer[i] == '0')
			safe_buffer[i] = 'a';
		else if(safe_buffer[i] == '1')
			safe_buffer[i] = 'b';
		else if(safe_buffer[i] == '2')
			safe_buffer[i] = 'c';
		else if(safe_buffer[i] == '3')
			safe_buffer[i] = 'd';
		else if(safe_buffer[i] == '4')
			safe_buffer[i] = 'e';
		else if(safe_buffer[i] == '5')
			safe_buffer[i] = 'f';
		else if(safe_buffer[i] == '6')
			safe_buffer[i] = 'g';
		else if(safe_buffer[i] == '7')
			safe_buffer[i] = 'h';
		else if(safe_buffer[i] == '8')
			safe_buffer[i] = 'i';
		else if(safe_buffer[i] == '9')
			safe_buffer[i] = 'j';
		if(i == n-1){
			n += 8;
			safe_buffer = realloc(safe_buffer, n);
		}
	}
	printf("%s\n", safe_buffer);

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
		// The complier could optimize this and not zero out all the memory 
		// but rather just "remove" the pointer if it is not used later in 
		// the program.
		char *ptr = malloc(128);
		memset(ptr, '\0', 128);
		
		// The complier wont optimize this and will actually set all memory 
		// to zero.
		char *pointer = malloc(128);
		volatile unsigned char *p = pointer;
		int size_to_remove = 128;
		while(size_to_remove--)
			*p++ = '\0';

	return 0;
}