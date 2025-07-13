#pragma once
#include "node.h"
#include <stdbool.h>

typedef struct graphMatrix_t
{
    edge_t*** connections;
    int num_nodes;
    bool undirected;
}graphMatrix_t;

void graphMatrix_init(graphMatrix_t* graphMatrix,int num_nodes,bool undirected);
void graphMatrix_destroy(graphMatrix_t* graphMatrix);
void graphMatrix_set_edge(graphMatrix_t* graphMatrix,node_t* from_node,node_t* to_node,float weight);
//TODO : declare this two
//float graphMatrix_calc_path_cost(graphMatrix_t* graphMatrix);
//graphMatrix_t* graphMatrix_copy(graphMatrix_t* graphMatrix);

void graphMatrix_draw(graphMatrix_t* graphMatrix);