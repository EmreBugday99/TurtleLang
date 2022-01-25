#include "instruction.h"
#include <stdlib.h>
#include "../data_types/vm_data.h"


struct instruction
{
	instruction_callback callback;
	vm_data data;
};

void* instruction_create(const instruction_callback callback, const vm_data data)
{
	struct instruction* new_instruction = malloc(sizeof(struct instruction));
	if (new_instruction == NULL)
		return NULL;

	new_instruction->callback = callback;
	new_instruction->data = data;

	return new_instruction;
}

void instruction_delete(struct instruction* instruction)
{
	free(instruction);
	instruction = NULL;
}