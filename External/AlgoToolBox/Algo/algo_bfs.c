#include "algo_dfs.h"
#include "algo_bfs.h"
#include "Src/DataStructure/Queue.h"
#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int *bfs(graph_t *graph, int start) 
{ 
    if(graph == NULL || start < 0 || start >= graph->num_nodes)
    {
        fprintf(stderr, "bfs : invalid graph or start index\n");
        return NULL;
    }
    int num_nodes = graph->num_nodes;
    bool* seen = calloc(num_nodes,sizeof(bool));
    if(seen == NULL) 
    {
        fprintf(stderr,"bfs : failed to allocate memory for seen list\n");
        exit(EXIT_FAILURE);
    }
    int* last = calloc(num_nodes,sizeof(int));
    if(last == NULL) 
    {
        fprintf(stderr,"bfs : failed to allocate memory for last list\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < num_nodes; ++i)
    {
        last[i] = -1;
    }
    queue_t* pending = queue_create(50);
    queue_push(pending,start);
    seen[start] = true;
    while(queue_is_empty(pending) == false)
    {
        int index = queue_pop(pending);
        
        node_t* current = &graph->nodes[index];
        edge_t* curr_edges = node_get_edges(current);
        int num_edges = node_get_num_edges(current);
        for(int i = 0; i < num_edges; ++i)
        {
            int neighbor = curr_edges[i].to_node;
            if(seen[neighbor] == false)
            {
                queue_push(pending,neighbor);
                seen[neighbor] = true;
                last[neighbor] = index;
            }
        }
    }
    queue_destroy(pending);
    return last; 
}

void bfs_test() 
{
    graph_t* g = malloc(sizeof(graph_t));
    graph_insert_edge(g,0,1,1.0f);
    graph_insert_edge(g,1,2,1.0f);
    graph_insert_edge(g,2,3,1.0f);
    graph_insert_edge(g,3,4,1.0f);

    int* last = bfs(g,0);

    printf("last[] from BFS starting at node 0:\n");
    for (int i = 0; i < g->num_nodes; ++i) {
        printf("last[%d] = %d\n", i, last[i]);
    }
    free(last);
    free(g);
}
