#pragma once
#include "DSNode.h"
#include <stddef.h>
#include <stdbool.h>
/*
    Binary Search Tree
*/
DSNode_t* bst_create(int* data,size_t tree_length);
DSNode_t* bst_insert(DSNode_t* root, int data);
DSNode_t* bst_search(DSNode_t* root,int target);
DSNode_t* bst_delete(DSNode_t* root,int target);
int bst_height(DSNode_t* tree);
bool bst_is_balanced(DSNode_t* root);
size_t bst_count_nodes(DSNode_t* tree);
void bst_fill_ordered(DSNode_t* tree, int* data, size_t* index);
DSNode_t* bst_find_minimum(DSNode_t* node);
int* bst_sorted_data(DSNode_t* tree);
void bst_destroy(DSNode_t *tree);

// console test 
void bst_print(DSNode_t* tree,int depth);
void bst_console_test();
// fancy raylib test
void bst_draw_node(DSNode_t* node, int x, int y, int offsetX);
void bst_raylib_test(bool bSorted);
