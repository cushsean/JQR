#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define THREADS (3)

// Use of mutex with semaphore.h syntex is directly below each pthread call.
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// sem_t mutex;

typedef struct meta{
	char *line;
	char *word;
	unsigned int *count;
}meta;

/**
 * A function for finding the number of times a specified word appears within 
 * a section of text.
 */
void* findWord(void *group){
	
	char *line = ((meta*)group)->line;
	char *word = ((meta*)group)->word;
	char *start = line;
	int local_count = 0;
	
	while(1==1){
		line = strstr(line, word);
		if(line == NULL)
			break;
		if(*(line) == '\n')
			break;
		int offset = strlen(word);
		if(line != start){
			if(*(line-1) != ' '){
				line += offset;
				continue;
			}
		}
		if( (*(line+offset) >= 'A' && *(line+offset) <= 'Z') || 
			(*(line+offset) >= 'a' && *(line+offset) <= 'z'))
		{	
			line += offset;
			continue;
		}

		local_count++;

		line += offset;
		continue;
	}

	if(local_count > 0){
		// LOCK
		pthread_mutex_lock(&mutex);
		// sem_wait(&mutex);

		*((meta*)group)->count += local_count;

		// UNLOCK
		pthread_mutex_unlock(&mutex);
		// sem_post(&mutex);
	}
	free(start);
	start = NULL;
	free(group);
	group = NULL;
	return NULL;
}


int main(int argc, char **argv){
	if(argc != 3){
		fprintf(stderr, "SYNOPSIS: [word]\n");
		return EXIT_FAILURE;
	}

	// meta *txt = calloc(1, sizeof(meta));
	// txt->original = 1;

	char *fileName = argv[1];
	
	FILE *txtFile;
	txtFile = fopen(fileName, "r");
	if(txtFile == NULL){
		fprintf(stderr, "Failed to open file stream\n");
		return EXIT_FAILURE;
	}

	pthread_t *thread = calloc(THREADS, sizeof(pthread_t));

	// sem_init(&mutex, 0, 1);

	
	unsigned int *count = calloc(1, sizeof(unsigned int));
	

	while(feof(txtFile) == 0){
		int t;
		for(t = 0; t < THREADS && feof(txtFile) == 0; t++){
			// Create struct
			meta *txt = calloc(1, sizeof(meta));
			txt->word = argv[2];
			int lineSize = 128;
			txt->line = calloc(lineSize, sizeof(char));

			// LOCK
			pthread_mutex_lock(&mutex);
			// sem_wait(&mutex);

			txt->count = count;
			// Look at r/w locks

			// UNLOCK
			pthread_mutex_unlock(&mutex);
			// sem_post(&mutex);

			// Get a line of the script.
			int i = 0;
			for(; (txt->line[i] = getc(txtFile)) != '\n' && 
					txt->line[i] != EOF; i++){
				if(i+1 == lineSize){
					lineSize += 128;
					txt->line = realloc(txt->line, lineSize);
				}
			}
			txt->line[++i] = 0;

			// findWord(txt);
			pthread_create(&thread[t], NULL, findWord, txt);
		}
		for(t = 0; t < THREADS; t++){
			pthread_join(thread[t], NULL);
		}
	}

	printf("\n\n%s:%d\n", argv[2], *count);

	// sem_destroy(&mutex);
	free(count);
	free(thread);
	fclose(txtFile);

	return EXIT_SUCCESS;
}