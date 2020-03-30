#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "list.h"
#include "que.h"
#include "stack.h"
#include "graph.h"

#define GRAPH_SIZE (7)
#define MAX_WEIGHT (20)


/**
 * Structure for Dijkstra's Algorithm
 * 
 * Contents:
 * int name;
 * uint8_t visited;
 * int lastNode;
 * int weight; 
 */
typedef struct dijk{
	int name;
	uint8_t visited;
	struct dijk *lastNode;
	int weight;
}dijk_t;


static dijk_t* getNextNode(graph_t *graph, dijk_t *meta, dijk_t *curr_node);
static void ptDijk(dijk_t meta);


/**
 * Finds the next unvisited node with the smallest weight.
 */
static dijk_t* getNextNode(graph_t *graph, dijk_t *meta, dijk_t *curr_node){
	
	dijk_t *next = NULL;
	adjNode_t *curr_adj = graph->adjArr[curr_node->name].list;


	while(curr_adj != NULL){
		ptDijk(meta[curr_adj->child.name]);
		while(meta[curr_adj->child.name].visited)
			curr_adj = curr_adj->next;
		if(curr_adj == NULL)
			break;
		if(next != NULL){
			printf("next weight %d\n", next->weight);
			printf("curr_adj weight %d\n", curr_adj->weight);
		}
		if(next == NULL)
			next = &meta[curr_adj->child.name];
		else if(next->weight > curr_adj->weight)
			next = &meta[curr_adj->child.name];
		curr_adj = curr_adj->next;
	}
	
	printf("\n");
	if(next == NULL)
		return NULL;
	else
		return next;
}


/**
 * Local Function: Prints the contents of the dijk structure.
 */
static void ptDijk(dijk_t meta){
	printf("meta name: %d\n", meta.name);
	printf("meta visited: %d\n", meta.visited);
	printf("meta lastNode: ");
	if(meta.lastNode == NULL)
		printf("NULL \n");
	else
		printf("%d \n", meta.lastNode->name);
	printf("meta weight: %d\n\n", meta.weight);
	return;
}


int main(void){

	graph_t *graph = newGraph(GRAPH_SIZE);
	addEdge(graph, 0, 1, 4);
	addEdge(graph, 0, 2, 3);
	addEdge(graph, 0, 4, 7);
	addEdge(graph, 1, 3, 5);
	addEdge(graph, 1, 2, 6);
	addEdge(graph, 2, 3, 11);
	addEdge(graph, 2, 4, 8);
	addEdge(graph, 3, 4, 2);
	addEdge(graph, 3, 5, 2);
	addEdge(graph, 3, 6, 10);
	addEdge(graph, 4, 6, 5);
	addEdge(graph, 5, 6, 3);

	////////////////////////////
	//	THE GRAPH			  //
	//	(NODE)				  //
	//	[WEIGHT]			  //
	//						  //
	//	(1)--[5]-(3)-[2]-(5)  //
	//	 | \     /|\      |   //
	//   | [6][11]| \     |   //
	//	 |   \ /  |  \    |   //
	//	[4]  (2) [2][10] [3]  //
	//	 |   / \  |    \  |   //
	//	 | [3] [8]|     \ |   //
	//	 | /     \|      \|   //
	//  (0)--[7]-(4)-[5]-(6)  //
	//						  //
	////////////////////////////

	ptGraph(graph, print_int);


	// Define list of all nodes
	node_t *path = mkList(GRAPH_SIZE, DOUBLY);
	node_t *curr = path;
	dijk_t *meta = malloc(sizeof(dijk_t) * GRAPH_SIZE);
	for(int i=0; curr != NULL && i<GRAPH_SIZE; curr = curr->next, i++){
		meta[i].name = i;
		meta[i].visited = 0;
		meta[i].lastNode = NULL;
		meta[i].weight = GRAPH_SIZE * MAX_WEIGHT + 1;
		curr->data = meta;
	}


	// Define start and end nodes
	dijk_t *start = &meta[0];
	dijk_t *end = &meta[5];
	// ptDijk(*start);
	// ptDijk(*end);


	dijk_t *curr_meta = start; 
	dijk_t *next_meta = getNextNode(graph, meta, curr_meta);
	printf("next node: %d\n", next_meta->name);
	
	



	// Clean up
	// Free list
	while(path != NULL){
		node_t *tmp;
		tmp = path->next;
		free(path);
		path = NULL;
		path = tmp;
	}

	// Free meta
	free(meta);

	// Free graph
	freeGraph(graph);
	
	return 0;
}