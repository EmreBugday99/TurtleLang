#include "stack.h"
#include <stdlib.h>

struct stack* stack_create(const size_t capacity)
{
	const size_t allocation_size = sizeof(struct stack) + (capacity * sizeof(vm_data));
	struct stack* new_stack = malloc(allocation_size);
	if (new_stack == 0)
		return 0;

	new_stack->capacity = capacity;
	new_stack->elements = 0;
	new_stack->cached_data = 0;
	for (size_t i = 0; i < new_stack->capacity; i++)
	{
		new_stack->data_stack[i] = 0;
	}

	return new_stack;
}

unsigned char stack_push(struct stack* stack, const vm_data data)
{
	if (stack_is_full(stack) == 1)
		return 0;

	stack->data_stack[stack->elements++] = data;
	return 1;
}

unsigned char stack_pop(struct stack* stack)
{
	if (stack_is_empty(stack) == 1)
		return 0;

	stack->cached_data = stack->data_stack[stack->elements - 1];
	stack->elements--;

	return 1;
}

unsigned char stack_peek(struct stack* stack)
{
	if (stack_is_empty(stack) == 1)
		return 0;

	stack->cached_data = stack->data_stack[stack->elements - 1];

	return 1;
}

unsigned char stack_is_empty(const struct stack* stack)
{
	return stack->elements == 0;
}

unsigned char stack_is_full(const struct stack* stack)
{
	return stack->elements == stack->capacity;
}