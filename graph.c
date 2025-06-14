#include "graph.h"

edge_t *get_edges(graph_t *graph, node_t *from_node, node_t *to_node) 
{
  return graph->nodes->edges;
}

bool is_edge(node_t *from_node, node_t *to_node) 
{ 
    return from_node->edges->to_node == to_node; 
}

edge_t *make_edgeList(graph_t *graph) 
{ 
    return NULL; 
}

void insert_edge(graph_t *graph, node_t *from_node, node_t *to_node,
                 float weight) 
                 {

                 }

void add_edge(graph_t *graph, node_t *to_node, float weight) 
{

}

void remove_edge(graph_t *graph, node_t *to_node) 
{
    if(graph->nodes->edges->to_node == to_node)
    {
        graph->nodes->edges->to_node == NULL;
    }
}

graph_t *make_graph_copy(graph_t *from_graph) 
{ 
    graph_t* new_graph = malloc(sizeof(from_graph));
    if(new_graph == NULL) return NULL;
    new_graph = from_graph;
    return new_graph; 
}

node_t *get_Out_neighbors(graph_t *from_graph, node_t *node) 
{ 
    if(node == NULL) return NULL;
    node_t* listNeighbors = malloc(sizeof(node_t)* from_graph->num_nodes);
    if(listNeighbors == NULL) return NULL;

    for(size_t i = 0; i < from_graph->num_nodes;++i)
    {
        listNeighbors[i] = *from_graph->nodes->edges->to_node;
    } 
    return listNeighbors;
}

node_t *get_In_neighbors(graph_t *from_graph, node_t *node) 
{ 
    if(node == NULL) return NULL;
    node_t* listNeighbors = malloc(sizeof(node_t)* from_graph->num_nodes);
    if(listNeighbors == NULL) return NULL;

    for(size_t i = 0; i < from_graph->num_nodes;++i)
    {
        listNeighbors[i] = from_graph->nodes[i];
    } 
    return listNeighbors; 
}

float clustering_coefficient(graph_t *graph, int index) 
{
    
    return 0.0f; 
}
