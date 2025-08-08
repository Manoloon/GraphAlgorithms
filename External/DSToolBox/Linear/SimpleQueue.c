#include "SimpleQueue.h"
#include <stdlib.h>
#include<stdio.h>

#define INITIAL_CAPACITY 100
struct queue_t
{
    void** data;
    size_t front;
    size_t back;
    size_t size;
    size_t capacity;
    queue_free_func free_func;
};

queue_t *queue_create(size_t capacity) 
{ 
    if(capacity < 1) capacity = INITIAL_CAPACITY;
    queue_t* q = malloc(sizeof(queue_t));
    if(q == NULL)
    {
        fprintf(stderr,"Create queue dynamic : failed to allocate memory for Queue\n");
        return NULL;
    }
    q->capacity = capacity;
    q->data = malloc(sizeof(void*) * capacity);
    if(q->data == NULL)
    {
        fprintf(stderr,"Create queue dynamic: failed to allocate memory for data\n");
        free(q);
        return NULL;
    }
    q->front = 0;
    q->back = 0;
    q->size = 0;
    q->free_func = NULL;
    return q;
}

queue_t *queue_create_fixed() 
{ 
    queue_t* q = malloc(sizeof(queue_t));
    if(q == NULL)
    {
        fprintf(stderr,"Create queue : failed to allocate memory for Queue\n");
        return NULL;
    }
    q->capacity = INITIAL_CAPACITY;
    q->data = malloc(sizeof(void*)*INITIAL_CAPACITY);
    if(q->data == NULL)
    {
        fprintf(stderr,"Create queue : failed to allocate memory for data\n");
        free(q);
        return NULL;
    }
    q->front = 0;
    q->back = 0;
    q->size = 0;
    return q;
}

void queue_set_free_func(queue_t *q, queue_free_func func) 
{
    if(q)
    {
        q->free_func = func;
    }
}

bool queue_is_empty(const queue_t *q) 
{ 
    return q->size == 0; 
}

void queue_push(queue_t *q, void* val) {
  if (q->size == q->capacity) 
  {
    size_t new_capacity = q->capacity * 2;
    void** new_data = realloc(q->data, sizeof(void*) * new_capacity);
    if (new_data == NULL) {
      fprintf(stderr, "queue_push : realloc failed\n");
      return;
    }
    if (q->front > q->back) {
      for (size_t i = 0; i < q->back; ++i) 
      {
        new_data[i + q->capacity] = new_data[i];
      }
      q->back = q->capacity;
    }
    q->data = new_data;
    q->capacity = new_capacity;
  }
  q->data[q->back] = val;
  q->back = (q->back + 1) % q->capacity;
  q->size++;
}

void* queue_pop(queue_t *q) 
{ 
    if(queue_is_empty(q)) 
    {
        fprintf(stderr,"queue_pop : queue is empty");
        return NULL;
    }
    void* value = q->data[q->front];
    q->front = (q->front +1) % q->capacity;
    q->size--;
    return value;
}

void* queue_peek(queue_t *q) 
{ 
    if(queue_is_empty(q))
    {
        fprintf(stderr,"queue_peek : queue is empty");
        return NULL;
    }
    return q->data[q->front];
}

void queue_destroy(queue_t *q) 
{
    if(q != NULL)
    {
        if(q->free_func)
        {
            for(size_t i = 0; i < q->size;++i)
            {
                size_t index = (q->front +i) % q->capacity;
                q->free_func(q->data[index]);
            }
        }
        free(q->data);
        free(q);
    }
}

void queue_test() 
{
    printf("Start Queue Test\n");
    // this func should be out of main
    /*
    void free_str(void* str)
    {
        free(str);
    }
    */
    queue_t* q = queue_create(10);
    //queue_free_func(q,free_str);
    int val1 = 10;
    int val2 = 20;
    int val3 = 30;
    int val4 = 40;
    queue_push(q, &val1);
    queue_push(q, &val2);
    queue_push(q, &val3);

    printf("Queue : Front: %d\n",*(int*)queue_peek(q)); // 10

    printf("Queue : Dequeued: %d\n", *(int*)queue_pop(q)); // 10
    printf("Queue : Dequeued: %d\n", *(int*)queue_pop(q)); // 20

    queue_push(q, &val4);

    printf("Queue : Front: %d\n", *(int*)queue_peek(q)); // 30

    while (!queue_is_empty(q)) {
        printf("Queue : Dequeued: %d\n", *(int*)queue_pop(q));
        // if using free_func
        // free(str);
    }
    queue_destroy(q);
}