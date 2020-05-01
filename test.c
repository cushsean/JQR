#include <stdlib.h>
#include <stdio.h>

#include "test.h"

int main(void){
	apples *a;

	// This doesn't work
	// a->color = "GREEN";
	// a->quantity = 10;
	// a->type = "SOUR";

	// This requries a function to write and another to read each
	// item within the struct.
	set_color(&a, "GREEN");
	set_quantity(&a, 10);
	set_type(&a, "SOUR");

	printf("There was %d apples, ", get_quantity(a));
	printf("they were %s apples, ", get_color(a));
	printf("therefore they had to be %s apples.\n", get_type(a));

	return 0;
}