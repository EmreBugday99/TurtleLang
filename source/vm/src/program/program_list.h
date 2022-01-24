#pragma once
#ifndef PROGRAM_LIST_H
#define PROGRAM_LIST_H

#include "program.h"
#include "../types.h"
#include "../virtual_machine/virtual_machine.h"

typedef struct
{
	program* list;
	unsigned char elements;
	unsigned char capacity;
} program_list;

program_list program_list_create(unsigned char capacity);
vm_result program_list_add_new_program(program_list* programs, virtual_machine* vm, size_t stack_size);
vm_result program_list_remove(program_list* programs, unsigned char index);

#endif
