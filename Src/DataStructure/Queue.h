#pragma once
#include <stdlib.h>
#include<stdio.h>
#include <stdbool.h>
#include "Src/node.h"
/*
    Simple Queue (FIFO)
*/
#define INITIAL_CAPACITY 100
typedef struct queue_t
{
    int* data;
    int front;
    int back;
    int size;
    int capacity;
}queue_t;

queue_t* create_queue()
{
    queue_t* q = (queue_t*)malloc(sizeof(queue_t));
    // TODO : check if null
    q->capacity = INITIAL_CAPACITY;
    q->data = malloc(sizeof(int)*INITIAL_CAPACITY);
    // TODO : check if null
    // free q;

    q->front = 0;
    q->back = 0;
    q->size = 0;
    return q;
}

bool queue_is_empty(queue_t* q)
{
    return q->size == 0;
}

void queue_push(queue_t* q, int val)
{
    if(q->size == q->capacity)
    {
        q->capacity *=2;
        int* new_data =(int*)realloc(q->data,sizeof(int) * q->capacity);
        if(new_data == NULL)
        {
            perror("queue_push : realloc failed");
            exit(EXIT_FAILURE);
        }
        if(q->front > q->back)
        {
            for(int i = 0; i < q->back;++i)
            {
                new_data[i+q->size] = new_data[i];
            }
            q->back = q->size;
        }
        q->data = new_data;
    }
    q->data[q->back] = val;
    q->back = (q->back + 1) % q->capacity;
    q->size++;
}

int queue_pop(queue_t* q)
{
    if(queue_is_empty(q)) 
    {
        fprintf(stderr,"queue_pop : queue is empty");
        exit(EXIT_FAILURE);
    }
    int value = q->data[q->front];
    q->front = (q->front +1) % q->capacity;
    q->size--;
    return value;
}

int queue_peek(queue_t* q)
{
    if(queue_is_empty(q))
    {
        fprintf(stderr,"queue_peek : queue is empty");
        exit(EXIT_FAILURE);
    }
    return q->front;
}

void queue_destroy(queue_t* q)
{
    if(q != NULL)
    {
        free(q->data);
        free(q);
    }
}

void queue_test()
{
    printf("Start Queue Test\n");
    queue_t* q = create_queue();

    queue_push(q, 10);
    queue_push(q, 20);
    queue_push(q, 30);

    printf("Queue : Front: %d\n", queue_peek(q)); // 10

    printf("Queue : Dequeued: %d\n", queue_pop(q)); // 10
    printf("Queue : Dequeued: %d\n", queue_pop(q)); // 20

    queue_push(q, 40);

    printf("Queue : Front: %d\n", queue_peek(q)); // 30

    while (!queue_is_empty(q)) {
        printf("Queue : Dequeued: %d\n", queue_pop(q));
    }
    free(q);
}