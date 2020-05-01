#ifndef TEST_H_CUSHMAN
#define TEST_H_CUSHMAN

#include <stdlib.h>

/**
 * The structure of an apple.
 */
typedef struct APPLES apples;

/**
 * Set the color of an apple.
 */
void set_color(apples **an_apple, char *color);

/**
 * Set the quantity of an apple.
 */
void set_quantity(apples **an_apple, int quantity);

/**
 * Set the type of an apple.
 */
void set_type(apples **an_apple, char *type);


/**
 * Get the color of an apple.
 */
char* get_color(apples* an_apple);

/**
 * Get the quantity of an apple.
 */
int get_quantity(apples *an_apple);

/**
 * Get the type of an apple.
 */
char* get_type(apples *an_apple);

#endif /* TEST_H_CUSHMAN */