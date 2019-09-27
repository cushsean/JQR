#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

void state(int state){
	printf("The current state is: ");
	switch(state){
		case 0:
		printf("Waiting for selection.\n");
		break;
		case 1:
		printf("Receiving payment.\n");
		break;
		case 2:
		printf("Processing payment.\n");
		break;
		case 3:
		printf("Dispensing item.\n");
		break;
		case 4:
		printf("Issuing refund.\n");
		break;
		case 5:
		printf("Maintenance issue.\n");
	}
	return;
}

void refund(float cost){
	state(4);
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

int pay(float cost){
	int input;
	state(1);
	printf("Please input your payment menthod:\n");
	while(cost > 0){
		printf("Balance: %.2f\n", cost);
		printf("1: Nickel\n");
		printf("2: Dime\n");
		printf("3: Quarter\n");
		printf("4: Refund\n");
		input = getchar() - 48;
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
				refund(cost);
				return 0;
			break;
			default:
			printf("Invalid form of payment.\n");
		}
	}
	if(cost < 0){
		refund(cost * -1);
	}
	return 1;
}

int main(){

	int item;
	float cost;
	float payment;
	float running_total;

	printf("Welcome to the vending machine.\n");
	state(0);
	printf("Please select a product.\n");
	printf("0: Kick the Machine.\n");
	printf("1: Coke\n");

	item = getchar() - 48;
	getchar();

	switch(item){
		case 0:
			state(5);
		break;
		case 1:
			if(pay(1.15)){
				state(2);
				sleep(2);
				state(3);
				printf("Enjoy your Coke!\n");
			}
		break;
		default:
			printf("ERROR: Invalid input.\n\n");
			printf("NO DRINK FOR YOU!\n");
	}
	return 0;
} 