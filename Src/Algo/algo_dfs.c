#include "algo_dfs.h"
#include "Stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int *dfs(graph_t *graph, int start) 
{
    if(graph == NULL || start < 0 || start >= graph->num_nodes)
    {
        fprintf(stderr, "dfs : invalid graph or start index\n");
        return NULL;
    }
    int num_nodes = graph->num_nodes;

    bool* seen = calloc(num_nodes,sizeof(bool));
    if(seen == NULL) 
    {
        fprintf(stderr,"dfs : failed to allocate memory for seen list\n");
        exit(EXIT_FAILURE);
    }

    int* last = calloc(num_nodes,sizeof(int));
    if(last == NULL) 
    {
        fprintf(stderr,"dfs : failed to allocate memory for last list\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i< num_nodes;++i)
    {
        last[i] = -1;
    }
    stack_t* to_explore = stack_create(50);
    int* start_ptr = malloc(sizeof(int));
    *start_ptr = start;
    stack_push(to_explore,start_ptr);
    while (!stack_is_empty(to_explore))
    {
        int* index_ptr = stack_pop(to_explore);
        int index = *index_ptr;
        free(index_ptr);
        if(!seen[index])
        {
            seen[index] = true;
            node_t* current = &graph->nodes[index];
            edge_t* all_edges = node_get_sorted_edges(current);
            int num_edges = node_get_num_edges(current);
            //reverse all edges
            for(int i = num_edges-1;i>=0;--i)
            {
                int neighbor = all_edges[i].to_node->index;
                if(!seen[neighbor])
                {
                    int* neighbor_ptr = malloc(sizeof(int));
                    *neighbor_ptr = neighbor;
                    stack_push(to_explore,neighbor_ptr);
                    last[neighbor] = index;
                }
            }
            free(all_edges);
        }
    }
    stack_destroy(to_explore);
    free(seen);
    return last; 
}
void dfs_test() 
{
    time_t current_time;
    struct tm *local_time;
    time(&current_time);
    local_time = localtime(&current_time);
    printf("DFS Test Starting at %02d:%02d:%02d\n",local_time->tm_hour,local_time->tm_min,local_time->tm_sec);
    graph_t* g = graph_create(5,true);

    graph_insert_edge(g,0,1,1.0f);
    graph_insert_edge(g,1,2,1.0f);
    graph_insert_edge(g,2,3,1.0f);
    graph_insert_edge(g,3,4,1.0f);

    int* last = dfs(g,0);

    printf("last[] from DFS starting at node 0:\n");
    for (int i = 0; i < g->num_nodes; ++i) {
        printf("last[%d] = %d\n", i, last[i]);
    }
    if(last != NULL)
    {
        free(last);
    }
    free(g);
}
