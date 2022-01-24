#include "stack.h"
#include <stdlib.h>

stack stack_create(size_t capacity)
{
	return (stack) {
		.capacity = capacity,
		.elements = 0,
		.cache1 = 0,
		.data_stack = (vm_data*)malloc(capacity * sizeof(vm_data))
	};
}

vm_result stack_push(stack* stack, const vm_data data)
{
	if (stack_is_full(stack) == VM_RESULT_SUCCESS)
		return VM_RESULT_FAIL;

	stack->data_stack[stack->elements++] = data;
	return VM_RESULT_SUCCESS;
}

vm_result stack_pop(stack* stack)
{
	if (stack_is_empty(stack) == VM_RESULT_SUCCESS)
		return VM_RESULT_FAIL;

	stack->cache1 = stack->data_stack[stack->elements - 1];
	stack->elements--;

	return VM_RESULT_SUCCESS;
}

vm_result stack_peek(stack* stack)
{
	if (stack_is_empty(stack) == VM_RESULT_SUCCESS)
		return VM_RESULT_FAIL;

	stack->cache1 = stack->data_stack[stack->elements - 1];

	return VM_RESULT_SUCCESS;
}

vm_result stack_is_empty(const stack* stack)
{
	if (stack->elements == 0)
		return VM_RESULT_SUCCESS;

	return VM_RESULT_FAIL;
}

vm_result stack_is_full(const stack* stack)
{
	if (stack->elements == stack->capacity)
		return VM_RESULT_SUCCESS;

	return VM_RESULT_FAIL;
}