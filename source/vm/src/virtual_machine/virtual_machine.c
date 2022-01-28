#include "virtual_machine.h"
#include <stdlib.h>
#include "../data_types/stack.h"
#include "../data_types/list.h"
#include "../program/program.h"

struct virtual_machine
{
	void* program_list;
};

void* vm_create(void)
{
	struct virtual_machine* vm = (struct virtual_machine*)malloc(sizeof(struct virtual_machine));
	if (vm == NULL)
		return NULL;

	vm->program_list = list_create(4, program_get_size());

	return vm;
}

result vm_start(struct virtual_machine* vm)
{
	if (list_get_element_count(vm->program_list) <= 0)
		return RESULT_FALSE;

	program_start(list_get_unsafe(vm->program_list, 0));

	return RESULT_TRUE;
}

void* vm_get_program_list(struct virtual_machine* vm)
{
	return vm->program_list;
}
