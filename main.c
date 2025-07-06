#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "graph.h"
#include "graphMatrix.h"

// int argc,char* argv[]
int main() 
{
    node_t* new_node1 = malloc(sizeof(node_t));
    new_node1->edge_capacity = 0;
    new_node1->index = 0;
    new_node1->edges = NULL;
    new_node1->num_edges = 0;
    node_t* new_node2 = malloc(sizeof(node_t));
    new_node2->edge_capacity = 0;
    new_node2->index = 1;
    new_node2->edges = NULL;
    new_node2->num_edges = 0;
    node_add_edge(new_node1,new_node2,2);

    node_destroy(new_node1);
    node_destroy(new_node2);
    // graph matrix
    graphMatrix_t gMatrix;
    graphMatrix_init(&gMatrix,13,true);
    graphMatrix_draw(&gMatrix);
    graphMatrix_destroy(&gMatrix);
    return 0;
}