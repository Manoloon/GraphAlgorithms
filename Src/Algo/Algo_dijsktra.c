#include "Algo_Dijsktra.h"
#include <math.h>

int * shortest_path_DKT(graph_t * graph, int startIndex)
{
    int* cost = graph->nodes; // iniciar todos con infinito
    int* last = graph->nodes; // iniciar a todos con -1
    /*
    priorityQueue pq = minHeap;
    pq.enqueue(startIndex,0.0);
    for (i : g.nodes)
    {
        if(i != startIndex)
            pq.enqueue(i,infinity);
    }
    cost[startIndex] = 0.0;
    while(!pq.is_empty())
    {
        int index = pq.dequeue();
        for( edge : g.nodes[index].get_edges())
        {
            int neighbor = edge.to_node;
            if(pq.enqueue(neigh))
            {
                float new_cost = cost[index] + edge.weight;
                if(new_cost < cost[neighbor])
                {
                    pq.update_priority(neighbor,new_cost);
                    last[neighbor] = index;
                    cost[neighbor] = new_cost;
                }
            }
        }
    }
    */
return last;
}
