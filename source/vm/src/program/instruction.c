#include "instruction.h"
#include <stdlib.h>

struct instruction
{
	uint8_t type;
	vm_data data;
};

void* instruction_create(const uint8_t type, vm_data data)
{
	struct instruction* new_instruction = malloc(sizeof(struct instruction));
	if (new_instruction == NULL)
		return NULL;

	new_instruction->type = type;
	new_instruction->data = data;

	return new_instruction;
}

void instruction_delete(struct instruction* instruction)
{
	free(instruction);
	instruction = NULL;
}

uint8_t instruction_get_type(const struct instruction* instruction)
{
	return instruction->type;
}

vm_data instruction_get_data(struct instruction* instruction)
{
	vm_data data = instruction->data;
	return data;
}

uint64_t instruction_get_size(void)
{
	return sizeof(struct instruction);
}