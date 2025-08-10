#include "Heap.h"
#include "DSNode.h"
#include <stdio.h>
#include <stdlib.h>

struct heap_t
{
    bool is_min_heap;
    size_t capacity;
    size_t size;
    WeightedNode_t* items;
};

void heap_bubble_down(heap_t *heap,int index)
{
    size_t left = 2 * index + 1;
    size_t right = 2 * index +2;
    
    if(heap->is_min_heap)
    {
        int smallest = index;
        if(left < heap->size && &heap->items[left].weight < &heap->items[index].weight)
            smallest = left;
        if(right < heap->size && &heap->items[right].weight < &heap->items[index].weight)
            smallest = right;

        if(smallest != index)
        {
            heap_swapItems(&heap->items[smallest],&heap->items[index]);
            heap_bubble_down(heap,smallest);
        }
    }
    else // is MaxHeap
    {
        int biggest = index;
        if(left < heap->size && &heap->items[left].weight > &heap->items[index].weight)
            biggest = left;
        if(right < heap->size && &heap->items[right].weight > &heap->items[index].weight)
            biggest = right;
        
        if(biggest != index)
        {
            heap_swapItems(&heap->items[biggest],&heap->items[index]);
            heap_bubble_down(heap,biggest);
        }
    }
}

void heap_bubble_up(heap_t *heap, int item_index)
{
    while (item_index != 0)
    {
        int parent = item_index - 1;
        if(heap->is_min_heap)
        {
            if(&heap->items[item_index].weight < &heap->items[parent].weight)
            {
                heap_swapItems(&heap->items[item_index],&heap->items[parent]);
                item_index = parent;
            }
            else break;
            }
        else
        {
            if(&heap->items[item_index].weight > &heap->items[parent].weight)
            {
                heap_swapItems(&heap->items[item_index],&heap->items[parent]);
                item_index = parent;
            }
            else break;
        }
    }
}

bool heap_is_min(heap_t *heap)
{
    return heap->is_min_heap;
}

bool heap_is_empty(heap_t *heap)
{
    return heap->size == 0;
}

void heap_swapItems(void *a, void *b)
{
    void* temp = a;
    a = b;
    b = &temp; 
}

int heap_get_size(heap_t *heap)
{
    return heap->size;
}

heap_t *heap_create_min(size_t capacity)
{
    if(capacity < 2)
    {
        fprintf(stderr,"MinHeap : capacity should be greater than 1");
        return NULL;
    }
    heap_t* new_heap = malloc(sizeof(heap_t));
    if(new_heap == NULL)
    {
        fprintf(stderr,"MinHeap : failed to allocate memory for heap");
        return NULL;
    }
    void* new_items = malloc(sizeof(void*)*capacity);
    if(new_items == NULL)
    {
        fprintf(stderr,"MaxHeap : failed to allocate memory for Data");
        free(new_heap);
        return NULL;
    }
    new_heap->capacity = capacity;
    new_heap->is_min_heap = true;
    new_heap->items = new_items;
    new_heap->size = 0;
    return new_heap;
}

heap_t *heap_create_max(size_t capacity)
{
    if(capacity < 2)
    {
        fprintf(stderr,"MaxHeap : capacity should be greater than 1");
        return NULL;
    }
    heap_t* new_heap = malloc(sizeof(heap_t));
    if(new_heap == NULL)
    {
        fprintf(stderr,"MaxHeap : failed to allocate memory for heap");
        return NULL;
    }
    void* new_items = malloc(sizeof(void*)*capacity);
    if(new_items == NULL)
    {
        fprintf(stderr,"MaxHeap : failed to allocate memory for Data");
        free(new_heap);
        return NULL;
    }
    new_heap->capacity = capacity;
    new_heap->is_min_heap = true;
    new_heap->items = new_items;
    new_heap->size = 0;
    return new_heap;
}

void heap_insert(heap_t *heap, WeightedNode_t new_value)
{
    if(heap->size == heap->capacity)
    {
        fprintf(stderr,"Heap_insert : no place for more items in this heap\n");
        return;
    }
    heap->size++;
    heap->items[heap->size-1] = new_value;
    heap_bubble_up(heap,heap->size-1);
}

WeightedNode_t heap_extract(heap_t *heap)
{
    if(heap_is_empty(heap))
    {
        fprintf(stderr,"heap_remove : heap is empty\n");
        return (WeightedNode_t){0.0,0};
    }
    WeightedNode_t result = heap->items[0];
    heap->items[0] = heap->items[heap->size-1];
    heap->size--;
    heap_bubble_down(heap,0);
    return result;
}

void heap_print(heap_t *heap)
{
    for(size_t i = 0; i < heap->size;++i)
    {
        printf("(%f, %d) ", heap->items[i].weight, heap->items[i].data);
    }
    printf("\n");
}

void heap_consoleTest(bool heap_is_min)
{
    heap_t* current_heap;
    if(heap_is_min)
    {
        current_heap = heap_create_min(10);
    }
    else
    {
        current_heap = heap_create_min(10);
    }
    
        heap_insert(current_heap, (WeightedNode_t){0.1, 10});
        heap_insert(current_heap, (WeightedNode_t){0.4, 30});
        heap_insert(current_heap, (WeightedNode_t){1.0, 100});
        heap_insert(current_heap, (WeightedNode_t){0.2, 20});

        printf("Heap is %s: ",(heap_is_min)?"Min":"Max");
        heap_print(current_heap);

        WeightedNode_t curr_node = heap_extract(current_heap);
        printf("Extracted Node: (%f, %d)\n", curr_node.weight, curr_node.data);

        printf("Heap after extraction: ");
        heap_print(current_heap);

        free(current_heap->items);
        free(current_heap);
}