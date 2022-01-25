#pragma once
#include <stdint.h>
#include "vm_stack.h"
#include "../token/token_list.h"

typedef struct
{
	vm_stack stack;
	token_list token_list;
	size_t token_pointer;
} virtual_machine;

virtual_machine* vm_create(void);
void vm_execute_token(virtual_machine* vm, token vm_token);
void vm_start(virtual_machine* vm);
void vm_dump_stack(const virtual_machine* vm);