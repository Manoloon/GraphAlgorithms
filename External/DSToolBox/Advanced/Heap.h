#pragma once 
#include "DSNode.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
/*
    Heaps : Min and Max Heap 
*/

typedef struct heap_t heap_t;
// create heap indicating if min or max type
heap_t* heap_create_min(size_t capacity);
heap_t* heap_create_max(size_t capacity);
// insert new node
void heap_insert(heap_t* heap,WeightedNode_t new_value);
// pop min or max and replace with new_node
WeightedNode_t heap_extract(heap_t* heap);

// from bottom start comparing with parent if (min or max) 
// and swaping with it if correspond.
void heap_bubble_up(heap_t* heap, int item_index);
// from top to bottom comparing with left child if (min or max) 
// and swaping with it if correspond.
void heap_bubble_down(heap_t* heap,int index);
// return if heap is min type or false if its max type
bool heap_is_min(heap_t* heap);
bool heap_is_empty(heap_t* heap);
void heap_swapItems(WeightedNode_t* a,WeightedNode_t* b);
// get number of items in heap
int heap_get_size(heap_t* heap);

void heap_print(heap_t* heap);
void heap_print_file(heap_t* heap,FILE* file_out);
void heap_consoleTest(bool heap_is_min,const char* input_file,const char* output_file);
