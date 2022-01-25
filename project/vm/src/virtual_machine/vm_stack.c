#include "vm_stack.h"
#include <stdlib.h>

vm_stack vm_stack_create(size_t capacity)
{
	return (vm_stack) {
		.capacity = capacity,
			.elements = 0,
			.cached_data = 0,
			.data_stack = (vm_data*)malloc(capacity * sizeof(vm_data))
	};
}

unsigned char vm_stack_push(vm_stack* stack, const vm_data data)
{
	if (vm_stack_is_full(stack) == 1)
		return 0;

	stack->data_stack[stack->elements++] = data;
	return 1;
}

unsigned char vm_stack_pop(vm_stack* stack)
{
	if (vm_stack_is_empty(stack) == 1)
		return 0;

	stack->cached_data = stack->data_stack[stack->elements - 1];
	stack->elements--;

	return 1;
}

unsigned char vm_stack_peek(vm_stack* stack)
{
	if (vm_stack_is_empty(stack) == 1)
		return 0;

	stack->cached_data = stack->data_stack[stack->elements - 1];

	return 1;
}

unsigned char vm_stack_is_empty(const vm_stack* stack)
{
	return stack->elements == 0;
}

unsigned char vm_stack_is_full(const vm_stack* stack)
{
	return stack->elements == stack->capacity;
}