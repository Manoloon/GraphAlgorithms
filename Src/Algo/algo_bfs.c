#include "algo_dfs.h"
#include "algo_bfs.h"
#include "Src/DataStructure/Queue.h"
#include <stdio.h>
#include <stdlib.h>

int *bfs(graph_t *graph, int start) 
{ 
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
    for(int i = 0; i < num_nodes;++i)
    {
        last[i] = -1;
    }
    queue_t* pending = create_queue();
    pending.put(start);
    seen[start] = true;
    while(queue_is_empty(pending) == false)
    {
        int index = pending.get();
        node_t* current = &graph->nodes[index];
        edge_t* curr_edges = node_get_edges(current);
        int num_edges = node_get_num_edges(current);
        for(int i = 0;i < num_edges;++i)
        {
            int neighbor = curr_edges[i].to_node;
            if(seen[neighbor] == false)
            {
                pending.put(neighbor);
                seen[neighbor] = true;
                last[neighbor] = i;
            }
        }
    }
    free(pending);
    return last; 
}
