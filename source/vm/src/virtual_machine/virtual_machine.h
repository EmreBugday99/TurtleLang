#pragma once
#include <stdint.h>

struct virtual_machine
{
	void* token_list;
	size_t token_pointer;
	void* stack;
};

struct virtual_machine* vm_create(void);
void vm_execute_token(struct virtual_machine* vm, void* token);
void vm_start(struct virtual_machine* vm);
void vm_dump_stack(const struct virtual_machine* vm);