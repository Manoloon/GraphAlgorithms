#include "node.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

size_t node_get_num_edges(node_t *node) 
{ 
    if(node == NULL) return 0;
    return node->num_edges > 0 ? node->num_edges : 0; 
}
//TODO
edge_t *node_get_edge(node_t *from_node, int neighbor) 
{ 
    if(neighbor < 0 || neighbor >= (int)from_node->num_edges)
    {
        return NULL; 
    }
    return &from_node->edges[neighbor];
}

edge_t *node_get_edges(node_t *node) 
{ 
    return node ? node->edges : NULL; 
}

void node_add_edge(node_t *target, node_t *new_node, float weight) 
{
    if(!target || !new_node) return;
    // expand capacity if needed
    if(target->num_edges >= (int)target->edge_capacity)
    {
        size_t new_capacity = target->edge_capacity == 0 ? 1 : target->edge_capacity * 2;
        edge_t* new_edges = realloc(target->edges, new_capacity * sizeof(edge_t));
        if(new_edges == NULL) return;
        target->edges = new_edges;
        target->edge_capacity = new_capacity;
    }

    edge_t new_edge = {.to_node = new_node,
                        .from_node = target,
                        .weight = weight};
    target->edges[target->num_edges] = new_edge;
    target->num_edges +=1;
}

void node_remove_edge(node_t *target, node_t *to_remove) 
{
    if(!target || !to_remove || target->num_edges == 0) return;
    int n = 0;
    while (n < target->num_edges)
    {
        if(target->edges[n].to_node == to_remove)
        {
            // move last edge into this slot
            target->edges[n] = target->edges[target->num_edges-1];
            target->num_edges-= 1;
            printf("remove : num_edges %d:\n",target->num_edges);
        }
        else
        {
            ++n;
        }
    }
}

edge_t *node_get_sorted_edges(node_t *node) 
{ 
    if(!node || node->num_edges == 0) return NULL;

    edge_t* sorted = malloc(node->num_edges * sizeof(edge_t));
    if(!sorted) return NULL;
    // TODO Sort the edges
    memcpy(sorted, node->edges, node->num_edges * sizeof(edge_t));
    qsort(sorted, node->num_edges, sizeof(edge_t), edge_compare);
    return sorted; 
}

node_t** node_get_neighbors(node_t *node) 
{ 
    if(node == NULL) return NULL;
    node_t** listNeighbors = malloc(sizeof(node_t*) * node->num_edges);
    if(listNeighbors == NULL ) return NULL;
    for(int i = 0; i < node->num_edges;++i)
    {
        listNeighbors[i] = node->edges[i].to_node;
        printf("GRAPH : neighbor index %d",listNeighbors[i]->index);
    }
    return listNeighbors; 
}

int edge_compare(const void *a, const void *b) 
{
    const edge_t* tempA = (const edge_t*)a;
    const edge_t* tempB = (const edge_t*)b; 
    return (tempA->weight > tempB->weight) - (tempA->weight < tempB->weight); 
}

void node_destroy(node_t *node) 
{
    if(node != NULL)
    {
        free(node->edges);
        free(node);
    }
}
