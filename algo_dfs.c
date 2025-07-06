#include <algo_dfs.h>
#include <stdlib.h>
#include <stdio.h>

void dfs_recursive_basic(graph_t *graph, int index, bool *seen) 
{
    seen[index] = true;
    node_t* current = &graph->nodes[index];
    edge_t* current_edges = node_get_edges(current);
    int current_num_edges = node_get_num_edges(current);
    for(int i = 0; i < current_num_edges;++i)
    {
        int neighbor = current_edges[i].to_node->index;
        if (seen[neighbor] != NULL)
        {
            fprintf(stderr,"dfs_recursive_basic : Neighbor in Seen is out of bound\n");
            exit(EXIT_FAILURE);
        }
        if(seen[neighbor] == false)
        {
            dfs_recursive_basic(graph,index,seen);
        }
    }
}

void dfs_basic(graph_t *graph, int start) 
{
    int num_nodes = graph->num_nodes;
    bool* seen = calloc(num_nodes,sizeof(bool));
    if(seen == NULL) 
    {
        fprintf(stderr,"dfs_basic : failed to allocate memory for seen list\n");
        exit(EXIT_FAILURE);
    }
    dfs_recursive_basic(graph,start,seen);
    free(seen);
}

void dfs_basic_all(graph_t *graph) 
{
    int num_nodes = graph->num_nodes;
    bool* seen = calloc(num_nodes,sizeof(bool));
    if(seen == NULL) 
    {
        fprintf(stderr,"dfs_basic_all : failed to allocate memory for seen list\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0;i<num_nodes;++i)
    {
        if(seen[i] == false)
        {
            dfs_recursive_basic(graph,i,seen);
        }
    }
    free(seen);
}

void dfs_recursive_path(graph_t *graph, int index, bool *seen, bool *last) 
{
    seen[index] = true;
    node_t* current = &graph->nodes[index];
    edge_t* current_edges = node_get_edges(current);
    int num_edges = node_get_num_edges(current);
    for(int i = 0; i < num_edges;++i)
    {
        int neighbor = current_edges[i].to_node;
        if(seen[neighbor] == false)
        {
            last[neighbor] = index;
            dfs_recursive_path(graph,neighbor,seen,last);
        }
    }
}

// int* last should be free after used
int* dfs_path(graph_t *graph) 
{ 
    int num_nodes = graph->num_nodes;
    bool* seen = calloc(num_nodes,sizeof(bool));
    if(seen == NULL)
    {
        fprintf(stderr,"dfs_path : failed to allocate memory for seen list\n");
        exit(EXIT_FAILURE);
    }
    int* last = calloc(num_nodes,sizeof(int));
    if(last == NULL)
    {
        fprintf(stderr,"dfs_path : failed to allocate memory for last list\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < num_nodes;++i)
    {
        last[i] = -1;
    }
    for(int i = 0; i < num_nodes;++i)
    {
        if(seen[i] == false)
        {
            dfs_recursive_path(graph,i,seen,last);
        }
    }
    free(seen);
    return last; 
}

void dfs_recursive_cc(graph_t *graph, int index, int *components,int current_comp)
{
    components[index] = current_comp;
    node_t* current_node = &graph->nodes[index];
    edge_t* current_edges = node_get_edges(current_node);
    int num_edges = node_get_num_edges(current_node);
    for(int i = 0; i < num_edges;++i)
    {
        int neighbor = current_edges[i].to_node;
        if(components[neighbor] == -1)
        {
            dfs_recursive_cc(graph,neighbor,components,current_comp);
        }
    }
}
// NEED TO FREE Components
int *dfs_connected_components(graph_t *graph) 
{ 
    int num_nodes = graph->num_nodes;
    int* components = calloc(num_nodes,sizeof(int));
    if(components == NULL)
    {
        fprintf(stderr,"dfs_connected_components : failed to allocate memory for components list\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < num_nodes;++i)
    {
        components[i] = -1;
    }
    int current_comp = 0;
    for(int i = 0; i < num_nodes;++i)
    {
        if(components[i] == -1)
        {
            dfs_recursive_cc(graph,i,components,current_comp);
            current_comp += 1;
        }
    }
    return components; 
}
