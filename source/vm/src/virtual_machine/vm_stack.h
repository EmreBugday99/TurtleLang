#pragma once
#include "vm_types.h"

typedef struct
{
	size_t capacity;
	size_t elements;
	vm_data* data_stack;
	vm_data cached_data;
} vm_stack;

vm_stack vm_stack_create(size_t capacity);
unsigned char vm_stack_push(vm_stack* stack, vm_data data);
unsigned char vm_stack_pop(vm_stack* stack);
unsigned char vm_stack_peek(vm_stack* stack);
unsigned char vm_stack_is_empty(const vm_stack* stack);
unsigned char vm_stack_is_full(const vm_stack* stack);