#pragma once
#include <stdbool.h>
/*
Stack (LIFO)
*/

typedef struct stack_t stack_t;

stack_t* stack_create(int capacity);

void* stack_peek(stack_t* stack);

void stack_push(stack_t* stack,void* item);

void* stack_pop(stack_t* stack);

bool stack_is_empty(const stack_t* s);

void stack_destroy(stack_t* stack);

void stack_test();