#ifndef HASH_H_CUSHMAN
#define HASH_H_CUSHMAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "util.h"
#include "sort.h"

#define MATCH 0
#define LIMITER 99999999
#define WORD_SIZE 128

typedef struct hashSet{
	void *key;
	void *data;
	size_t size;
	struct hashSet *next;
}hash_set;

typedef struct hashTable{
	struct hashSet *set;
	size_t size;
	size_t nElem;
	unsigned long (*hash)(char*, size_t);
	int (*cmp_key)(void*, void*);
	void (*print_set)(hash_set);
}hash_table;


/**
 * Allocates memory and set inital values for hashTable struct.
 * Sets inital size of table to 16.
 */
hash_table* newHashTable(unsigned long (*hash)(char*, size_t), 
	int (*cmp_key)(void*, void*), void (*ptr_set)(hash_set));


/**
 * Inserts new set into hash table.
 */
void insertHashSet(hash_table *table, void *data, size_t size);


/**
 * Increase the size of the table by 2^n+1.
 */
void growTable(hash_table *table);


/**
 * Find the nth item in the hash table.
 */
hash_set* find_nth_hashItem(hash_table *table, int n);


/**
 * Find an item in the hash table.
 */
hash_set* find_hashItem(hash_table *table, void *item, size_t size);


/**
 * Frees a hash_set.
 * Returns:
 * 	0 - If the hash set is empty after freeing. (i.e. set.next == NULL)
 * 	1 - If the hash set was filled with the next set. (i.e. set.next != NULL)
 */
int freeSet(hash_table *table, hash_set *set);


/**
 * Frees the hash tabel and sets array. Takes the address of the table in order
 * to set the table to NULL.
 */
void freeTable(hash_table **table);

#endif /* HASH_H_CUSHMAN */