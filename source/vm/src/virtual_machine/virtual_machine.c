#include "virtual_machine.h"
#include <stdio.h>
#include <stdlib.h>

virtual_machine* vm_create(void)
{
	virtual_machine* vm = (virtual_machine*)malloc(sizeof(virtual_machine));
	if (vm == NULL)
		return NULL;

	vm->programs = program_list_create(1);
	vm->stack = stack_create(100);

	return vm;
}

void vm_start(virtual_machine* vm)
{
	for (size_t i = 0; i < vm->programs.list[0].instruction_count; i++)
	{
		vm->programs.list[0].instructions[i].callback(vm->programs.list[0], vm->programs.list[0].instructions[i].data);
	}
}

void vm_load_program(virtual_machine* vm, token_list* tokens, instruction_map* instructions, size_t stack_size)
{
	if (program_list_add_new_program(vm->programs, vm, stack_size) == VM_RESULT_FAIL)
	{
		vm_on_error(vm, "Failed to load program");
		return;
	}

	program_install_instructions(vm->programs.list[vm->programs.elements], tokens, instructions);

	free(tokens->list);
	tokens->list = 0;
}

void vm_dump_stack(const virtual_machine* vm)
{
	printf("Stack Dump: \n");

	for (size_t i = 0; i < vm->stack.elements; i++)
	{
		printf("%lld \n", vm->stack.data_stack[i]);
	}

	printf("\n");
}

void vm_on_error(virtual_machine* vm, const char* error_message)
{
	printf("---Error Message Start--- \n");
	printf("%s", error_message);
	printf("---Error Message End--- \n \n");
	printf("---Error Time Stack Dump--- \n");
	vm_dump_stack(vm);
}