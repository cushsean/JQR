#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

enum SIZE {SIZE = 5};			//How many nodes will be in the plot
enum MAX_DIST {MAX_DIST = 10};	//Maximum distance between each node
const int ADJ = 0;				//Standin for node.wt array parameter - adjacent node
const int DIST = 1;				//Standin for node.wt array parameter - distance between nodes

struct graph{
	//int id;					//name of node
	int nbrs[SIZE-1][2];	//adjacent nodes and distance
	int nbrs_count;			//number of adjacent(neighbor) nodes
	//int vis;				//Boolean has the node been visited
	//int weight;				//Stored distance to the node
};

struct short_path{
	int length;			//node the path is to
	int route[SIZE];	//array of the path to the node
};
/*
void rand_plot(struct graph *node, int);

void update_weight(int, struct short_path *path, struct graph *node);

int update_curr(struct graph *node);
*/
void get_nbrs(struct graph *node);

void assign_nbr(int, int, struct graph *node);

void set_inital_values(struct graph *node);
	
int main() {
	srand(time(NULL));				//seeds the random number table
	struct graph node[SIZE];		//initializes an array of graph nodes
	set_inital_values(node);		//sets the initial vales for all node varialbes
	get_nbrs(node);					//generates neighbors for all nodes
	/*
	struct short_path path[SIZE];	//struct of short_path for each node on the graph
	rand_plot(node, 1);				//create a random plot of nodes
	fprintf(stderr,"GRAPH CREATED\n");
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

	node[0].weight=0;										//set starting node distance to 0
	node[0].vis=1;											//add starting node to visited list
	path[0].length=1;										//set the number of nodes in route to 1
	path[0].route[0]=0;										//set routes first node to 0
	for(int i=1; i<SIZE; i++){
		node[i].weight = SIZE * MAX_DIST;					//Sets all other distances to SIZE * MAX_DIST to ensure a greater value than possible
		node[i].vis = 0;									//remove all other nodes from visited list
		path[i].length=1;									//Add node 0 as first node in route to all nodes
		path[i].route[0]=0;
	}
	int curr_node = 0;										//set current node to 0 (first node)
	fprintf(stderr,"DEFAULTS SET\n");
	do{
		fprintf(stderr,"CURRENT NODE: %d\n",curr_node);
		update_weight(curr_node, path, node);				//update weights for the current node
		curr_node = update_curr(node);						//update the current node
		node[curr_node].vis=1;
	}while(curr_node != SIZE-1);							//until the current node is the final node
	printf("The shortest path from 0 to %d is:\n",SIZE-1);	//print to stdout
	for(int i=0; i<path[SIZE-1].length; i++){				//prints shortest route to final node n in formate 0->...->n
		if(path[SIZE-2].route[i] == SIZE-2){
			printf("%d\n",SIZE-1);
		}
		printf("%d->",path[SIZE-2].route[i]);
	}
	*/
	return 0;												//END OF PROGRAM
}
/*
void rand_plot(struct graph *node, int prt){
	for(int i=0; i<SIZE; i++){							//cycles through all nodes
		node[i].id = i;									//sets id of each node
		node[i].nbrs = 0;								//sets number of adjacent nodes to 0
		for(int n=0; n<=rand()%(SIZE); n++){				//cycles through a random number of adjacent nodes
			int new_nbr = rand()%SIZE;					//random node to be adjacent to node[i]
			while(new_nbr == i){						
				new_nbr = rand()%SIZE;					//ensure new neighbor is not current node
			}											
			for(int j=0; j<node[i].nbrs; j++){			//cycles through all neighbors of the current node
				if(new_nbr == node[i].wt[j][ADJ]){		//if new neighbor is already a neighbor, re-randomize new neighbor
					do{									
						new_nbr = rand()%SIZE;			
					}while(new_nbr == i);				//ensure new neighbor is not current node
				}
			}
			node[i].wt[n][ADJ] = new_nbr;				//set new neighbor as an adjacent node
			node[i].wt[n][DIST] = rand()%MAX_DIST+1;	//set random dist between to new neighbor
			node[i].nbrs++;								//increment neightbor count
			//////////////////////////////////////////////////////////////////////////////////////
			// 									**OPTIMIZATION**								//
			// CAN OPTIMIZE MEMORY USAGE IN LUE OF CLOCK CYCLES BY CALCULATING THE NUMBER OF 	//
			// EXISTING NEIGHBORS INSTEAD OF COUNTING THEM. SINCE STRUCT ARRAYS ARE INHERINTL	//
			// LARGER THAN TYPICAL ARRAYS CALCULATION WILL SHOW MORE BENIFIT AS THE ARRAY GROWS	//
			//////////////////////////////////////////////////////////////////////////////////////
		}
	}
	if(prt == 1){										//prints the nodes and their neighbors if prt flag is true
		for(int i=0; i<SIZE; i++){
			printf("\nNode: %d\n", node[i].id);
			for(int n=0; n<node[i].nbrs; n++){
				printf("\t%d:%d\n", node[i].wt[n][ADJ], node[i].wt[n][DIST]);
			}
		}
	}
	return;
}

void update_weight(int curr, struct short_path *path, struct graph *node){
	fprintf(stderr,"CURRENT NODE NEIGHBORS: %d\n", node[curr].nbrs);
	for(int i=0; i<node[curr].nbrs; i++){							//compare calculated weights to stored weights of all neighbor nodes
		int nbr = node[curr].wt[i][ADJ];							//set nbr(neighbor) node
		int calc_weight = node[curr].wt[i][DIST]+node[curr].weight;	//weight to neighbor node plus current node's weight
		fprintf(stderr,"NEIGHBOR = %d\nCALCULATED WEIGHT = %d\nNEIGHBORS WEIGHT = %d\n",nbr,calc_weight,node[nbr].weight);
		if(calc_weight < node[nbr].weight){ 						//if calculated weight is less then the neighbor's stored weight
			node[nbr].weight = calc_weight;							//set the stored weight to the calculated weight
			path[curr].route[path[curr].length] = nbr;				//update route to nbr node with route to current node with nbr node appended
			fprintf(stderr,"WEIGHT OF NODE %d SET TO %d\n",nbr,calc_weight);
		}
	}
}

int update_curr(struct graph *node){
	int nxt = 1;													//nxt(next node) set to 1, 0 will never be next node
	for(int i=1; i<SIZE; i++){										//excluding node 0, look at all nodes
		if(!node[i].vis && node[i].weight < node[nxt].weight){		//if current node not visited and current node weight less than nxt weight
			nxt = i;												//current node is next node
			fprintf(stderr,"NXT SET TO %d\n",nxt);
		}
	}
	return nxt;
}
*/
void get_nbrs(graph_t *node){
	for (int curr_node = 0; curr_node < SIZE-1; curr_node++){
		int off_set;
		int new_nbr_count;
		if (node[curr_node].nbrs_count == 0){
			off_set = curr_node + 2;
			new_nbr_count = rand() % (SIZE - off_set) + 1;
		}
		else{
			off_set = curr_node + 1;
			new_nbr_count = rand() % (SIZE - off_set);
		}
		printf("Node: %d\n", curr_node);
		printf("New_nbr: ");
		while (new_nbr_count >= 0){			
			off_set = curr_node + 1;
			int new_nbr = rand() % (SIZE - off_set) + off_set;
			printf(" %d", new_nbr);
			assign_nbr(curr_node, new_nbr, node);
			new_nbr_count--;
		}
		printf("\n");

	}
	return;
}

void assign_nbr(nd1, nd2, *node){
	int count_1 = node[nd1].nbrs_count;
	int count_2 = node[nd2].nbrs_count;
	node[n1].nbrs[count_1][ADJ] = nd2;
	node[n1].nbrs[count_1][DIST] = rand() % MAX_DIST + 1;
	node[n2].nbrs[count_2][ADJ] = nd1;
	node[n2].nbrs[count_2][DIST] = rand() % MAX_DIST + 1;
}

void set_inital_values(*node){
	for (int i = 0; i < sizeof(node); i++){
		node[i].nbrs_count = 0;
		for (int k = 0; k < sizeof(node[i].nbrs[0][0]); k++){
			node[i].nbrs[k][0] = NULL;
			node[i].nbrs[k][1] = NULL;
		}
	}
}