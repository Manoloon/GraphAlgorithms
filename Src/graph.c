#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

edge_t *graph_get_edge(graph_t *graph, int from_node, int to_node) 
{
    if(from_node < 0 || from_node >= graph->num_nodes)
    {
        fprintf(stderr,"graph_get_edge : from_node out of bound\n");
        exit(EXIT_FAILURE);
    }
    if(to_node < 0 || to_node >= graph->num_nodes)
    {
        fprintf(stderr,"graph_get_edge : to_node out of bound\n");
        exit(EXIT_FAILURE);
    }

    return node_get_edge(&graph->nodes[from_node],to_node);
}

bool graph_is_edge(node_t *from_node, node_t *to_node) 
{ 
    return from_node->edges->to_node == to_node; 
}

edge_t *graph_make_edgeList(graph_t *graph) 
{ 
    int num_nodes = graph->num_nodes;
    if(num_nodes < 1) return NULL;
    int num_edges = 0;
    for(int i = 0; i < num_nodes;++i)
    {
        num_edges += graph->nodes[i].num_edges;
    }
    edge_t* all_edges =malloc(sizeof(edge_t)*num_edges);
    if(all_edges == NULL)
    {
        fprintf(stderr,"graph_make_list : failed to allocate\n");
        exit(EXIT_FAILURE);
    }
  
    // Copy all edges into the new array
    int k = 0; // Index in all_edges
    for (int i = 0; i < num_nodes; ++i) 
    {
        for (int j = 0; j < graph->nodes[i].num_edges; ++j) 
        {
            all_edges[k++] = graph->nodes[i].edges[j];
        }
    }
    return all_edges; 
}

void graph_insert_edge(graph_t *graph, int from_node, int to_node,float weight) 
{
    if(from_node < 0 || from_node >= graph->num_nodes)
    {
        fprintf(stderr,"graph_insert_edge : from_node out of bound\n");
        exit(EXIT_FAILURE);
    }
    if(to_node < 0 || to_node >= graph->num_nodes)
    {
        fprintf(stderr,"graph_insert_edge : to_node out of bound\n");
        exit(EXIT_FAILURE);
    }
    node_add_edge(&graph->nodes[from_node],&graph->nodes[to_node],weight);
    if(graph->undirected)
    {
        node_add_edge(&graph->nodes[to_node],&graph->nodes[from_node],weight);
    }
}

void graph_remove_edge_byIndex(graph_t *graph, int from_node, int to_node) 
{
    if(from_node < 0 || from_node >= graph->num_nodes)
    {
        fprintf(stderr,"graph_remove_edge_byIndex : from_node out of bound\n");
        exit(EXIT_FAILURE);
    }
    if(to_node < 0 || to_node >= graph->num_nodes)
    {
        fprintf(stderr,"graph_remove_edge_byIndex : to_node out of bound\n");
        exit(EXIT_FAILURE);
    }
    node_remove_edge(&graph->nodes[from_node],&graph->nodes[to_node]);
    if(graph->undirected)
    {
        node_remove_edge(&graph->nodes[to_node],&graph->nodes[from_node]);
    }
}

void graph_remove_edge(graph_t *graph,node_t* from_node, node_t *to_node) 
{
     for (int i = 0; i < graph->num_nodes; ++i) 
    {
        if (&graph->nodes[i] == from_node) 
        {
            // Remove the edge from 'from_node' to 'to_node'
            node_remove_edge(from_node, to_node);

            // If the graph is undirected, remove the reverse edge too
            if (graph->undirected) 
            {
                node_remove_edge(to_node, from_node);
            }

            break; // Edge removed, no need to continue looping
        }
    }
}

graph_t *graph_make_copy(graph_t *from_graph) 
{ 
    graph_t* new_graph = malloc(sizeof(*from_graph));
    if(new_graph == NULL) return NULL;
    new_graph = from_graph;
    return new_graph; 
}

node_t *graph_get_Out_neighbors(graph_t *from_graph, node_t *node) 
{ 
    if(node == NULL) return NULL;
    node_t* listNeighbors = malloc(sizeof(node_t)* from_graph->num_nodes);
    if(listNeighbors == NULL) return NULL;

    for(int i = 0; i < from_graph->num_nodes;++i)
    {
        listNeighbors[i] = *from_graph->nodes->edges->to_node;
    } 
    return listNeighbors;
}

node_t *graph_get_In_neighbors(graph_t *from_graph, node_t *node) 
{ 
    if(node == NULL) return NULL;
    node_t* listNeighbors = malloc(sizeof(node_t)* from_graph->num_nodes);
    if(listNeighbors == NULL) return NULL;

    for(int i = 0; i < from_graph->num_nodes;++i)
    {
        listNeighbors[i] = from_graph->nodes[i];
        printf("GRAPH : neighbor index %d",listNeighbors[i].index);
    } 
    return listNeighbors; 
}

