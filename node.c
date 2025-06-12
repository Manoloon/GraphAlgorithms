#include "node.h"

size_t getNumEdges(node_t *node) 
{ 
    return node ? node->num_edges : 0; 
}

edge_t *getEdges(node_t *node) 
{ 
    return node ? node->edges : NULL; 
}

void add_edge(node_t *target, node_t *new_node, float weight) 
{
    if(!target || !new_node) return;
    // expand capacity if needed
    if(target->num_edges >= target->edge_capacity)
    {
        size_t new_capacity = target->edge_capacity == 0 ? 4 : target->edge_capacity * 2;
        edge_t* new_edges = realloc(target->edges, new_capacity * sizeof(edge_t));
        if(new_edges == NULL) return;
        target->edges = new_edges;
        target->edge_capacity = new_capacity;
    }

    edge_t new_edge = {.to_node = new_node,
                        .from_node = target,
                        .weight = weight};
    target->edges[target->num_edges++] = new_edge;
}

void remove_edge(node_t *target, node_t *to_remove) 
{
    if(!target || !to_remove || target->num_edges == 0) return;
    size_t n = 0;
    while (n < target->num_edges)
    {
        if(target->edges[n].to_node == to_remove)
        {
            // move last edge into this slot
            target->edges[n] = target->edges[target->num_edges - 1];
            target->num_edges--;
        }
        else
        {
            ++n;
        }
    }
}

edge_t *getSortedEdges(node_t *node) 
{ 
    if(!node || node->num_edges == 0) return NULL;

    edge_t* sorted = malloc(node->num_edges * sizeof(edge_t));
    if(!sorted) return NULL;
    memcpy(sorted,node->edges,sizeof(edge_t),edge_compare);
    return sorted; 
}

int edge_compare(const void *a, const void *b) 
{
    const edge_t* tempA = (const edge_t*)a;
    const edge_t* tempB = (const edge_t*)b; 
    return (tempA->weight > tempB->weight) - (tempA->weight < tempB->weight); 
}
