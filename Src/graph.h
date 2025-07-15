#pragma once
#include "node.h"
#include <stdbool.h>

typedef struct graph_t
{
    node_t* nodes;
    int num_nodes;
    bool undirected;
}graph_t;

typedef struct path_t
{
    node_t* nodes;
    int num_nodes;
}path_t;

graph_t* graph_create(int num_nodes,bool undirected);
// find the edge with the index from and to node
edge_t* graph_get_edge(graph_t* graph,int from_node,int to_node);
//
bool graph_is_edge(node_t* from_node, node_t* to_node);
edge_t* graph_make_edgeList(graph_t* graph);
void graph_insert_edge(graph_t* graph, int from_node, int to_node,float weight);
void graph_remove_edge_byIndex(graph_t* graph,int from_node, int to_node);
void graph_remove_edge(graph_t* graph,node_t* from_node, node_t* to_node);
graph_t* graph_make_copy(graph_t* from_graph);

node_t* graph_get_Out_neighbors(graph_t *from_graph, node_t* node);
node_t* graph_get_In_neighbors(graph_t *from_graph, node_t* node);
// Clustering Coefficient metric
// its a metric that shows how interconnected node's neighbors are with each other.
float graph_clustering_coefficient(graph_t* graph, int index);
// average local clustering coefficient
float avg_clustering_coefficient(graph_t* graph);

// generate an open or closed neighborhood subgraph around a given node ( with index) in an undirected graph
graph_t* graph_undirected_neighborhood_subgraph(graph_t* graph,int index, bool closed);
// make a grid
void graph_draw_grid(graph_t* graph,int width,int height);
void graph_draw_grid_obstacles(graph_t* graph,int width,int height,int** obstacles);
// Paths
bool graph_check_node_path_valid(graph_t* graph, path_t* path);
