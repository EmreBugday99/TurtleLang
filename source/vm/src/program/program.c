#include "program.h"

#include <stdio.h>
#include <stdlib.h>
#include "instruction.h"
#include "instruction_callback_type.h"
#include "../data_types/list.h"
#include "../data_types/stack.h"

#define MAP_IMPLEMENTATION
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

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

GENERATE_MAP(instruction_callback)

struct program
{
	void* instruction_list;
	void* stack;
	void* vm;
	struct map_instruction_callback instruction_map;
	uint64_t instruction_pointer;
};

void* program_create(void* vm)
{
	struct program* new_program = malloc(sizeof(struct program));
	if (new_program == NULL)
		return NULL;

	new_program->instruction_list = list_create(20, sizeof(instruction_get_size()));
	new_program->stack = stack_create(1024);
	new_program->vm = vm;
	new_program->instruction_map = map_create_instruction_callback(4);
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

		instruction_callback callback = program_get_callback_from_instruction_map(program, type);

		callback(program, data);
		printf("ip: %llu \n", program->instruction_pointer);
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

	map_add_instruction_callback(&program->instruction_map, TOKEN_NONE, &instruction_callback_none);
	map_add_instruction_callback(&program->instruction_map, TOKEN_PUSH, &instruction_callback_stack_push);
	map_add_instruction_callback(&program->instruction_map, TOKEN_POP, &instruction_callback_stack_pop);
	map_add_instruction_callback(&program->instruction_map, TOKEN_ADD, &instruction_callback_stack_add);
	map_add_instruction_callback(&program->instruction_map, TOKEN_SUBTRACT, &instruction_callback_stack_subtract);
	map_add_instruction_callback(&program->instruction_map, TOKEN_MULTIPLICATION, &instruction_callback_stack_multiplication);
	map_add_instruction_callback(&program->instruction_map, TOKEN_DIVISION, &instruction_callback_stack_division);
	map_add_instruction_callback(&program->instruction_map, TOKEN_JUMP, &instruction_callback_jump);
	map_add_instruction_callback(&program->instruction_map, TOKEN_COMPARE, &instruction_callback_stack_compare);
	map_add_instruction_callback(&program->instruction_map, TOKEN_JUMP_COMPARE, &instruction_callback_stack_jump_compare);

	return RESULT_TRUE;
}

void program_add_instruction_to_instruction_map(struct program* program, uint8_t key, instruction_callback callback)
{
	map_add_instruction_callback(&program->instruction_map, key, callback);
}

instruction_callback program_get_callback_from_instruction_map(struct program* program, uint8_t key)
{
	return map_get_unsafe_instruction_callback(&program->instruction_map, key);
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