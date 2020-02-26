#ifndef HASH_H_CUSHMAN
#define HASH_H_CUSHMAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "util.h"

#define MATCH 0
#define LIMITER 99999999
#define WORD_SIZE 128

typedef struct hash_node{
	char* key;
	void* data;
	char* valid_node;
}node_h;

typedef struct hash_table_meta{
	node_h** set;
	size_t size;
	size_t num_elem;
	//unsigned long (*hash)(void);
	//void* (*key_cpy)(void*);
	//int (*key_cmp)(void*, void*);
}meta_h;

meta_h* hash_new_table(void);
int hash_insert_node(meta_h* table, char* key);
void* hash_get_node(meta_h* table, char* key);
int hash_rm_node(meta_h* table, char* key);

//Old functions below
unsigned long hash(char*);
char** hash_table();
char** hash_insert(char**, void*, int*);
void hash_free(char**);
long hash_find_byValue(char**, void*);
long hash_find_byNumber(char**, unsigned long);
char** hash_rmItem(char**, void*);
#endif /* HASH_H_CUSHMAN */