float graph_clustering_coefficient(graph_t *graph, int index) 
{
    if(!graph) return 0.0f;

    node_get_neighbors(&graph->nodes[index]);
    int num_edges = graph->nodes[index].num_edges;
    node_t** neighbors = node_get_neighbors(&graph->nodes[index]);

    int count  = 0;
    for(int i = 0; i < num_edges;++i)
    {
        node_t* ni = neighbors[i];
        for(int j = 0; j < neighbors[i]->num_edges;++j)
        {
            node_t* nj = neighbors[j];
            //check if ni and nj are connected
            for(int k = 0; k < ni->num_edges;++k)
            {
                if(ni->edges[k].to_node == nj)
                {
                    count +=1;
                    break;
                }
            }
        }
    }
    free(neighbors);
    float possible_links = (num_edges * (num_edges -1)) / 2.0f;
    if(possible_links == 0.0f) return 0.0f;
    return count / possible_links; 
}

float avg_clustering_coefficient(graph_t *graph) 
{
    if(!graph || graph->num_nodes == 0) return 0.0f;
    float total = 0.0f;
    for(int i = 0; i < graph->num_nodes;++i)
    {
        total += graph_clustering_coefficient(graph,i);
    } 

    return total / graph->num_nodes; 
}

graph_t *graph_undirected_neighborhood_subgraph(graph_t *graph, int index,
                                               bool closed) 
{
    if(!graph->undirected || !graph)
    {
        fprintf(stderr,"the graph should be undirected");
        return NULL;
    }

    node_t* center_node = &graph->nodes[index];
    size_t num_neighbors = node_get_num_edges(center_node);
    size_t num_nodes_in_subgraph = closed ? num_neighbors +1 : num_neighbors;

    //allocate node array for subgraph 
    node_t** nodes_to_use = malloc(sizeof(node_t*) * num_nodes_in_subgraph);
    if(nodes_to_use == NULL) return NULL;
    // add neighbors to list
    for(size_t i = 0; i < num_neighbors; ++i)
    {
        nodes_to_use[i] = center_node->edges[i].to_node;
    }
    if(closed)
    {
        nodes_to_use[num_neighbors] = center_node;
    }

    // create index mapping from old to new
    int index_map[100]; // TODO : dynamic size
    for(int i = 0 ; i < 100; ++i)
    {
        index_map[i] = 1;
    }
    for(size_t i = 0; i < num_nodes_in_subgraph;++i)
    {
        index_map[nodes_to_use[i]->index] = i;
    }

    // allocate subgraph
    graph_t* subgraph = malloc(sizeof(graph_t));
    if(subgraph == NULL) return NULL;
    subgraph->num_nodes = num_nodes_in_subgraph;
    subgraph->nodes = calloc(num_nodes_in_subgraph,sizeof(node_t));
    subgraph->undirected = true;

    // copy nodes with new indices
    for(size_t i = 0 ; i < num_nodes_in_subgraph;++i)
    {
        subgraph->nodes[i].index = i;
    }
    // copy edges within neighborhood
    for(size_t i = 0 ; i < num_nodes_in_subgraph;++i)
    {
        node_t* old_node = nodes_to_use[i];
        for(int j = 0 ; j < old_node->num_edges;++j)
        {
            node_t* neighbor = old_node->edges[j].to_node;
            int new_neighbor_index = index_map[neighbor->index];
            if(new_neighbor_index != -1)
            {
                // add edge to new graph
                node_add_edge(&subgraph->nodes[i],
                            &subgraph->nodes[new_neighbor_index],
                                    old_node->edges[j].weight);
            }
        }
    }
    free(nodes_to_use);
  return subgraph;
}

void graph_draw_grid(graph_t* graph, int width, int height) 
{ 
    for(int r = 0; r < height;++r)
    {
        for(int c = 0; c < width;++c)
        {
            int index = r * width + c;
            if(c < width -1 )
                graph_insert_edge(graph,index,index+1,1.0);
            if(r < height -1)
                graph_insert_edge(graph,index,index+1,1.0);
        }
    }
}

void graph_draw_grid_obstacles(graph_t* graph,int width, int height, int **obstacles) 
{
    for(int r = 0; r < height;++r)
    {
        for(int c = 0; c < width;++c)
        {
            if(obstacles[r][c] == 0)
            {
                int index = r * width + c;
                if(c < width -1 && obstacles[r][c+1] == 0)
                    graph_insert_edge(graph,index,index+1,1.0);
                if(r < height -1 && obstacles[r+1][c] == 0)
                    graph_insert_edge(graph,index,index+1,1.0);
            }
        }
    }
}

bool graph_check_node_path_valid(graph_t *graph, path_t* path) 
{ 
    if(graph == NULL || path == NULL) return false;
    
    int num_node_on_path = path->num_nodes;
    if(num_node_on_path == 0) return true;
    
    node_t* prev_node = &path->nodes[0];
    if(prev_node->index < 0 || prev_node->index >= graph->num_nodes) return false;

    for(int i = 0; i < num_node_on_path; ++i)
    {
        node_t* next_node = &path->nodes[i];
        if(!graph_is_edge(prev_node,next_node)) return false;
        prev_node = next_node;
    }
    return true; 
}
