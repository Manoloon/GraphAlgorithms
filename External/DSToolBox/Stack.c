#include "Stack.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CAPACITY 100

struct stack_t
{
    size_t size;
    size_t top;
    void** items;
};

stack_t *stack_create(int capacity) 
{ 
    if(capacity < 1) capacity = MAX_CAPACITY;
    stack_t* s = malloc(sizeof(stack_t));
    if(s == NULL)
    {
        fprintf(stderr,"stack_create : failed to alloc memory \n");
        return NULL;
    }
    s->items = malloc(sizeof(void*) * capacity);
    if(s->items == NULL)
    {
        fprintf(stderr,"stack_create : failed to alloc memory for items\n");
        free(s);
        return NULL;
    }
    s->size = capacity;
    s->top = 0;
    return s;
}

void *stack_peek(stack_t *stack) 
{ 
    if(stack->top == 0) return NULL;
    stack->top--;
    return stack->items[stack->top];
}

void *stack_pop(stack_t *stack) 
{ 
    if(stack_is_empty(stack)) return NULL;
    return stack->items[stack->top--];
}

bool stack_is_empty(const stack_t *s) 
{ 
    return s->top == 0;
}

void stack_destroy(stack_t *stack) 
{
    if(stack)
    {
        free(stack->items);
        free(stack);
    }
}

void stack_push(stack_t *stack, void *item) 
{
    if(stack->top == stack->size)
    {
        size_t new_size = stack->size * 2;
        void** new_items = realloc(stack->items, sizeof(void*)*new_size);
        if(!stack->items)
        {
            fprintf(stderr, "stack_push : Memory allocation failed for stack expansion\n");
            return;
        }
        stack->items = new_items;
        stack->size = new_size;
    }
    stack->top++;
    stack->items[stack->top] = item;
}

void stack_test() 
{
    printf("Stack \n");
    stack_t* s = stack_create(3);
    int node1 = 10;
    int node2 = 20;
    int node3 = 30;
    int node4 = 40;
    stack_push(s, &node1);
    printf("stack : Push: %d\n", *(int*)stack_peek(s)); // 10
    stack_push(s, &node2);
    printf("stack : Push: %d\n", *(int*)stack_peek(s)); // 10
    stack_push(s, &node3);
    printf("stack : Push: %d\n", *(int*)stack_peek(s)); // 10    

    printf("stack pop: %d\n", *(int*)stack_pop(s)); // 10
    printf("stack pop: %d\n", *(int*)stack_pop(s)); // 20

    stack_push(s, &node4);
    printf("stack : Push: %d\n", *(int*)stack_peek(s)); // 30

    while (!stack_is_empty(s)) {
        printf("stack pop: %d\n", *(int*)stack_pop(s));
    }
    stack_destroy(s);
}