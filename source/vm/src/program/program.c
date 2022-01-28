#include "program.h"

#include <stdio.h>
#include <stdlib.h>
#include "instruction.h"
#include "instruction_callback_type.h"
#include "../data_types/list.h"
#include "../data_types/stack.h"
#include "../data_types/map.h"
#include "../token/token_type.h"

#include "../instruction_callbacks/instruction_callback_none.h"
#include "../instruction_callbacks/instruction_callback_stack_push.h"
#include "../instruction_callbacks/instruction_callback_stack_pop.h"
#include "../instruction_callbacks/instruction_callback_stack_add.h"
#include "../instruction_callbacks/instruction_callback_stack_subtract.h"
#include "../instruction_callbacks/instruction_callback_stack_multiplication.h"
#include "../instruction_callbacks/instruction_callback_stack_division.h"
#include "../instruction_callbacks/instruction_callback_jump.h"
#include "../instruction_callbacks/instruction_callback_stack_jump_compare.h"
#include "../instruction_callbacks/instruction_callback_stack_compare.h"
#include "../token/token.h"

struct program
{
	void* instruction_list;
	void* stack;
	void* vm;
	void* instruction_map;
	uint64_t instruction_pointer;
};

#ifdef TURTLE_OS_WINDOWS
#pragma pack(push, 1)
struct callback
{
	instruction_callback callback;
};
#pragma pack(pop)
#endif

#ifdef TURTLE_OS_LINUX
struct callback
{
	instruction_callback callback;
}__attribute__((packed));
#endif

void* program_create(void* vm)
{
	struct program* new_program = malloc(sizeof(struct program));
	if (new_program == NULL)
		return NULL;

	new_program->instruction_list = list_create(20, sizeof(instruction_get_size()));
	new_program->stack = stack_create(1024);
	new_program->vm = vm;
	new_program->instruction_map = map_create(20, sizeof(struct callback));
	new_program->instruction_pointer = 0;

	return new_program;
}

result program_start(struct program* program)
{
	if (list_get_element_count(program->instruction_list) <= 0)
		return RESULT_FALSE;

	program->instruction_pointer = 0;
	uint64_t instruction_count = list_get_element_count(program->instruction_list);
	while (program->instruction_pointer < instruction_count)
	{
		const uint8_t type = instruction_get_type(list_get_unsafe(program->instruction_list, program->instruction_pointer));
		const vm_data data = instruction_get_data(list_get_unsafe(program->instruction_list, program->instruction_pointer));

		const instruction_callback callback = program_get_callback_from_instruction_map(program, type);

		callback(program, data);
		program_dump_stack(program);
		program->instruction_pointer++;
	}

	return RESULT_TRUE;
}

void* program_get_instruction_list(const struct program* program)
{
	if (program == NULL)
		return NULL;

	return program->instruction_list;
}

void program_add_instruction_with_token(struct program* program, void* token)
{
	const uint8_t token_type = token_get_type(token);
	const vm_data data = token_get_data(token);
	void* instruction = instruction_create(token_type, data);

	list_add(program->instruction_list, instruction);

	free(instruction);
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

result program_insert_standard_instructions_to_instruction_map(struct program* program)
{
	if (program == NULL)
		return RESULT_FALSE;

	struct callback inst_stack_none = { &instruction_callback_none };
	struct callback inst_stack_push = { &instruction_callback_stack_push };
	struct callback inst_stack_pop = { &instruction_callback_stack_pop };
	struct callback inst_stack_add = { &instruction_callback_stack_add };
	struct callback inst_stack_subtract = { &instruction_callback_stack_subtract };
	struct callback inst_stack_multiply = { &instruction_callback_stack_multiplication };
	struct callback inst_stack_divide = { &instruction_callback_stack_division };
	struct callback inst_jump = { &instruction_callback_jump };
	struct callback inst_stack_compare = { &instruction_callback_stack_compare };
	struct callback inst_stack_jump_compare = { &instruction_callback_stack_jump_compare };
	map_add(program->instruction_map, TOKEN_NONE, &inst_stack_none);
	map_add(program->instruction_map, TOKEN_PUSH, &inst_stack_push);
	map_add(program->instruction_map, TOKEN_POP, &inst_stack_pop);
	map_add(program->instruction_map, TOKEN_ADD, &inst_stack_add);
	map_add(program->instruction_map, TOKEN_SUBTRACT, &inst_stack_subtract);
	map_add(program->instruction_map, TOKEN_MULTIPLICATION, &inst_stack_multiply);
	map_add(program->instruction_map, TOKEN_DIVISION, &inst_stack_divide);
	map_add(program->instruction_map, TOKEN_JUMP, &inst_jump);
	map_add(program->instruction_map, TOKEN_COMPARE, &inst_stack_compare);
	map_add(program->instruction_map, TOKEN_JUMP_COMPARE, &inst_stack_jump_compare);

	return RESULT_TRUE;
}

void program_add_instruction_to_instruction_map(const struct program* program, uint8_t key, void* instruction)
{
	map_add(program->instruction_map, key, instruction);
}

instruction_callback program_get_callback_from_instruction_map(const struct program* program, uint8_t key)
{
	const struct callback* cb = (struct callback*)map_get_unsafe(program->instruction_map, key);
	return cb->callback;
}

uint64_t program_get_size(void)
{
	return sizeof(struct program);
}

void program_dump_stack(struct program* program)
{
	for (uint64_t i = 0; i < stack_get_elements(program->stack); i++)
	{
		printf("stack #%llu %llu \n", i, stack_get_data(program->stack, i));
	}
}