#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Src/node.h"
/*
Stack (LIFO)
*/
#define MAX_NAME_CHAR 20


typedef struct stack_t
{
    int size;
    int top;
    node_t* items;
}stack_t;

stack_t* create_stack(int capacity)
{
    stack_t* s = (stack_t*)malloc(sizeof(stack_t));
    s->size = capacity;
    s->top = -1;
    s->items = (node_t*)malloc(sizeof(node_t)* capacity);
    return s;
}

int stack_peek(stack_t* stack)
{
    if(stack->top == -1) return -1;
    return stack->items[stack->top].data;
}
void push(stack_t* stack,node_t* item)
{
    if(stack->top == stack->size -1)
    {
        stack->size *= 2;
        stack->items = (node_t*)realloc(stack->items, sizeof(node_t)*stack->size);
        if(!stack->items)
        {
            fprintf(stderr, "Memory allocation failed for stack expansion");
            exit(EXIT_FAILURE);
        }
    }
    stack->top +=1;
    stack->items[stack->top] = *item;
}

node_t pop(stack_t* stack)
{
    node_t result = {.data = -1};

    if(stack->top >= 0)
    {
        result = stack->items[stack->top];
        stack->top--;
    }
    return result;
}

bool stack_is_empty(stack_t* s)
{
    return s->top == -1;
}

void destroy_stack(stack_t* stack)
{
    free(stack->items);
    stack->items = NULL;
    stack->size = 0;
    stack->top = -1;
}

void stack_test()
{
    printf("Stack \n");
    stack_t* s = create_stack(3);
    node_t node1 = {.data = 10};
    node_t node2 = {.data = 20};
    node_t node3 = {.data = 30};
    node_t node4 = {.data = 40};
    push(s, &node1);
    printf("stack : Push: %d\n", stack_peek(s)); // 10
    push(s, &node2);
    printf("stack : Push: %d\n", stack_peek(s)); // 10
    push(s, &node3);
    printf("stack : Push: %d\n", stack_peek(s)); // 10    

    printf("stack pop: %d\n", pop(s).data); // 10
    printf("stack pop: %d\n", pop(s).data); // 20

    push(s, &node4);
    printf("stack : Push: %d\n", stack_peek(s)); // 30

    while (!stack_is_empty(s)) {
        printf("stack pop: %d\n", pop(s).data);
    }
    destroy_stack(s);
}