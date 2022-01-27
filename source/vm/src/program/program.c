#include "program.h"
#include <stdlib.h>

#include "instruction.h"
#include "instruction_callback_type.h"
#include "../data_types/list.h"
#include "../data_types/stack.h"
#include "../data_types/map.h"
#include "../token/token_type.h"
#include "../instruction_callbacks/instruction_callback_none.h"

struct program
{
	void* instruction_list;
	void* stack;
	void* vm;
	void* instruction_map;
	uint64_t instruction_pointer;
};

void* program_create(void* vm)
{
	struct program* new_program = malloc(sizeof(struct program));
	if (new_program == NULL)
		return NULL;

	new_program->instruction_list = list_create(4, sizeof(instruction_get_size()));
	new_program->stack = stack_create(1024);
	new_program->vm = vm;
	new_program->instruction_map = map_create(4, sizeof(instruction_callback));
	new_program->instruction_pointer = 0;

	return new_program;
}

void* program_get_instruction_list(const struct program* program)
{
	if (program == NULL)
		return NULL;

	return program->instruction_list;
}

void* program_get_stack(const struct program* program)
{
	if (program == NULL)
		return NULL;

	return program->stack;
}

void* program_get_vm(const struct program* program)
{
	return program->vm;
}

uint64_t program_get_instruction_pointer(struct program* program)
{
	return program->instruction_pointer;
}

void program_set_instruction_pointer(struct program* program, uint64_t instruction_pointer)
{
	program->instruction_pointer = instruction_pointer;
}

result program_delete(struct program* program)
{
	if (program == NULL)
		return RESULT_FALSE;

	list_destroy(program->instruction_list);
	stack_delete(program->stack);

	program->instruction_list = NULL;
	program->stack = NULL;
	program->vm = NULL;

	return RESULT_TRUE;
}

result program_insert_standard_instructions(struct program* program)
{
	if (program == NULL)
		return RESULT_FALSE;

	map_add(program->instruction_map, TOKEN_NONE, );
	map_add(program->instruction_map, TOKEN_PUSH, 0);
	map_add(program->instruction_map, TOKEN_POP, 0);
	map_add(program->instruction_map, TOKEN_ADD, 0);
	map_add(program->instruction_map, TOKEN_SUBTRACT, 0);
	map_add(program->instruction_map, TOKEN_MULTIPLICATION, 0);
	map_add(program->instruction_map, TOKEN_DIVISION, 0);
	map_add(program->instruction_map, TOKEN_JUMP, 0);
	map_add(program->instruction_map, TOKEN_COMPARE, 0);
	map_add(program->instruction_map, TOKEN_JUMP_COMPARE, 0);

	return RESULT_TRUE;
}