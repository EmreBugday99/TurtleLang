#define MAP_IMPLEMENTATION
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "data_types/list.h"
#include "data_types/map.h"
#include "program/program.h"
#include "token/token.h"
#include "token/token_type.h"
#include "virtual_machine/virtual_machine.h"

GENERATE_MAP(int)

int main()
{
	void* vm = vm_create();
	void* program1 = program_create(vm);

	void* token1 = token_create(TOKEN_PUSH, 3);
	void* token2 = token_create(TOKEN_PUSH, 10);
	void* token3 = token_create(TOKEN_MULTIPLICATION, 0);
	void* token4 = token_create(TOKEN_PUSH, 20);
	void* token5 = token_create(TOKEN_JUMP_COMPARE, 6);
	void* token6 = token_create(TOKEN_PUSH, 1);
	void* token7 = token_create(TOKEN_PUSH, 250);
	void* token8 = token_create(TOKEN_PUSH, 111);

	program_insert_standard_instructions_to_instruction_map(program1);

	program_add_instruction_with_token(program1, token1);
	program_add_instruction_with_token(program1, token2);
	program_add_instruction_with_token(program1, token3);
	program_add_instruction_with_token(program1, token4);
	program_add_instruction_with_token(program1, token5);
	program_add_instruction_with_token(program1, token6);
	program_add_instruction_with_token(program1, token7);
	program_add_instruction_with_token(program1, token8);

	list_add(vm_get_program_list(vm), program1);
	vm_start(vm);

	printf("\n");
	printf("\n");

	program_dump_stack(program1);

	return 0;
}