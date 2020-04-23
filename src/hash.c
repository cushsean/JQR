/*
*	05FEB2020
*	Need to modify hash_table to be an actual table
*	instead of a hash_set as it currently is.
*	The table should include both the KEY and DATA,
*	both of which should be void*. The table should not
*	start at 99999999 (LIMITER) like it is but rather 
*	start small like 16 and grow at a rate of 2^n,
*	n starting at 4 and increasing when num_elem is
*	equal to 3/4 2^n. When the table_size increase,
*	the index for each hash in the table will need to be
*	increased as well. This will be done in the grow_table
*	function. The elements of the table should be a struct
*	that contains the key and any data. ex)
*		struct bucket{
*			void* key;
*			void* data;
*		}
*	A separte struct should be used to hold the tables
*	meta data. ex)
*		struct hash_table{
*			struct bucket* array;
*			size_t table_size;
*			size_t num_elem;
*			ulong (*hash)(void*);
*			void* (*key_cpy)(void*);
*			int (*key_cmp)(void*, void*)
*		}
*	The following functions should be used to perform
*	operations on the hash_table:
*	1)	struct hash_table* new_hash_table(
*			ulong (*hash)(void*),
*			void* (*key_cpy)(void*),
*			int (*key_cmp)(void*,void*)
*		)
*	2)	int insert_hash_table(
*			struct hash_table*,
*			void* key,
*			void* value
*		)
*	3)	void* get_hash_table(
*			struct hash_table*,
*			void* key
*		)
*	4)	int rm_hash_table(
*			struct hash_table*,
*			void* key
*		)
*/

#include "hash.h"

/**
 * Local Function for inserting buckets where a bucket exists.
 */
static void shiftSet(hash_table *table, size_t index, 
						size_t hash, void *key, void *data);

hash_table* newHashTable(unsigned long (*hash)(void *key, size_t sizeof_key), 
							void (*cpykey)(void **dest, void *src), 
							int (*cmp_key)(void *key1, void *key2),
							size_t (*sizeof_key)(void *key),
							void (*free_data)(void *data),
							void (*print_set)(bucket set)){
	hash_table *table = calloc(1, sizeof(hash_table));
	table->tSize = 16;
	table->set = calloc(table->tSize, sizeof(bucket));
	table->nElem = 0;
	table->hash = hash;
	table->cpykey = cpykey;
	table->cmp_key = cmp_key;
	table->sizeof_key = sizeof_key;
	table->free_data = free_data;
	table->print_set = print_set;
	return table;
}


static void shiftSet(hash_table *table, size_t index, 
						size_t hash, void *key, void *data){
	// bucket *tmp = calloc(1, sizeof(bucket));

	bucket *tmp = table->set+index;

	while(tmp != NULL){
		if(table->cmp_key(tmp->key, key) == 0){
			// Key is alread in table, update data
			table->free_data(tmp->data);
			tmp->data = data;

			return;
		}
		
		tmp = tmp->next;
	}

	// Key is not in table
	tmp = calloc(1, sizeof(bucket));

	tmp->hash = table->set[index].hash;
	tmp->key = table->set[index].key;
	tmp->data = table->set[index].data;
	tmp->next = table->set[index].next;

	table->set[index].hash = hash;
	table->set[index].key = key;
	table->set[index].data = data;
	table->set[index].next = tmp;

	return;
}


static void insert_at(hash_table *table, size_t hash, void *key, void *data){
	size_t index = hash % table->tSize;
	if(table->set[index].key != NULL)
		shiftSet(table, index, hash, key, data);
	else{
		table->set[index].hash = hash;
		table->set[index].key = key;
		table->set[index].data = data;
	}

	return;
}


void insertHashSet(hash_table *table, void *user_key, void *data){
	// Grow table if at 75% cap.
	if(table->nElem >= table->tSize*.75)
		growTable(table);

	// copy key
	void *key = calloc(1, table->sizeof_key(user_key));
	table->cpykey(&key, user_key);

	// Hash key
	size_t hash = table->hash(key, table->sizeof_key(key));

	// Insert set into table
	insert_at(table, hash, key, data);
	table->nElem++;

	return;
}

void growTable(hash_table *table){
	// printf("The table needs to grow.\n");
	table->tSize *= 2;
	bucket *old = table->set;
	table->set = calloc(table->tSize, sizeof(bucket));
	for(int i=0; i<table->tSize/2; i++){
		bucket *tmp = old+i;
		do{
			if(tmp->key != NULL){
				insert_at(table, tmp->hash, tmp->key, tmp->data);
			}
			tmp = tmp->next;
		}while(tmp != NULL);
		tmp = old[i].next;
		while(tmp != NULL){
			bucket *tmp_next = tmp->next;
			free(tmp);
			tmp = tmp_next;
		}

	}
	free(old);
	old = NULL;

	return;
}

bucket* find_nth_hashItem(hash_table *table, int n){
	if(table->nElem < n){
		fprintf(stderr, "Table contains less than %d elements\n", n);
		return NULL;
	}
	bucket *target = NULL;
	for(int i=0; n>0 && i<table->tSize; i++){
		target = table->set+i;
		while(target != NULL){
			if(target->key != NULL)
				if(--n == 0)
					break;
			target = target->next;
		}
	}
	return target;
}

bucket* find_key(hash_table *table, void *key){
	size_t hash = table->hash(key, table->sizeof_key(key));
	bucket *target = table->set + hash % table->tSize;
	while(target != NULL){
		if(table->cmp_key(target->key, key))
			target = target->next;
		else
			break;
	}
	return target;

}



int freeSet(hash_table *table, bucket *set){
	if(set->key == NULL)
		return 0;

	table->nElem -= 1;
	free(set->key);
	table->free_data(set->data);
	if(set->next == NULL){
		set->key = NULL;
		set->data = NULL;
		return 0;
	}
	else{
		set->key = set->next->key;
		set->data = set->next->data;
		bucket *tmp = set->next->next;
		free(set->next);
		set->next = tmp;
		return 1;
	}
}

void freeTable(hash_table **table){
	for(int i=0; i<(*table)->tSize; i++)
		while(freeSet((*table), (*table)->set+i));
	free((*table)->set);
	(*table)->set = NULL;
	free(*table);
	*table = NULL;
}
