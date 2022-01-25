#pragma once
#include <stdint.h>
#include "stack.h"
#include "../token/token_list.h"

struct virtual_machine
{
	token_list token_list;
	size_t token_pointer;
	struct stack* stack;
};

struct virtual_machine* vm_create(void);
void vm_execute_token(struct virtual_machine* vm, token vm_token);
void vm_start(struct virtual_machine* vm);
void vm_dump_stack(const struct virtual_machine* vm);