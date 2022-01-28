#pragma once
#include <stdint.h>
#include "../result.h"
#include "instruction_callback_type.h"

struct program;

void* program_create(void* vm);
result program_start(struct program* program);
void* program_get_instruction_list(const struct program* program);
void program_add_instruction_with_token(struct program* program, void* token);
void* program_get_stack(const struct program* program);
void* program_get_vm(const struct program* program);
uint64_t program_get_instruction_pointer(struct program* program);
void program_set_instruction_pointer(struct program* program, uint64_t instruction_pointer);
result program_delete(struct program* program);
result program_insert_standard_instructions_to_instruction_map(struct program* program);
void program_add_instruction_to_instruction_map(const struct program* program, uint8_t key, void* instruction);
instruction_callback program_get_callback_from_instruction_map(const struct program* program, uint8_t key);
uint64_t program_get_size(void);

void program_dump_stack(struct program* program);