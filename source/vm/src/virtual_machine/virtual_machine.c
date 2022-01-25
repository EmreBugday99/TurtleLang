#include "virtual_machine.h"
#include <stdio.h>
#include <stdlib.h>
#include "../data_types/stack.h"
#include "../data_types/list.h"
#include "../token/token.h"
#include "../token/token_type.h"


struct virtual_machine
{
	void* token_list;
	size_t token_pointer;
	void* stack;
};

void* vm_create(void)
{
	struct virtual_machine* vm = (struct virtual_machine*)malloc(sizeof(struct virtual_machine));
	if (vm == NULL)
		return NULL;

	vm->token_pointer = 0;
	vm->token_list = list_create(5, token_get_size());
	vm->stack = stack_create(1024);

	return vm;
}

void vm_execute_token(struct virtual_machine* vm, const void* token)
{
	switch (token_get_type(token))
	{
	case TOKEN_NONE:
	{
		printf("Token Type Can't be None!");
		break;
	}
	case TOKEN_PUSH:
	{
		stack_push(vm->stack, token_get_data(token));
		break;
	}
	case TOKEN_ADD:
	{
		stack_pop(vm->stack);
		const vm_data data1 = stack_get_cache(vm->stack);

		stack_pop(vm->stack);
		const vm_data data2 = stack_get_cache(vm->stack);

		stack_push(vm->stack, data1 + data2);
		break;
	}
	case TOKEN_SUBTRACT:
	{
		stack_pop(vm->stack);
		const vm_data data1 = stack_get_cache(vm->stack);

		stack_pop(vm->stack);
		const vm_data data2 = stack_get_cache(vm->stack);

		stack_push(vm->stack, data1 - data2);
		break;
	}
	case TOKEN_MULTIPLICATION:
	{
		stack_pop(vm->stack);
		const vm_data data1 = stack_get_cache(vm->stack);

		stack_pop(vm->stack);
		const vm_data data2 = stack_get_cache(vm->stack);

		stack_push(vm->stack, data1 * data2);
		break;
	}
	case TOKEN_DIVISION:
	{
		stack_pop(vm->stack);
		const vm_data data1 = stack_get_cache(vm->stack);

		stack_pop(vm->stack);
		const vm_data data2 = stack_get_cache(vm->stack);

		stack_push(vm->stack, data1 / data2);
		break;
	}
	case TOKEN_JUMP:
	{
		vm->token_pointer = token_get_data(token);
		break;
	}
	case TOKEN_COMPARE:
	{
		stack_pop(vm->stack);

		if (stack_get_cache(vm->stack) == token_get_data(token))
			stack_push(vm->stack, 1);
		else
			stack_push(vm->stack, 0);
		break;
	}
	case TOKEN_JUMP_COMPARE:
	{
		stack_pop(vm->stack);
		const vm_data data1 = stack_get_cache(vm->stack);

		stack_pop(vm->stack);
		const vm_data data2 = stack_get_cache(vm->stack);

		if (data1 == data2)
			vm->token_pointer = token_get_data(token);

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

	for (vm->token_pointer = 0; vm->token_pointer < list_get_element_count(vm->token_list); vm->token_pointer++)
	{
		vm_execute_token(vm, list_get(vm->token_list ,vm->token_pointer));
	}
}

void vm_dump_stack(const struct virtual_machine* vm)
{
	printf("Stack Dump: \n");

	for (size_t i = 0; i < stack_get_elements(vm->stack); i++)
	{
		printf("%li \n", stack_get_data(vm->stack, i));
	}

	printf("\n");
}

void* vm_get_token_list(const struct virtual_machine* vm)
{
	return vm->token_list;
}

size_t vm_get_token_pointer(const struct virtual_machine* vm)
{
	return vm->token_pointer;
}

void vm_set_token_pointer(struct virtual_machine* vm, const size_t token_pointer)
{
	vm->token_pointer = token_pointer;
}

void* vm_get_stack(const struct virtual_machine* vm)
{
	return vm->stack;
}
