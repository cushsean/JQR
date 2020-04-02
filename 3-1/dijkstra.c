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

#define GRAPH_SIZE (12)
#define MAX_WEIGHT (10)


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
static void updateMeta(graph_t *graph, dijk_t *meta, node_t **pQue);


/**
 * Local Function: Prints the contents of the dijk structure.
 */
static void ptDijk(dijk_t meta);


/**
 * Compare the weight of two nodes.
 */
int cmp_weight(void*, void*);


/**
 * Wrapper for printing dijk_t as void*
 */
void ptDijk_ptr(void *var);


/**
 * Local Function: Updates the meta data of any unvisited adjacent 
 * nodes and updates the curr_node to the unvisited adjacent node 
 * with the smallest weight.
 */
static void updateMeta(graph_t *graph, dijk_t *meta, node_t **pQue){
	
	// Hold next meta to update
	dijk_t *next = NULL;

	dijk_t *curr_node = (dijk_t*)(*pQue)->data;

	// Get list of adjacent nodes and loop until NULL
	adjNode_t *curr_adj = graph->adjArr[curr_node->name].list;
	while(curr_adj != NULL){

		// Skip visited nodes
		while(meta[curr_adj->child.name].visited){
			curr_adj = curr_adj->next;
			if(curr_adj == NULL)
				break;
		}
		if(curr_adj == NULL)
			break;

		// Set next
		next = &meta[curr_adj->child.name];

		// Update next if needed
		if(next->weight > curr_node->weight + curr_adj->weight){
			next->weight = curr_node->weight + curr_adj->weight;
			next->lastNode = curr_node;
		}

		// Update curr_adj
		curr_adj = curr_adj->next;
	}
	
	// Set curr_node to visited and update
	curr_node->visited = 1;

	// Clean up
	// ptList(*pQue, ptDijk_ptr); printf("NULL\n\n");
	if((*pQue)->next != NULL){
		*pQue = (*pQue)->next;
		free((*pQue)->prev);
		(*pQue)->prev = NULL;
		*pQue = sort_bubble_list(*pQue, cmp_weight);
	}
	else{
		free(*pQue);
		*pQue = NULL;
	}


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
	srand(time(NULL));
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

	/////////////////////////////
	//	THE GRAPH			  //
	//	(NODE)				  //
	//	[WEIGHT]			  //
	//						  //
	//	(1)--[5]-(3)-[2]-(5)  //
	//	 | \     /|\      |   //
	//    | [6][11]| \     |   //
	//	 |   \ /  |  \    |   //
	//	[4]  (2) [2][10] [3]  //
	//	 |   / \  |    \  |   //
	//	 | [3] [8]|     \ |   //
	//	 | /     \|      \|   //
	//   (0)--[7]-(4)-[5]-(6)  //
	//						  //
	/////////////////////////////
	

	// Dynamically connect nodes with edges
    // Iterate through each node other than the last
    // for(int curr=0; curr<GRAPH_SIZE; curr++){        
    //     do{
    //         // Potential edge can connect to nodes with
    //         // names greater than the current node
    //         int adj = curr+1;
    //         int size = GRAPH_SIZE;
    //         // Check that final node contains edges
    //         if(curr == GRAPH_SIZE-1 && graph->adjArr[curr].list == NULL){
    //             adj = 0;
    //             size--;
    //         }
    //         for(; adj<size; adj++)
    //             // 50% chance of edge connecting between curr and adj
    //             if(rand()%100/75)
    //                 // add the edge
    //                 addEdge(graph, curr, adj, rand()%MAX_WEIGHT+1);
    //     // Check that at least 1 edge is on the node before moving on
    //     }while(graph->adjArr[curr].list == NULL);
    // }
	

	// Print Graph
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
		curr->data = &meta[i];
	}


	// Define start and end nodes
	int start = rand()%GRAPH_SIZE;
	int end;
	do{
		end = rand()%GRAPH_SIZE;
	}while(end == start);

	
	// Print START and END
	printf("START: %d\n", start);
	printf("END: %d\n\n", end);


	// Set start meta
	meta[start].weight = 0;
	meta[start].lastNode = &meta[start];
	pQue = sort_bubble_list(pQue, cmp_weight);


	// Calculate shortest paths
	for(int i=0; i<GRAPH_SIZE; i++)
		updateMeta(graph, meta, &pQue);


	// Get shortest path from meta
	printf("Shortest path from START to END\n");
	int path[GRAPH_SIZE];
	int i = 0;
	int j = end;
	while(j != start){
		path[i++] = meta[j].name;
		j = meta[j].lastNode->name;
	}
	printf("S");
	for(--i; i>=0; i--){
		printf(" -> ");
		if(path[i] == end)
			printf("E");
		else
			printf("%d", path[i]);
	}
	printf("\nWeight of path: %d\n\n", meta[end].weight);


	// Print table of shortest paths
	printf("Table of shortest paths...\n\n");

	printf("\t       | SHORTEST | PREVIOUS\n");
	printf("\tVERTEX | DISTANCE |  VERTEX \n");
	printf("\t       |  FROM S  |         \n");
	printf("\t----------------------------\n");
	for(int i=0; i<GRAPH_SIZE; i++){
		printf("\t");
		
		// Vertex
		if(i == start)
			printf("   S   ");
		else if(i == end)
			printf("   E   ");
		else{
			for(int j=0; j<3-i/10; j++)
				printf(" ");
			printf("%d   ", i);
		}
		printf("|");

		// Shortest Distance
		if(meta[i].weight/10 == 0)
			printf("     %d    |", meta[i].weight);
		else if(meta[i].weight/100 == 0)
			printf("    %d    |", meta[i].weight);
		else
			printf("    %d   |", meta[i].weight);

		// Previous Vertex
		if(meta[i].name == start)
		printf("         ");
		else if(meta[i].lastNode->name == start)
			printf("    S    ");
		else if(meta[i].lastNode->name == end)
			printf("    E    ");
		else{
			for(int j=0; j<4-meta[i].lastNode->name/10; j++)
				printf(" ");
			printf("%d    ", meta[i].lastNode->name);
		}
		if(i != GRAPH_SIZE-1)
			printf("\n\t----------------------------\n");
		else
			printf("\n\n");
	}


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