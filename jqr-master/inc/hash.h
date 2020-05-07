#ifndef HASH_H_CUSHMAN
#define HASH_H_CUSHMAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "util.h"
#include "sort.h"

#define MATCH 0
#define WORD_SIZE 128

typedef struct bucket{
	size_t hash;
	void *key;
	void *data;
	struct bucket *next;
}bucket;

typedef struct hashTable{
	struct bucket *set;
	size_t tSize;
	size_t nElem;
	size_t (*hash)(void*, size_t);
	void (*cpykey)(void**, void*);
	int (*cmp_key)(void*, void*);
	size_t (*sizeof_key)(void*);
	void (*free_data)(void*);
	void (*print_set)(bucket);
}hash_table;


/**
 * Allocates memory and set inital values for hashTable struct.
 * Sets inital size of table to 16.
 */
hash_table* newHashTable(size_t (*hash)(void *key, size_t sizeof_key), 
	void (*cpykey)(void **dest, void *src), 
	int (*cmp_key)(void *key1, void *key2), size_t (*sizeof_key)(void *key), 
	void (*free_data)(void *data), void (*ptr_set)(bucket set));


/**
 * Inserts new set into hash table.
 */
void insertHashSet(hash_table *table, void *key, void *data);


/**
 * Increase the size of the table by 2^n+1.
 */
void growTable(hash_table *table);


/**
 * Find the nth item in the hash table.
 */
bucket* find_nth_hashItem(hash_table *table, int n);


/**
 * Find an item in the hash table. NULL is returned if key not found.
 */
bucket* find_key(hash_table *table, void *key);


/**
 * Frees a hash_set.
 * Returns:
 * 	0 - If the hash set is empty after freeing. (i.e. set.next == NULL)
 * 	1 - If the hash set was filled with the next set. (i.e. set.next != NULL)
 */
int freeSet(hash_table *table, bucket *set);


/**
 * Frees the hash tabel and sets array. Takes the address of the table in order
 * to set the table to NULL.
 */
void freeTable(hash_table **table);

#endif /* HASH_H_CUSHMAN */