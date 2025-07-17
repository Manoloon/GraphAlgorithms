#include "algo_dfs.h"
#include "algo_bfs.h"
#include "Queue.h"
#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    queue_push(pending,&start);
    seen[start] = true;
    while(queue_is_empty(pending) == false)
    {
        int index = *(int*)queue_pop(pending);
        
        node_t* current = &graph->nodes[index];
        edge_t* curr_edges = node_get_edges(current);
        int num_edges = node_get_num_edges(current);
        for(int i = 0; i < num_edges; ++i)
        {
            int neighbor = curr_edges[i].to_node->index;
            if(seen[neighbor] == false)
            {
                queue_push(pending,&neighbor);
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
    int num_nodes = 100;
    time_t current_time;
    struct tm *local_time;
    time(&current_time);
    local_time = localtime(&current_time);
    printf("BFS Test Starting at %02d:%02d:%02d\n",local_time->tm_hour,local_time->tm_min,local_time->tm_sec);
    graph_t* g = graph_create(num_nodes,true);
    for(int i = 0; i < num_nodes-1;++i)
    {
        graph_insert_edge(g,i,i+1,1.0f);
    }

    int* last = bfs(g,0);

    printf("last[] from BFS starting at node 0:\n");
    for (int i = 0; i < g->num_nodes; ++i) {
        printf("last[%d] = %d\n", i, last[i]);
    }
    if(last != NULL)
    {
        free(last);
    }
    free(g);
}
