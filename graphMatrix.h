#pragma once
#include "node.h"
#include <stdbool.h>

typedef struct graphMatrix_t
{
    edge_t*** connections;
    int num_nodes;
    bool undirected;
}graphMatrix_t;

void init(graphMatrix_t* graphMatrix,int num_nodes,bool undirected);
void graphMatrix_set_edge(graphMatrix_t* graphMatrix,node_t* from_node,node_t* to_node,float weight);
float graphMatrix_calc_path_cost(graphMatrix_t* graphMatrix);
graphMatrix_t* graphMatrix_copy(graphMatrix_t* graphMatrix);