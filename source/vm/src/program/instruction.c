#include "instruction.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef TURTLE_OS_WINDOWS
#pragma pack(push, 1)
struct instruction
{
	uint8_t type;
	vm_data data;
};
#pragma pack(pop)
#endif

#ifdef TURTLE_OS_LINUX
struct instruction
{
	uint8_t type;
	vm_data data;
}__attribute__((packed));
#endif

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
	const uint8_t* data = &instruction->type + 1;
	return *data;
}

uint64_t instruction_get_size(void)
{
	return sizeof(struct instruction);
}

void dump_struct_size(void)
{
	uint64_t size = sizeof(uint8_t) + sizeof(vm_data);

	printf("%llu \n", sizeof(struct instruction));
	printf("%llu \n", size);
}