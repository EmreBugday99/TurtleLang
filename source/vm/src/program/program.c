#include "program.h"
#include <stdlib.h>
#include "instruction_callback_type.h"
#include "../data_types/list.h"
#include "../data_types/stack.h"

struct program
{
	void* instruction_list;
	void* stack;
	void* vm;
};

void* program_create(void* vm)
{
	struct program* new_program = malloc(sizeof(struct program));
	if (new_program == NULL)
		return NULL;

	new_program->instruction_list = list_create(4, sizeof(instruction_callback));
	new_program->stack = stack_create(1024);
	new_program->vm = vm;

	return new_program;
}

void* program_get_instruction_list(const struct program* program)
{
	return program->instruction_list;
}

void* program_get_stack(const struct program* program)
{
	return program->stack;
}

void* program_get_vm(const struct program* program)
{
	return program->vm;
}

void program_delete(struct program* program)
{
	list_destroy(program->instruction_list);
	stack_delete(program->stack);

	program->instruction_list = NULL;
	program->stack = NULL;
	program->vm = NULL;
}