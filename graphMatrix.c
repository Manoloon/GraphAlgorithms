#include "graphMatrix.h"
#include <stdio.h>
#include <stdlib.h>

void init(graphMatrix_t *graphMatrix,int num_nodes,bool undirected) 
{
    graphMatrix->num_nodes = num_nodes;
    graphMatrix->undirected = undirected;
    // connections are [[0.0] * num_nodes, num_nodes];
}

void graphMatrix_set_edge(graphMatrix_t *graphMatrix, node_t *from_node,
                          node_t *to_node, float weight) {
  if (!graphMatrix || !from_node || !to_node)
    return;

  int fromIndex = from_node->index;
  int toIndex = to_node->index;

  if (fromIndex < 0 || fromIndex >= graphMatrix->num_nodes) {
    fprintf(stderr, "from node out of bound");
    return;
  }
  if (toIndex < 0 || toIndex >= graphMatrix->num_nodes) {
    fprintf(stderr, "to_node out of bound");
    return;
  }
  // allocate matrix if not already allocated
  if (!graphMatrix->connections) {
    graphMatrix->connections =
        malloc(graphMatrix->num_nodes * sizeof(edge_t *));
    for (int i = 0; i < graphMatrix->num_nodes; ++i) {
      graphMatrix->connections[i] =
          calloc(graphMatrix->num_nodes, sizeof(edge_t));
    }
  }
  // allocate new edge
  edge_t *new_edge = malloc(sizeof(edge_t));
  new_edge->from_node = from_node;
  new_edge->to_node = to_node;
  new_edge->weight = weight;

  // set edge
  graphMatrix->connections[fromIndex][toIndex] = new_edge;

  if (graphMatrix->undirected) {
    edge_t *mirror_edge = malloc(sizeof(edge_t));
    mirror_edge->from_node = to_node;
    mirror_edge->to_node = from_node;
    mirror_edge->weight = weight;
    graphMatrix->connections[toIndex][fromIndex] = mirror_edge;
  }
}

float graphMatrix_calc_path_cost(graphMatrix_t *graphMatrix) 
{ 
    
    return 0.0f; 
}

graphMatrix_t *graphMatrix_copy(graphMatrix_t *graphMatrix) 
{ 
    
    return NULL; 
}
