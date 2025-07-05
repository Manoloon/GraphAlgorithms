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
            fprintf(stderr,"Neighbor in Seen is out of bound");
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
        fprintf(stderr,"failed to allocate memory for seen list");
        exit(EXIT_FAILURE);
    }
    for(int i = 0 ; i < num_nodes;++i)
    {
        seen[i] = false;
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
        fprintf(stderr,"failed to allocate memory for seen list");
        exit(EXIT_FAILURE);
    }
    for(int i = 0 ; i < num_nodes;++i)
    {
        seen[i] = false;
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
