#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define STATE_WAITING (0)
#define STATE_RECEIVING (1)
#define STATE_PROCESSING (2)
#define STATE_DISPENSING (3)
#define STATE_REFUND (4)
#define STATE_MAINTENANCE (5)

void state(int);
int selection();
void pay(float);
void process_payment(float);
void give_item();
void refund(float);
void maintenance();

int main(){
	int shutdown = 0;
	while(shutdown == 0){
		printf("\nWelcome to the vending machine.\n");
		if (selection() == 1)
			pay(1.15);	
		else
			maintenance(&shutdown);
	}
	return 0;
} 

void state(int state){
	char *sys_states[] = {
		"Waiting for selection.",
		"Receiving payment.",
		"Processing payment.",
		"Dispensing item.",
		"Issuing refund.",
		"Maintenance issue."
	};
	printf("%s\n", sys_states[state]);
	return;
}

int selection(){
	state(STATE_WAITING);
	int item;
	printf("Please select a product.\n");
	printf("0: Kick the Machine.\n");
	printf("1: Coke\n");
	item = getchar() - '0';
	getchar();	//Catch ENTER key
	return item;
}

void pay(float cost){
	state(STATE_RECEIVING);
	int input;
	printf("Please input your payment menthod:\n");
	while(cost > 0){
		printf("Balance: %.2f\n", cost);
		printf("1: Nickel\n");
		printf("2: Dime\n");
		printf("3: Quarter\n");
		printf("4: Refund\n");
		input = getchar() - '0';
		getchar();
		switch(input){
			case 1:
				cost -= 0.05;
			break;
			case 2:
				cost -= 0.10;
			break;
			case 3:
				cost -= 0.25;
			break;
			case 4:
				process_payment(cost);
				return;
			break;
			default:
			printf("Invalid form of payment.\n");
		}
	}
	process_payment(cost);
	return;
}

void process_payment(float cost){
	state(STATE_PROCESSING);
	sleep(2);
	if(cost <= 0){
		give_item();
		refund(cost * (-1));
	}
	else
		refund(1.15 - cost);
	return;
}

void give_item(){
	state(STATE_DISPENSING);
	sleep(2);
	return;
}

void refund(float cost){
	state(STATE_REFUND);
	cost *= 100;
	printf("Your change is below.\n");
	while(cost >= 25){
		printf("QUARTER\n");
		cost -= 25;
	}
	while(cost >= 10){
		printf("DIME\n");
		cost -= 10;
	}
	while(cost >= 5){
		printf("NICKEL\n");
		cost -= 5;
	}
	return;
}

void maintenance(int* shutdown){
	state(STATE_MAINTENANCE);
	*shutdown = 1;
	return;
}