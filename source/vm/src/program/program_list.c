#include "program_list.h"

#include <stdlib.h>

program_list program_list_create(unsigned char capacity)
{
	return (program_list) {
		.list = (program*)malloc(capacity * sizeof(program)),
			.elements = 0,
			.capacity = capacity
	};
}

vm_result program_list_add_new_program(program_list* programs, virtual_machine* vm, size_t stack_size)
{
	if (programs->elements == programs->capacity)
		return VM_RESULT_FAIL;

	programs->list[programs->elements].host = vm;
	programs->list[programs->elements].instructions = 0;
	programs->list[programs->elements].instruction_pointer = 0;
	programs->list[programs->elements].program_id = programs->elements;
	programs->list[programs->elements].program_stack = stack_create(stack_size);

	programs->elements++;

	return VM_RESULT_SUCCESS;
}

vm_result program_list_remove(program_list* programs, unsigned char index)
{
	if (index > programs->elements)
		return VM_RESULT_FAIL;

	free(programs->list[index].program_stack.data_stack);
	free(programs->list[index].instructions);

	programs->list[index].program_stack.data_stack = 0;
	programs->list[index].instructions = 0;
	programs->list[index].host = 0;
	programs->list[index].program_id = 0;

	for (unsigned char i = index; i < programs->elements - 1; i++)
	{
		programs->list[i] = programs->list[i + 1];
	}

	programs->elements--;

	return VM_RESULT_SUCCESS;
}