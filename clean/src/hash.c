#include "hash.h"

struct bucket{
	size_t hash;
	void *key;
	void *data;
	struct bucket *next;
};

struct hashTable{
	struct bucket *set;
	size_t tSize;
	size_t nElem;
	size_t (*hash)(void*);
	void (*keycpy)(void**, void*);
	int (*keycmp)(void*, void*);
	void (*datafree)(void*);
};



/**
 * Local Function for inserting buckets where a bucket exists.
 */
static void shiftSet(hash_table *table, size_t index, 
						size_t hash, void *key, void *data);


// PRIVATE FUNCTIONS

static void shiftSet(hash_table *table, size_t index, 
						size_t hash, void *key, void *data){
	// bucket *tmp = calloc(1, sizeof(bucket));

	bucket *tmp = table->set+index;

	while(tmp != NULL){
		if(table->keycmp(tmp->key, key) == 0){
			// Key is alread in table, update data
			table->datafree(tmp->data);
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


/**
 * Inserts the key and data into the hash table based on the the size of the 
 * table and the hash passed to the function.
 */
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


static void growTable(hash_table *table){
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

static bucket* find_nth(hash_table *table, void *nth){
	int n = *(int*)nth;
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

static bucket* find_key(hash_table *table, void *key){
	size_t hash = table->hash(key);
	bucket *target = table->set + hash % table->tSize;
	while(target != NULL){
		if(table->keycmp(target->key, key))
			target = target->next;
		else
			break;
	}
	return target;
}


static int freeSet(hash_table *table, bucket *set){
	if(set->key == NULL)
		return 0;

	table->nElem -= 1;
	free(set->key);
	table->datafree(set->data);
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

static int delete_all(hash_table *table){
	for(int i=0; i<table->tSize; i++)
		while(freeSet(table, table->set+i));
	free(table->set);
	table->set = NULL;
	return 1;
}


static void print_set_util(bucket set, int level, 
							void (*print_data)(void *data)){
	if(set.key == NULL){
		for(int i=0; i<level; i++)
			printf("\t");
		printf("EMPTY\n");
	}
	else{
		for(int i=0; i<level; i++)
			printf("\t");
		(*print_data)(set.data);
		printf("\n");
		if(set.next != NULL){
			for(int i=0; i<level; i++)
				printf("\t");
			printf("Next :\n");
			print_set_util(*(set.next), level+1, print_data);
		}
	}
	return;
}


static void print_set(bucket set, void (*print_data)(void *data)){
	print_set_util(set, 1, print_data);
	printf("\n");
	return;
}


// PUBLIC FUNCTIONS


hash_table* hashTable_create(unsigned long (*hash)(void *key), 
							void (*keycpy)(void **dest, void *src), 
							int (*keycmp)(void *key1, void *key2),
							void (*datafree)(void *data)){
	hash_table *table = calloc(1, sizeof(hash_table));
	table->tSize = 16;
	table->set = calloc(table->tSize, sizeof(bucket));
	table->nElem = 0;
	table->hash = hash;
	table->keycpy = keycpy;
	table->keycmp = keycmp;
	table->datafree = datafree;
	return table;
}


void hashTable_insert(hash_table *table, void *user_key, void *data, 
						size_t size){
	// Grow table if at 75% cap.
	if(table->nElem >= table->tSize*.75)
		growTable(table);

	// copy key
	void *key;
	table->keycpy(&key, user_key);

	// Hash key
	size_t hash = table->hash(key);

	// Insert set into table
	insert_at(table, hash, key, data);
	table->nElem++;

	return;
}

void* hashTable_find(hash_table *table, int nth_mode, void *key){
	if(nth_mode == TRUE)
		return find_nth(table, key)->data;
	else
		return find_key(table, key)->data;
}

int hashTable_delete(hash_table *table, int nth_mode, void *key){
	if(nth_mode == TRUE){
		return freeSet(table, find_nth(table, key));
	}
	else if(key != NULL){
		return freeSet(table, find_key(table, key));
	}
	else
		return delete_all(table);
}

void hashTable_destroy(hash_table **table){
	delete_all(*table);
	free(*table);
	*table = NULL;
	return;
}

size_t hashTable_size(hash_table *table){
	return table->nElem;
}

void hashTable_print(hash_table *table, void (*print_data)(void *data)){
	for(int n = 0; n < table->tSize; n++){
		print_set(table->set[n], print_data);
	}
	return;
}