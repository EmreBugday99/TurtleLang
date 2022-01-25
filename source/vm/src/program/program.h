#pragma once

struct program;

void* program_create(void* vm);
void* program_get_instruction_list(const struct program* program);
void* program_get_stack(const struct program* program);
void* program_get_vm(const struct program* program);
void program_delete(struct program* program);