#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "graph.h"
#include "stack.h"
#include "util.h"

#define SIZE_GRAPH (5)

static graph_t* fillGraph(graph_t *graph){
    srand(time(NULL));
    for(int i = 0; i < SIZE_GRAPH; i++){
        int *num = malloc(sizeof(int));
        *num = rand()%5;
        graph->nodeArr[i].data = num;
    }
    return graph;
}

int main(void){
    srand(time(NULL));
    graph_t* graph = newGraph(SIZE_GRAPH);
    graph->max_weight = 5;

    // Fill the graph nodes with random numbers
    graph = fillGraph(graph);

    // Dynamically connect nodes with edges
    // Iterate through each node other than the last
    for(int curr=0; curr<SIZE_GRAPH; curr++){        
        do{
            // Potential edge can connect to nodes with
            // names greater than the current node
            int adj = curr+1;
            int size = SIZE_GRAPH;
            // Check that final node contains edges
            if(curr == SIZE_GRAPH-1 && graph->adjArr[curr].list == NULL){
                adj = 0;
                size--;
            }
            for(; adj<size; adj++)
                // 50% chance of edge connecting between curr and adj
                if(rand()%2)
                    // add the edge
                    addEdge(graph, curr, adj, rand()%graph->max_weight+1);
        // Check that at least 1 edge is on the node before moving on
        }while(graph->adjArr[curr].list == NULL);
    }
    printf("\nPRINT INITAL GRAPH...\n");
    ptGraph(graph, print_int);


    // FIND NODE WITHIN GRAPH
    int num = 2;
    int *ptr = &num;
    printf("\nFIND NODE WITH VALUE %d...\n\n", num);
    graphNode_t *target = findGraphNode(graph, DEPTH, 0, ptr, cmp_int);
    if(target == NULL)
        printf("Value %d not found\n", num);
    else
        printf("Value %d found in node %d\n", num, target->name);
    printf("\n");

    printf("\n\nCLEAN UP...\n\n");
    freeGraph(graph);

    return 0;
}