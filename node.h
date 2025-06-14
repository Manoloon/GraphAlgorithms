#pragma once
#include <stddef.h>

typedef struct node_t
{
    int index;
    char* label;
    edge_t* edges;
    size_t num_edges;
    size_t edge_capacity;
}node_t;

typedef struct edge_t
{
    node_t* to_node;
    node_t* from_node;
    float weight;
}edge_t;

size_t getNumEdges(node_t* node);
edge_t* getEdges(node_t* node);
void add_edge(node_t* target, node_t* new_node,float weight);
void remove_edge(node_t* target,node_t* to_remove);
edge_t* get_sorted_edges(node_t* node);
node_t* get_neighbors(node_t* node);
int edge_compare(const void* a, const void* b);
