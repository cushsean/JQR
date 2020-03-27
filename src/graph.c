#include "graph.h"


/**
 * Local function: Creates a new adjNode
 */
static adjNode_t* newAdjNode(int name, 
                                int weight, 
                                graphNode_t child, 
                                graphNode_t parent ){
    adjNode_t* new_node = malloc(sizeof(adjNode_t));
    new_node->weight = weight;
    new_node->next = NULL;
    new_node->parent = parent;
    new_node->child = child;
    return new_node;
}

graph_t* newGraph(int num){
    graph_t* graph = malloc(sizeof(graph_t));
    graph->size = num;

    // Create adjList for each node in graph
    graph->adjArr = malloc(num * sizeof(adjList_t));

    // Create a list of nodes in the graph
    graph->nodeArr = malloc(num * sizeof(graphNode_t));

    // Initialize adjLists to NULL
    // and name nodes will NULL data
    for(int i=0; i<num; i++){
        graph->adjArr[i].list = NULL;
        graph->nodeArr[i].name = i;
        graph->nodeArr[i].data = NULL;
    }
    return graph;
}

void addEdge(graph_t *graph, int src, int dest, int weight){ 
    // Add an edge from src to dest. A new node is 
    // added to the adjacency list of src. The node
    // is added at the beginning
    adjNode_t *new_node 
        = newAdjNode(   dest, 
                        weight, 
                        graph->nodeArr[dest], 
                        graph->nodeArr[src] );
    new_node->next = graph->adjArr[src].list;
    graph->adjArr[src].list = new_node;

    // Add an edge from dest to src also
    new_node = newAdjNode(  src, 
                            weight, 
                            graph->nodeArr[src], 
                            graph->nodeArr[dest] );
    new_node->weight = weight;
    // new_node->node = graph->nodeArr[src];
    new_node->next = graph->adjArr[dest].list;
    graph->adjArr[dest].list = new_node;

    return;
}


void ptGraph(graph_t *graph, void (*print_ptr)(void*)){
    for(int i=0; i<graph->size; i++){
        adjNode_t *curr_adj = graph->adjArr[i].list;
        graphNode_t curr_node = graph->nodeArr[i];
        printf("\nNode %d contains value ",  curr_node.name);
        if(curr_node.data != NULL)
            (*print_ptr)(curr_node.data);
        else
            printf("NULL");
        printf(" and is adj to:\n\t");
        while(1==1){
            printf("%d(%d)", curr_adj->child.name, curr_adj->weight);
            curr_adj = curr_adj->next;
            if(curr_adj)
                printf(", ");
            else
                break;
        }
        printf("\n");
    }
    printf("\n\n");
    return;
}


/**
 * Local Function: Prints the array of visited nodes.
 */
static void ptVisited(uint8_t *list, int size){
    printf("Visited Nodes...\n\t");
    for(int i=0; i<size; i++){
        printf("%d(%d) -> ", i, list[i]);
    }
    printf("\n");
    return;
}


/**
 * Local function: Identifies and returns the graphNode_t represented by the 
 * value at the top of the stack.
 */
static graphNode_t nodeFromStack(node_t *stack, graph_t *graph){
    return graph->nodeArr[*(int*)(stack->data)];
}


graphNode_t* findGraphNode(graph_t *graph, 
                            int method, 
                            int start,
                            void *value, 
                            int (*cmp_ptr)(void*,void*)){
    
    // Define function variables
    graphNode_t next_node = graph->nodeArr[start];
    uint8_t *visited = malloc(graph->size);
    graphNode_t *target = NULL;


    // ptVisited(visited, graph->size);


    // Inital check
    if((*cmp_ptr)(next_node.data, value) == 0)
        // Target found
        target = &next_node;

    // DEPTH METHOD
    else if(method == DEPTH){

        // Define stack
        node_t *stack = mkStack(1);
        stack = pop(stack);


        for(int i=0; i<graph->size; i++){
            // Declare local variables
            graphNode_t curr_node = next_node;
            adjNode_t *curr_adj = graph->adjArr[curr_node.name].list;
            int min_weight = graph->max_weight+1;


            // Set curr_node on stack and visited list
            int *nameHolder = malloc(sizeof(int));
            *nameHolder = curr_node.name;
            stack = push(stack, nameHolder);
            visited[curr_node.name] = 1;


            while(visited[next_node.name]){
                for(; curr_adj != NULL; curr_adj = curr_adj->next){
                    // Loop through all adj Nodes to curr
                    if(!visited[curr_adj->child.name])
                        if(curr_adj->weight < min_weight){
                            // update next_node
                            min_weight = curr_adj->weight;
                            next_node = curr_adj->child;
                        }
                }


                if(curr_node.name == next_node.name){
                    // No unvisited nodes found
                    stack = pop(stack);
                    if(!get_stack_size(stack)){
                        i = graph->size;
                        break;
                    }
                    curr_node = nodeFromStack(stack, graph);
                    next_node = curr_node;
                    curr_adj = graph->adjArr[curr_node.name].list;
                }
            }

            
            if((*cmp_ptr)(next_node.data, value) == 0){
                // Target node found
                target = &next_node;
                break;
            }
        }
        rmStack(stack);
    }

    // BREATH METHOD
    else{
        printf("Placeholder for BREADTH Method.\n");
        printf("Continuing using DEPTH Method.\n");
        target = findGraphNode(graph, DEPTH, start, value, cmp_ptr);

    }
    

    // CLEANUP
    free(visited);
    visited = NULL;
    
    return target;
}


/**
 * Local Function: Finds an adjNode based on the name of it's parent and child.
 */
