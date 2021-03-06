#include "stack.h"
#include <stdlib.h>
#include "../result.h"

struct stack
{
	size_t capacity;
	size_t elements;
	vm_data cache;
	vm_data data_stack[];
};

void* stack_create(const size_t capacity)
{
	const size_t allocation_size = sizeof(struct stack) + (capacity * sizeof(vm_data));
	struct stack* new_stack = malloc(allocation_size);
	if (new_stack == 0)
		return 0;

	new_stack->capacity = capacity;
	new_stack->elements = 0;
	new_stack->cache = 0;
	for (size_t i = 0; i < new_stack->capacity; i++)
	{
		new_stack->data_stack[i] = 0;
	}

	return new_stack;
}

result stack_push(struct stack* stack, const vm_data data)
{
	if (stack_is_full(stack) == 1)
		return RESULT_FALSE;

	stack->data_stack[stack->elements++] = data;
	return RESULT_TRUE;
}

result stack_pop(struct stack* stack)
{
	if (stack_is_empty(stack) == 1)
		return RESULT_FALSE;

	stack->cache = stack->data_stack[stack->elements - 1];
	stack->elements--;

	return RESULT_TRUE;
}

result stack_peek(struct stack* stack)
{
	if (stack_is_empty(stack) == 1)
		return RESULT_FALSE;

	stack->cache = stack->data_stack[stack->elements - 1];

	return RESULT_TRUE;
}

result stack_is_empty(const struct stack* stack)
{
	if (stack->elements == 0)
		return RESULT_TRUE;

	return RESULT_FALSE;
}

unsigned char stack_is_full(const struct stack* stack)
{
	if (stack->elements >= stack->capacity)
		return RESULT_TRUE;

	return RESULT_FALSE;
}

size_t stack_get_capacity(const struct stack* stack)
{
	return stack->capacity;
}

size_t stack_get_elements(const struct stack* stack)
{
	return stack->elements;
}

vm_data stack_get_cache(const struct stack* stack)
{
	return stack->cache;
}

void stack_set_cache(struct stack* stack, const vm_data data)
{
	stack->cache = data;
}

vm_data stack_get_data(const struct stack* stack, const size_t index)
{
	return stack->data_stack[index];
}

void stack_delete(struct stack* stack)
{
	free(stack);
	stack = NULL;
}
