#include "program.h"
#include <stdlib.h>
#include "../instruction/instruction.h"
#include "../token/token_list.h"

void program_install_instructions(program* prog, token_list* tokens, instruction_map* instruction_table)
{
	instruction* instruction_list = (instruction*)malloc(tokens->elements * sizeof(instruction));
	for (size_t i = 0; i < tokens->elements; i++)
	{
		instruction_list[i].callback = instruction_table->map[tokens->list[i].type];
		instruction_list[i].data = tokens->list[i].data;
	}

	prog->instructions = instruction_list;
	prog->instruction_count = tokens->elements;
}