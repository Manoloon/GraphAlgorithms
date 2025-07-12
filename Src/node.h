#pragma once
#include <stddef.h>

typedef struct node_t
{
    int index;
    int data;
    struct edge_t* edges;
    int num_edges;
    size_t edge_capacity;
}node_t;

typedef struct edge_t
{
    node_t* to_node;
    node_t* from_node;
    float weight;
}edge_t;

size_t node_get_num_edges(node_t* node);
edge_t* node_get_edge(node_t* from_node,int neighbor);
edge_t* node_get_edges(node_t* node);
void node_add_edge(node_t* target, node_t* new_node,float weight);
void node_remove_edge(node_t* target,node_t* to_remove);
edge_t* node_get_sorted_edges(node_t* node);
node_t** node_get_neighbors(node_t* node);
int edge_compare(const void* a, const void* b);
void node_destroy(node_t* node);
