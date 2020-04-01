#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "list.h"
#include "que.h"
#include "stack.h"
#include "graph.h"
#include "util.h"
#include "sort.h"

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


/**
 * Local Function: Updates the meta data of any unvisited adjacent 
 * nodes and updates the curr_node to the unvisited adjacent node 
 * with the smallest weight.
 */
static void updateMeta(graph_t *graph, dijk_t *meta, dijk_t *curr_node);


/**
 * Local Function: Prints the contents of the dijk structure.
 */
static void ptDijk(dijk_t meta);


/**
 * Compare the weight of two nodes.
 */
int cmp_weight(void*, void*);


/**
 * Local Function: Updates the meta data of any unvisited adjacent 
 * nodes and updates the curr_node to the unvisited adjacent node 
 * with the smallest weight.
 */
static void updateMeta(graph_t *graph, dijk_t *meta, dijk_t *curr_node){
	
	// Hold next meta to update
	dijk_t *next = NULL;

	// Hold next curr_node and set weight to infinity
	dijk_t *tmp_next = curr_node;
	tmp_next->weight = GRAPH_SIZE + MAX_WEIGHT + 1;

	// Get list of adjacent nodes and loop until NULL
	adjNode_t *curr_adj = graph->adjArr[curr_node->name].list;
	while(curr_adj != NULL){

		// Skip visited nodes
		while(meta[curr_adj->child.name].visited)
			curr_adj = curr_adj->next;
		if(curr_adj == NULL)
			break;

		// Set next
		next = &meta[curr_adj->child.name];

		// Update next if needed
		if(next->weight > curr_node->weight + curr_adj->weight){
			next->weight = curr_node->weight + curr_adj->weight;
			next->lastNode = curr_node;
		}

		// Update tmp_next
		if(next->weight < tmp_next->weight)
			tmp_next = next;

		// Update curr_adj
		curr_adj = curr_adj->next;
	}
	
	// Set curr_node to visited and update
	curr_node->visited = 1;
	// curr_node = tmp_next;

	// CLOSE OUT
	return;
}



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


int cmp_weight(void *var1, void *var2){
	int *num1 = &(*(dijk_t*)var1).weight;
	int *num2 = &(*(dijk_t*)var2).weight;
	return cmp_int(num1, num2);
}

void ptDijk_ptr(void *var){
	return ptDijk(*(dijk_t*)var);
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
	node_t *pQue = mkList(GRAPH_SIZE, DOUBLY);
	node_t *curr = pQue;
	dijk_t *meta = malloc(sizeof(dijk_t) * GRAPH_SIZE);
	for(int i=0; curr != NULL && i<GRAPH_SIZE; curr = curr->next, i++){
		meta[i].name = i;
		meta[i].visited = 0;
		meta[i].lastNode = NULL;
		meta[i].weight = GRAPH_SIZE * MAX_WEIGHT + 1;
		curr->data = meta;
	}


	// Define start and end nodes
	int start = 0;
	int end = 5;

	meta[start].weight = 0;
	meta[start].lastNode = &meta[start];
	
	ptList(pQue, ptDijk_ptr); printf("NULL\n\n");
	pQue = sort_bubble_list(pQue, cmp_weight);
	ptList(pQue, ptDijk_ptr); printf("NULL\n\n");
	

	dijk_t *curr_meta = (dijk_t*)pQue->data; 
	updateMeta(graph, meta, curr_meta);
	ptDijk(meta[0]);
	ptDijk(meta[1]);
	ptDijk(meta[2]);
	ptDijk(meta[4]);



	// Clean up
	// Free list
	while(pQue != NULL){
		node_t *tmp;
		tmp = pQue->next;
		free(pQue);
		pQue = NULL;
		pQue = tmp;
	}

	// Free meta
	free(meta);

	// Free graph
	freeGraph(graph);
	
	return 0;
}