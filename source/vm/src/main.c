#include "data_types/list.h"
#include "program/instruction.h"
#include "program/program.h"
#include "token/token.h"
#include "token/token_type.h"
#include "virtual_machine/virtual_machine.h"

int main()
{
	dump_struct_size();

	void* vm = vm_create();

	void* token1 = token_create(TOKEN_PUSH, 5);
	void* token2 = token_create(TOKEN_PUSH, 10);
	void* token3 = token_create(TOKEN_ADD, 0);

	void* program = program_create(vm);
	program_insert_standard_instructions_to_instruction_map(program);

	program_add_instruction_with_token(program, token1);
	program_add_instruction_with_token(program, token2);
	program_add_instruction_with_token(program, token3);

	list_add(vm_get_program_list(vm), program);
	vm_start(vm);

	return 0;
}