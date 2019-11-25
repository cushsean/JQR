#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

enum SIZE {SIZE = 5};			//How many nodes will be in the plot
enum MAX_DIST {MAX_DIST = 10};	//Maximum distance between each node
const int ID = 0;				//Standin for node.nbrs array parameter - adjacent node
const int DIST = 1;				//Standin for node.nbrs array parameter - distance between nodes

typedef struct graph{
	int nbrs[SIZE-1][2];	//adjacent nodes and distance
	int nbrs_count;			//number of adjacent(neighbor) nodes
}graph_t;

struct short_path{
	int length;			//node the path is to
	int route[SIZE];	//array of the path to the node
};

void get_nbrs(graph_t*);

void assign_nbr(int, int, graph_t*);

void set_inital_values(graph_t*);
	
int main() {
	srand(time(NULL));				//seeds the random number table
	graph_t node[SIZE];		//initializes an array of graph nodes
	set_inital_values(node);		//sets the initial vales for all node varialbes
	get_nbrs(node);					//generates neighbors for all nodes

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//												**DIJKSTRA ALGORITHM PLAN**												//
	//																														//
	// Node 0 will always be the starting node 																				//
	// Node 9 will always be the ending node 																				//
	// Tentitive distances to each node from 0 are set to SIZE*MAX_DIST to ensure a greater distance than possible			//
	// The dist to the initial node (node 0) is set to 0 																	//
	// Arrays for both visited and unvisted nodes are kept up-to-date; perhaps 1 2d arrays 									//
	// Viste the node with the shortest distance from the start node first													//
	// When visiting a node, compare the calculated distance from the start to that node and compare to the stored distance //
	// If the calculated distance is less than the stored distance, replace the stored distance and update the path			//
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	return 0;												//END OF PROGRAM
}

void get_nbrs(graph_t *node){
	for (int curr_node = 0; curr_node < SIZE-1; curr_node++){
		//int off_set = curr_node + 1;
		int new_nbr_count;
		if (node[curr_node].nbrs_count == 0){
			//off_set = curr_node + 2;						//For random numbers greater than 0
			new_nbr_count = rand() % (SIZE - (node[curr_node].nbrs_count + 1)) + 1;	//Gets random number 1 - 4
		}
		else{
			//off_set = curr_node + 1;					//For random numbers greater than or equal to 0
			//int available_nbrs = SIZE - off_set;
			//new_nbr_count = rand() % (SIZE - (node[curr_node].nbrs_count));	//Gets random number between 0 - 4
			new_nbr_count = rand() % (SIZE - (node[curr_node].nbrs_count));	//Gets random number between 0 - 4
		}
		//break
		//print curr_node
		//print node[curr_node].nbrs_count
		//print new_nbr_count
		printf("Node: %d\n", curr_node);
		printf("New_nbr: ");
		while (new_nbr_count > 0){			
			//off_set = curr_node + 1;
			/*
			int new_nbr = rand() % (SIZE - off_set) + off_set;
			for (int nbr = 0; nbr < node[curr_node].nbrs_count; nbr++){
				while (new_nbr == node[curr_node].nbrs[nbr][ID]){
					new_nbr = rand() % (SIZE - off_set) + off_set;
				}
			}
			*/
			int new_nbr = rand() % SIZE;
			for (int nbr = 0; nbr < node[curr_node].nbrs_count; nbr++){
				while (new_nbr == node[curr_node].nbrs[nbr][ID] || new_nbr == curr_node){
					new_nbr = rand() % SIZE;
				}
			} 
			printf(" %d", new_nbr);
			//break
			//print new_nbr
			assign_nbr(curr_node, new_nbr, node);
			new_nbr_count--;
			//break
			//print new_nbr_count
		}
		printf("\n");

	}
	return;
}

void assign_nbr(int n1, int n2, graph_t *node){
	int count_1 = node[n1].nbrs_count++;
	int count_2 = node[n2].nbrs_count++;
	node[n1].nbrs[count_1][ID] = n2;
	node[n1].nbrs[count_1][DIST] = rand() % MAX_DIST + 1;
	node[n2].nbrs[count_2][ID] = n1;
	node[n2].nbrs[count_2][DIST] = rand() % MAX_DIST + 1;
	//break
	//print node[n1].nbrs_count
	//print node[n2].nbrs_count
}

void set_inital_values(graph_t *node){
	for (int i = 0; i < sizeof(node); i++){
		node[i].nbrs_count = 0;
		for (int k = 0; k < sizeof(node[i].nbrs[0][0]); k++){
			node[i].nbrs[k][0] = -1;	//Setting every nodes nbrs to invalid (-1) 
			node[i].nbrs[k][1] = -1;
		}
	}
}