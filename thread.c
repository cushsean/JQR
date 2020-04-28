#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define THREADS (2)

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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
	
	// LOCK
	pthread_mutex_lock(&mutex);

	char *line = calloc(1, strlen(((meta*)group)->line));
	// printf("COW\n");
	memcpy(line, ((meta*)group)->line, strlen(((meta*)group)->line));
	// printf("MOO\n");

	char *word = calloc(128, sizeof(char));
	// printf("CAT\n");
	memcpy(word, ((meta*)group)->word, strlen(((meta*)group)->word));
	// printf("MEOW\n");

	// UNLOCK
	pthread_mutex_unlock(&mutex);
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

		*((meta*)group)->count += local_count;

		// UNLOCK
		pthread_mutex_unlock(&mutex);
	}


	// line = start;
	free(line);
	free(word);
	return NULL;
}


int main(int argc, char **argv){
	if(argc != 3){
		fprintf(stderr, "SYNOPSIS: [word]\n");
		return EXIT_FAILURE;
	}

	meta *txt = calloc(1, sizeof(meta));
	// txt->original = 1;

	char *fileName = argv[1];
	txt->word = argv[2];

	FILE *txtFile;
	txtFile = fopen(fileName, "r");
	if(txtFile == NULL){
		fprintf(stderr, "Failed to open file stream\n");
		return EXIT_FAILURE;
	}

	pthread_t *thread = calloc(THREADS, sizeof(pthread_t));

	int lineSize = 128;
	txt->line = calloc(lineSize, sizeof(char));
	txt->count = calloc(1, sizeof(unsigned int));

	while(feof(txtFile) == 0){
		int t;
		for(t = 0; t < THREADS && feof(txtFile) == 0; t++){
			// Get a line of the script.
			int i = 0;
			usleep(60);
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

	printf("\n\n%s:%d\n", txt->word, *(txt->count));

	free(txt->count);
	free(txt->line);
	free(txt);

	return EXIT_SUCCESS;
}