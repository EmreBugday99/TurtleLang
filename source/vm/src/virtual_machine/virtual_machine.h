#pragma once
#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include "stack.h"
#include "../program/program_list.h"

typedef struct
{
	stack stack;
	program_list programs;
} virtual_machine;

virtual_machine* vm_create(void);
void vm_start(virtual_machine* vm);
void vm_load_program(virtual_machine* vm, token_list* tokens, instruction_map* instructions, size_t stack_size);
void vm_dump_stack(const virtual_machine* vm);
void vm_on_error(virtual_machine* vm, const char* error_message);

#endif