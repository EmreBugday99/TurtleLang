#pragma once
#include <stdint.h>

#include "../result.h"

struct program;

void* program_create(void* vm);
void* program_get_instruction_list(const struct program* program);
void* program_get_stack(const struct program* program);
void* program_get_vm(const struct program* program);
uint64_t program_get_instruction_pointer(struct program* program);
void program_set_instruction_pointer(struct program* program, uint64_t instruction_pointer);
result program_delete(struct program* program);
result program_insert_standard_instructions(struct program* program);