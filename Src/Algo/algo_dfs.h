#pragma once

/*
Depth First Search Algorithm (LIFO)
*/
#include "node.h"
#include "graph.h"

int* dfs(graph_t* graph, int start);

/* void dfs_recursive_basic(graph_t* graph,int index,bool* seen);
// API
void dfs_basic(graph_t* graph,int start);
// API
void dfs_basic_all(graph_t* graph);

void dfs_recursive_path(graph_t* graph,int index,bool* seen,bool* last);
// API : NEED TO FREE last
int* dfs_path(graph_t* graph);

// Connected Components
void dfs_recursive_cc(graph_t* graph,int index,int* components,int current_comp);
// API : NEED TO FREE Components
int* dfs_connected_components(graph_t* graph); */



