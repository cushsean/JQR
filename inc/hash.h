#ifndef HASH_H_CUSHMAN
#define HASH_H_CUSHMAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "util.h"

#ifndef TRUE
#define TRUE (1)
#define FALSE (0)
#endif

#define MATCH 0
#define WORD_SIZE 128

typedef struct bucket bucket;

typedef struct hashTable hash_table;


/**
 * Sets up the hash table.
 * 
 * Returns pointer to table with type hash_table.
 * 
 * hash: User defined function.
 * 	Takes the key and sizeof the key as parameters and returns a hash of type
 * 	size_t.
 * 
 * keycpy: User defined function.
 * 	Copies the key from src to dest.
 * 
 * keycmp: User defined function.
 * 
 * 			Return:
 * 				 1 if data1 > data2
 * 				 0 if data1 == data2
 * 				-1 if data1 < data2
 * 
 * datafree: User defined fucntion to free data stored in linked list.
 * 	
 */
hash_table* hashTable_create(size_t (*hash)(void *key), 
	void (*keycpy)(void *dest, void *src), 
	int (*keycmp)(void *key1, void *key2),  
	void (*datafree)(void *data));


/**
 * Inserts new set into hash table.
 * 
 * Size is the size of the key.
 */
void hashTable_insert(hash_table *table, void *key, void *data, size_t size);


/**
 * Finds an item in the hash table and returns a void pointer to the data of 
 * that item.
 * 
 * nth_mode:
 * 		TRUE: Return a pointer to the data that is nth in the table. Key is an
 * 				interger pointer.
 * 		FALSE: Return a pointer ot the data that has a key that matches key.
 * 
 * Returns NULL on Failure.
 */
void* hashTable_find(hash_table *table, int nth_mode, void *key);


/**
 * Removes an item from the hash table.
 * 
 * nth_mode:
 * 		TRUE: Removes the nth item in the hash table. key is an int pointer 
 * 				containing n.
 * 		FALSE: Removes the item in the hash table. key is the key for the item 
 * 				to be removed.
 * 
 * To remove all items from the hash table, set nth_mode to FALSE and 
 * 	set key to NULL. All items will be removed but the hash table will still 
 * 	exist. To remove the hash table itself, call hashTable_destroy().
 * 
 * Returns 0 on success.
 * Returns 1 on Failure.
 */
int hashTable_delete(hash_table *table, int nth_mode, void* key);


/**
 * Removes all items from the hash table and destroies the table itself.
 */
void hashTable_destroy(hash_table **table);


/**
 * Returns the number of elements in the hash table.
 */
size_t hashTable_size(hash_table *table);


/**
 * Prints out the items in the hash table.
 */
void hashTable_print(hash_table *table, void (*print_data)(void *data));

#endif /* HASH_H_CUSHMAN */