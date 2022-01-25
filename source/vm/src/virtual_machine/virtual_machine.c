#include "virtual_machine.h"
#include <stdio.h>
#include <stdlib.h>
#include "vm_types.h"

struct virtual_machine* vm_create(void)
{
	struct virtual_machine* vm = (struct virtual_machine*)malloc(sizeof(struct virtual_machine));

	vm->token_pointer = 0;
	vm->token_list = token_list_create(0);
	vm->stack = stack_create(1024);

	return vm;
}

void vm_execute_token(struct virtual_machine* vm, token vm_token)
{
	switch (vm_token.type)
	{
	case TOKEN_NONE:
	{
		printf("Token Type Can't be None!");
		break;
	}
	case TOKEN_PUSH:
	{
		stack_push(vm->stack, vm_token.data);
		break;
	}
	case TOKEN_ADD:
	{
		stack_pop(vm->stack);
		const vm_data data1 = vm->stack->cached_data;

		stack_pop(vm->stack);
		const vm_data data2 = vm->stack->cached_data;

		stack_push(vm->stack, data1 + data2);
		break;
	}
	case TOKEN_SUBTRACT:
	{
		stack_pop(vm->stack);
		const vm_data data1 = vm->stack->cached_data;

		stack_pop(vm->stack);
		const vm_data data2 = vm->stack->cached_data;

		stack_push(vm->stack, data1 - data2);
		break;
	}
	case TOKEN_MULTIPLICATION:
	{
		stack_pop(vm->stack);
		const vm_data data1 = vm->stack->cached_data;

		stack_pop(vm->stack);
		const vm_data data2 = vm->stack->cached_data;

		stack_push(vm->stack, data1 * data2);
		break;
	}
	case TOKEN_DIVISION:
	{
		stack_pop(vm->stack);
		const vm_data data1 = vm->stack->cached_data;

		stack_pop(vm->stack);
		const vm_data data2 = vm->stack->cached_data;

		stack_push(vm->stack, data1 / data2);
		break;
	}
	case TOKEN_JUMP:
	{
		vm->token_pointer = vm_token.data;
		break;
	}
	case TOKEN_COMPARE:
	{
		stack_pop(vm->stack);

		if (vm->stack->cached_data == vm_token.data)
			stack_push(vm->stack, 1);
		else
			stack_push(vm->stack, 0);
		break;
	}
	case TOKEN_JUMP_COMPARE:
	{
		stack_pop(vm->stack);
		const vm_data data1 = vm->stack->cached_data;

		stack_pop(vm->stack);
		const vm_data data2 = vm->stack->cached_data;

		if (data1 == data2)
			vm->token_pointer = vm_token.data;

		break;
	}
	default:
	{
		printf("Not a valid Token Type");
		break;
	}
	}

#ifdef TURTLE_DEBUG
	vm_dump_stack(vm);
#endif // TURTLE_DEBUG
}

void vm_start(struct virtual_machine* vm)
{
	vm->token_pointer = 0;

	for (vm->token_pointer = 0; vm->token_pointer < vm->token_list.elements; vm->token_pointer++)
	{
		vm_execute_token(vm, vm->token_list.tokens[vm->token_pointer]);
	}
}

void vm_dump_stack(const struct virtual_machine* vm)
{
	printf("Stack Dump: \n");

	for (size_t i = 0; i < vm->stack->elements; i++)
	{
		printf("%lld \n", vm->stack->data_stack[i]);
	}

	printf("\n");
}