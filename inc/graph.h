#ifndef GRAPH_H_CUSHMAN
#define GRAPH_H_CUSHMAN

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "que.h"
#include "stack.h"

#define DEPTH (1)
#define BREADTH (2)

// Represents a node in the graph
// One node for each element in the graph
typedef struct graphNode{
    int name;
    void *data;
}graphNode_t;


// Represent adjacent nodes of the graph
// Two adjNodes creat an edge
typedef struct adjNode{
    struct graphNode parent;
    struct graphNode child;
    int weight;
    struct adjNode *next;
}adjNode_t;


// Represent list of adjacent nodes
typedef struct adjList{
    struct adjNode *list;
}adjList_t;


// Represents the graph
typedef struct graph{
    int size;
    int max_weight;
    struct adjList *adjArr;
    struct graphNode *nodeArr;
}graph_t;


/**
 * Creates a new graph with num number of nodes.
 */
graph_t* newGraph(int num);


/**
 * Adds adjNodes to create an Edge within the graph.
 */
void addEdge(graph_t* graph, int src, int dest, int weight);


/**
 * Prints a list of adjNodes(with weight) for each node in the graph and gives
 * the node's value.
 */
void ptGraph(graph_t *graph, void (*print_ptr)(void*));


/**
 * Finds a node in the graph with the value specifed by the user.
 */
graphNode_t* findGraphNode(graph_t *graph, 
                            int method, 
                            int start,
                            void *value, 
                            int (*cmp_ptr)(void*,void*));


/**
 * Finds an edge in the graph should one exist between two specified nodes
 */
void findEdge_by_parentChild(graph_t *graph, adjNode_t **edge,
    graphNode_t parent, graphNode_t child);


/**
 * Finds an edge in the graph should one exist that contains the weight 
 * specified.
 */
void findEdge_by_weight(graph_t *graph, adjNode_t **edge, int weight);                  


/**
 * Frees the adjNodes that create an Edge in the graph. Returns an array of the 
 * two adjNodes that comprise the edge. Parent function assumes ownership of
 * this list.
 */
void freeEdge(graph_t **graph, adjNode_t *parent, adjNode_t *child);


/**
 * Frees a node within the graph including any edges connected to it.
 */
void freeGraphNode(graph_t *graph, int name);


/**
 * Frees the entire graph includeing nodes, edges, and metadata.
 */
void freeGraph(graph_t *graph);

#endif /* GRAPH_H_CUSHMAN */