static adjNode_t* findAdjNode(graph_t *graph, int nameParent, int nameChild){
    adjNode_t *curr = graph->adjArr[nameParent].list;
    while(curr != NULL){
        if(curr->child.name == nameChild)
            break;
        curr = curr->next;
    }
    return curr;
}


void findEdge_by_parentChild(graph_t *graph, adjNode_t **edge,
    graphNode_t parent, graphNode_t child){
    

    // Clear the incoming edge
    edge[0] = edge [1] = NULL;

    
    // Define local varibales
    adjNode_t *curr = graph->adjArr[parent.name].list;


    // Could combine the next two while loops... but not right now.

    // While true, either find the adjNode pointing to the desired child and
    // copy its contents into the edge list, or determine there is not an 
    // adjNode pointing to the desired child and break.
    while(1){
        if(curr == NULL)
            break;
        else if(curr->child.name == child.name){
            edge[0] = curr;
            break;
        }
        curr = curr->next;
    }

    if(edge[0] != NULL){
        // Redefine curr
        curr = graph->adjArr[child.name].list;


        // Similar to previous while, however, child and parent nodes have 
        // swapped and adjNode, if found, will be copied to edge[1].
        while(1){
            if(curr == NULL)
                break;
            else if(curr->child.name == parent.name){
                edge[1] = curr;
                break;
            }
            curr = curr->next;
        }
    }

    return;
}


void findEdge_by_weight(graph_t *graph, adjNode_t **edge, int weight){
    
    // Clear the incoming edge
    edge[0] = edge[1] = NULL;


    // Declare local variables
    adjNode_t *curr;


    // Loop through all adjLists until an adjNode with the specifed weight
    // is found.
    for(int i=0; i<graph->size; i++){
        curr = graph->adjArr[i].list;
        while(curr != NULL){
            if(curr->weight == weight){
                edge[0] = curr;
                i = graph->size;
                break;
            }
            curr = curr->next;
        }
    }


    // If edge[0] != NULL, loop through the child's adjNode's until either NULL
    // or one is found with the parents names. Check that the weight is correct
    // before setting it to edge[1].
    if(edge[0] != NULL){
        curr = graph->adjArr[edge[0]->child.name].list;
        while(curr != NULL){
            if(curr->child.name == edge[0]->parent.name)
                if(curr->weight == weight){
                    edge[1] = curr;
                    break;
                }
            curr = curr->next;
        }
    }

    return;
}


void freeEdge(graph_t **graph, adjNode_t *parent, adjNode_t *child){
    /**
     * This function takes the graph metadata,
     *  the parent node, and the child node.
     * This function will remove the edge between these nodes should one exist.
     * Things that need to be freed:
     *  1) adjNode of the parent
     *  2) adjNode of the child
     */
    printf("Freeing edge between %d and %d...\n", 
        parent->parent.name, child->parent.name);
    adjNode_t *rm_node = parent;
    for(int i=0; i<2; i++){
        
        if(rm_node == NULL){
            fprintf(stderr, "MEM LEAK: adjNode not freed.\n");
            continue;
        }
        if(rm_node == (*graph)->adjArr[rm_node->parent.name].list)
            (*graph)->adjArr[rm_node->parent.name].list = rm_node->next;
        else{
            adjNode_t *curr = (*graph)->adjArr[rm_node->parent.name].list;
            adjNode_t *prev = NULL;
            while(curr != rm_node){
                prev = curr;
                curr = curr->next;
            }
            prev->next = rm_node->next;
        }
        // printf("Edge elements identified beginning free.\n");
        free(rm_node);
        rm_node = child;
        // printf("rm_node Freed\n");
    }
    rm_node = NULL;
    return;
}


void freeGraphNode(graph_t *graph, int name){
    /**
     * Things that need freed when node is removed.
     *  1) Remove all edges connected to the node.
     *  2) Free the data in the node.
     *  3) Set node name to -1 to indicate that it is ready to be freed.
    */
    // fprintf(stderr, "FREEING GRAPH NODE!\n");
    graphNode_t node = graph->nodeArr[name];

    //1
    while(graph->adjArr[node.name].list != NULL){
        // printf("Attempt to free edge between ");
        // printf("%d and %d\n", graph->adjArr[node.name].list->parent.name, 
                // graph->adjArr[node.name].list->child.name);
        freeEdge(&graph, 
                    graph->adjArr[node.name].list, 
                    findAdjNode(graph, 
                                    graph->adjArr[node.name].list->child.name,
                                    graph->adjArr[node.name].list->parent.name)
                );
    }
    // 2
    // printf("Attempting to free node.data...\n");
    free(node.data);
    node.data = NULL;
    // printf("node.data has been freed.\n");
    // 3
    node.name = -1;
    return;
}


void freeGraph(graph_t *graph){
    /**
     * This will free the entire graph including metadata.
     * Things that need to be freed:
     *  1) Each node (adjNodes will inherently be freed).
     *  2) The array of Nodes.
     *  3) The array of adjNodes.
     *  4) The graph itself.
     * NOTE: If a node has already been freed it name will be -1.
     */
    // printf("FREEING GRAPH!\n");
    //1
    for(int i=0; i<graph->size; i++){
        if(graph->nodeArr[i].name != -1)
            freeGraphNode(graph, i);
    }
    fprintf(stderr, "All nodes have been freed\n");

    //2
    free(graph->nodeArr);
    graph->nodeArr = NULL;
    fprintf(stderr, "Array of Nodes have been freed\n");
    
    //3
    free(graph->adjArr);
    graph->adjArr = NULL;
    fprintf(stderr, "Array of adjNodes have been freed\n");

    //4
    free(graph);
    graph = NULL;
    fprintf(stderr, "Graph has been destroyed\n");

    return;
}