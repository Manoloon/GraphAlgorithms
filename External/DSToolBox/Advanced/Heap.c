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
    size_t left = index + 1;
    size_t right = index +2;
    
    if(heap->is_min_heap)
    {
        int smallest = index;
        if(left < heap->size && heap->items[left].weight < heap->items[smallest].weight)
            smallest = left;
        if(right < heap->size && heap->items[right].weight < heap->items[smallest].weight)
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
        if(left < heap->size && heap->items[left].weight > heap->items[biggest].weight)
            biggest = left;
        if(right < heap->size && heap->items[right].weight > heap->items[biggest].weight)
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
    if(heap->is_min_heap)
    {
        while (item_index > 0)
        {
            int parent = (item_index - 1);
            if(heap->items[item_index].weight < heap->items[parent].weight)
            {
                heap_swapItems(&heap->items[item_index],&heap->items[parent]);
                item_index = parent;
            }
            else break;
        }
    }
    else
    {
        while (item_index > 0)
        {
            int parent = (item_index - 1);
            if(heap->items[item_index].weight > heap->items[parent].weight)
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

void heap_swapItems(WeightedNode_t* a, WeightedNode_t* b)
{
    WeightedNode_t temp = *a;
    *a = *b;
    *b = temp; 
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
    void* new_items = malloc(sizeof(WeightedNode_t)*capacity);
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
    void* new_items = malloc(sizeof(WeightedNode_t)*capacity);
    if(new_items == NULL)
    {
        fprintf(stderr,"MaxHeap : failed to allocate memory for Data");
        free(new_heap);
        return NULL;
    }
    new_heap->capacity = capacity;
    new_heap->is_min_heap = false;
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
    heap->items[heap->size] = new_value;
    heap->size++;  
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
        printf("(%.g, %d) ", heap->items[i].weight, heap->items[i].data);
    }
    printf("\n");
}

void heap_print_file(heap_t *heap, FILE *file_out)
{
    for(size_t i = 0; i < heap->size;++i)
    {
        fprintf(file_out,"(%.1f,%d) ",heap->items[i].weight,heap->items[i].data);
    }
    fprintf(file_out,"\n");
}

void heap_consoleTest(bool heap_is_min,const char* input_file,const char* output_file)
{
    FILE* file_in = fopen(input_file,"r");
    FILE* file_out = fopen(output_file,"w");

    if(!file_in || !file_out)
    {
        perror("file open failed");
        if(file_in) fclose(file_in);
        if(file_out) fclose(file_out);
        return;
    }
    char buffer[256]; // one line
    int capacity = 0;
    while(fgets(buffer,sizeof(buffer),file_in))
    {
        capacity++;
    }
    if(capacity < 1)
    {
        perror("no data to parse");
        fclose(file_in);
        fclose(file_out);
        return;
    }
    // reset file pointer so we can read it again
    rewind(file_in);
    printf("Capacity is: %d\n",capacity);
    heap_t* current_heap;
    if(heap_is_min)
    {
        printf("Creating Min heap\n");
        current_heap = heap_create_min(capacity);
    }
    else
    {
        printf("Creating Max heap\n");
        current_heap = heap_create_max(capacity);
    }
    // get data from file into nodes
    float weight;
    int data;
    while(fscanf(file_in,"%f %d",&weight,&data)==2)
    {
        printf("scanning file : w: %f, d: %d\n",weight,data);
        heap_insert(current_heap,(WeightedNode_t){weight,data});
    }

    printf("Heap is %s: ",(heap_is_min)?"Min\n":"Max\n");
    heap_print(current_heap);
    
    WeightedNode_t curr_node = heap_extract(current_heap);
    printf("Extracted Node: (%.g, %d)\n", curr_node.weight, curr_node.data);
    printf("Heap after extraction: ");
    heap_print(current_heap);
    
    WeightedNode_t curr_node2 = heap_extract(current_heap);
    printf("Extracted Node: (%.g, %d)\n", curr_node2.weight, curr_node2.data);
    printf("Heap after extraction: ");
    heap_print(current_heap);
    heap_print_file(current_heap,file_out);

    fclose(file_in);
    fclose(file_out);

    free(current_heap->items);
    free(current_heap);
}