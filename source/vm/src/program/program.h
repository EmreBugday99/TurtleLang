#pragma once
#ifndef PROGRAM_H
#define PROGRAM_H

#include "../virtual_machine/stack.h"
#include "../instruction/instruction.h"
#include "../token/token_list.h"

// TODO: Convert instructions into a new data type as an instruction list.
typedef struct program
{
	unsigned char program_id;
	instruction* instructions;
	size_t instruction_count;
	size_t instruction_pointer;
	stack program_stack;
	struct virtual_machine* host;
} program;

void program_install_instructions(program* prog, token_list* tokens, instruction_map* instruction_table);

#endif