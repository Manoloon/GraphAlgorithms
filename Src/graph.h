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

edge_t* get_edges(graph_t* graph,node_t* from_node,node_t* to_node);
bool is_edge(node_t* from_node, node_t* to_node);
edge_t* make_edgeList(graph_t* graph);
void insert_edge(graph_t* graph, node_t* from_node, node_t* to_node,float weight);
void add_edge(graph_t* graph, node_t* to_node,float weight);
void remove_edge(graph_t* graph, node_t* to_node);
graph_t* make_graph_copy(graph_t* from_graph);

node_t* get_Out_neighbors(graph_t *from_graph, node_t* node);
node_t* get_In_neighbors(graph_t *from_graph, node_t* node);
// Clustering Coefficient metric
// its a metric that shows how interconnected node's neighbors are with each other.
float clustering_coefficient(graph_t* graph, int index);
// average local clustering coefficient
float avg_clustering_coefficient(graph_t* graph);
// generate an open or closed neighborhood subgraph around a given node ( with index) in an undirected graph
graph_t* make_undirected_neighborhood_subgraph(graph_t* graph,int index, bool closed);

// Paths
bool check_node_path_valid(graph_t* graph, path_t* path);
