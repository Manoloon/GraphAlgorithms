#pragma once
#include <stddef.h>
#include <stdbool.h>
/*
    Simple Queue (FIFO)
*/

typedef struct queue_t queue_t;

// Optional : user-supplied destructor function
typedef void (*queue_free_func)(void**);

queue_t* queue_create(size_t capacity);
void queue_destroy(queue_t* q);

// set destructor for queue_destroy
void queue_set_free_func(queue_t* q,queue_free_func func);

inline bool queue_is_empty(const queue_t* q);

void queue_push(queue_t* q, void* val);
void* queue_pop(queue_t* q);
void* queue_peek(queue_t* q);

void queue_test();