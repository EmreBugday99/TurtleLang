#pragma once
#ifndef STACK_H
#define STACK_H

#include "vm_data.h"
#include "../types.h"

typedef struct
{
	size_t capacity;
	size_t elements;
	vm_data* data_stack;
	vm_data cache1;
} stack;

stack stack_create(size_t capacity);
vm_result stack_push(stack* stack, vm_data data);
vm_result stack_pop(stack* stack);
vm_result stack_peek(stack* stack);
vm_result stack_is_empty(const stack* stack);
vm_result stack_is_full(const stack* stack);

#endif