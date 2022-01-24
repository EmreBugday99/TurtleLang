#pragma once
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "../virtual_machine/vm_data.h"
#include "../program/program.h"
#include "instruction_results.h"

typedef instruction_result(*instruction_callback)(program*, const vm_data*);

#define STANDARD_LIBRARY_INSTRUCTION_COUNT 10
instruction_result std_instruction_none(program* process, const vm_data* data);
instruction_result std_instruction_stack_push(program* process, const vm_data* data);
instruction_result std_instruction_stack_pop(program* process, const vm_data* data);
instruction_result std_instruction_stack_add(program* process, const vm_data* data);
instruction_result std_instruction_stack_subtract(program* process, const vm_data* data);
instruction_result std_instruction_stack_multiply(program* process, const vm_data* data);
instruction_result std_instruction_stack_divide(program* process, const vm_data* data);
instruction_result std_instruction_jump(program* process, const vm_data* data);
instruction_result std_instruction_compare(program* process, const vm_data* data);
instruction_result std_instruction_jump_compare(program* process, const vm_data* data);

#endif