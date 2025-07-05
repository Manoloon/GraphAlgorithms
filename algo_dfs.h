#pragma once

/*
Depth Breadth First Algorithm
*/
#include "node.h"
#include "graph.h"

void dfs_recursive_basic(graph_t* graph,int index,bool* seen);

void dfs_basic(graph_t* graph,int start);

void dfs_basic_all(graph_t* graph);

void dfs_recursive_path(graph_t* graph,int index,bool* seen,bool* last);

int* dfs_path(graph_t* graph);