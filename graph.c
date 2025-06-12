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
