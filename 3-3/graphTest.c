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
    // graph = fillGraph(graph);
    int data[5] = {3,2,4,2,0};
    graph->nodeArr[0].data = data+0;
    graph->nodeArr[1].data = data+1;
    graph->nodeArr[2].data = data+2;
    graph->nodeArr[3].data = data+3;
    graph->nodeArr[4].data = data+4;

    addEdge(graph, 0, 2, 1);
    addEdge(graph, 0, 4, 4);
    addEdge(graph, 1, 4, 2);
    addEdge(graph, 2, 3, 3);
    addEdge(graph, 2, 4, 2);

    // Dynamically connect nodes with edges
    // Iterate through each node other than the last
    // for(int curr=0; curr<SIZE_GRAPH; curr++){        
    //     do{
    //         // Potential edge can connect to nodes with
    //         // names greater than the current node
    //         int adj = curr+1;
    //         int size = SIZE_GRAPH;
    //         // Check that final node contains edges
    //         if(curr == SIZE_GRAPH-1 && graph->adjArr[curr].list == NULL){
    //             adj = 0;
    //             size--;
    //         }
    //         for(; adj<size; adj++)
    //             // 50% chance of edge connecting between curr and adj
    //             if(rand()%2)
    //                 // add the edge
    //                 addEdge(graph, curr, adj, rand()%graph->max_weight+1);
    //     // Check that at least 1 edge is on the node before moving on
    //     }while(graph->adjArr[curr].list == NULL);
    // }
    printf("\nPRINT INITAL GRAPH...");
    ptGraph(graph, print_int);
    
    
    // Find node within an existing graph
    int num = 2;
    int *ptr = &num;
    graphNode_t target;
    target.name = -1;
    target.data = NULL;
    printf("FIND NODE WITH VALUE %d...\n", num);
    findGraphNode(graph, &target, DEPTH, 0, ptr, cmp_int);
    if(target.name == -1)
        printf("Target node not found.\n\n");
    else
        printf("Value found in node %d\n\n", target.name);
    

    // Print Graph
    // printf("\n\nPrinting Graph...\n");
    // ptGraph(graph, print_int);

    // Find an edge within an existing graph
    // Getting things setup
    adjNode_t *edge = NULL;
    num = 2;
    int num2 = 3;
    int *ptr2 = &num2;


    // Find edge by weight
    printf("\n\nFind edge by weight of %d\n", num);
    edge = findEdge_by_weight(graph, num);
    if(edge == NULL)
        printf("There is not an edge between the specified nodes.\n");
    else
        printf("An edge with weight %d was found between nodes %d and %d.\n",
            edge->weight, edge->parent.name, edge->child.name);
    printf("\n\n");

    // Find edge by parent-child relation
    printf("Find edge by parent-child relationship.");
    graphNode_t target2;
    target2.name = -1;
    target2.data = NULL;
    findGraphNode(graph, &target, DEPTH, 0, ptr, cmp_int);
    printf(" Parent %d", target.name);
    findGraphNode(graph, &target2, DEPTH, 0, ptr2, cmp_int);
    printf(" Child %d\n", target2.name);
    // ptGraph(graph, print_int);
    if(target.name == -1 || target2.name == -1){
        printf("One or more target nodes were not found.");
        printf("Attempt to find edge terminated.\n");
    }
    else{
        edge = findEdge_by_parentChild(graph, target, target2);
        if(edge == NULL){
            printf("There is not an edge between the specified nodes.\n");
            printf("\nAdding edge between nodes %d and %d\n",
                target.name, target2.name);
            addEdge(graph, target.name, target2.name, 4);
            ptGraph(graph, print_int);

            edge = findEdge_by_parentChild(graph, target, target2);
            if(edge == NULL)
                printf("There is not an edge between the specified nodes.\n");
            else
                printf("An edge with weight %d was found between nodes %d and %d.\n",
                    edge->weight, edge->parent.name, edge->child.name);
        }
        else
            printf("An edge with weight %d was found between nodes %d and %d.\n",
                edge->weight, edge->parent.name, edge->child.name);
    }
    printf("\n\n");

    
   
    // Clean Up and Exit


    // Remove a single edge from the graph
    // printf("Remove an edge from graph...\n");
    // freeEdge(&graph, edge, edge->next);
    // ptGraph(graph, print_int);


    printf("\n\nCLEAN UP...\n\n");
    freeGraph(graph);

    return 0;
}