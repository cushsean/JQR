#include "test.h"

struct APPLES{
	char *color;
	int quantity;
	char *type;
};

void set_color(apples **an_apple, char *color){
	(*an_apple)->color = color;
	return;
}

void set_quantity(apples **an_apple, int quantity){
	(*an_apple)->quantity = quantity;
	return;
}

void set_type(apples **an_apple, char *type){
	(*an_apple)->type = type;
	return;
}

char* get_color(apples *an_apple){
	return an_apple->color;
}

int get_quantity(apples *an_apple){
	return an_apple->quantity;
}

char* get_type(apples *an_apple){
	return an_apple->type;
}