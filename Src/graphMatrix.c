#include "graphMatrix.h"
#include <stdio.h>
#include <stdlib.h>

void graphMatrix_init(graphMatrix_t *graphMatrix,int num_nodes,bool undirected) 
{
  graphMatrix->num_nodes = num_nodes;
  graphMatrix->undirected = undirected;
  graphMatrix->connections = malloc(num_nodes * sizeof(float*));
  if(graphMatrix->connections == NULL)
  {
    fprintf(stderr,"graph Matrix : init : failed to allocate\n");
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < num_nodes;++i)
  {
    graphMatrix->connections[i] = calloc(num_nodes,sizeof(float));
    if(graphMatrix->connections[i] == NULL)
    {
      fprintf(stderr,"init : failed to allocate rows\n");
      //clean
      for(int j = 0; j < i; ++j)
      {
        free(graphMatrix->connections[j]);
      }
      free(graphMatrix->connections);
      exit(EXIT_FAILURE);
    }
  }
}

void graphMatrix_destroy(graphMatrix_t *graphMatrix) 
{
  for(int i = 0; i < graphMatrix->num_nodes;++i)
  {
    free(graphMatrix->connections[i]);
  }
  free(graphMatrix->connections);
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

/* float graphMatrix_calc_path_cost(graphMatrix_t *graphMatrix) 
{ 
    
    return 0.0f; 
}

graphMatrix_t *graphMatrix_copy(graphMatrix_t *graphMatrix) 
{ 
    
    return NULL; 
} */

void graphMatrix_draw(graphMatrix_t *graphMatrix) 
{
    int n = graphMatrix->num_nodes;

    printf("Adjacency Matrix (%d nodes):\n    ", n);
    for (int i = 0; i < n; ++i)
        printf("%3d", i);
    printf("\n   ");
    for (int i = 0; i < n; ++i)
        printf("----");
    printf("\n");

    for (int i = 0; i < n; ++i) {
        printf("%2d |", i);
        for (int j = 0; j < n; ++j) 
        {
          edge_t* temp_edge = graphMatrix->connections[i][j];
          printf("%3.0f", temp_edge->weight);
        }
        printf("\n");
    }
}
