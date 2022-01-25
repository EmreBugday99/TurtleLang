#pragma once
#include "vm_types.h"

struct stack
{
	size_t capacity;
	size_t elements;
	vm_data cached_data;
	vm_data data_stack[];
};

struct stack* stack_create(size_t capacity);
unsigned char stack_push(struct stack* stack, vm_data data);
unsigned char stack_pop(struct stack* stack);
unsigned char stack_peek(struct stack* stack);
unsigned char stack_is_empty(const struct stack* stack);
unsigned char stack_is_full(const struct stack* stack);