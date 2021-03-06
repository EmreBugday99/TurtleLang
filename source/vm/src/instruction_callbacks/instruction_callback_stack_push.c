#include "instruction_callback_stack_push.h"

#include <stdio.h>

#include "../data_types/stack.h"
#include "../program/program.h"

enum instruction_result instruction_callback_stack_push(void* program, vm_data data)
{
	if (stack_push(program_get_stack(program), data) == RESULT_FALSE)
		return INSTRUCTION_RESULT_STACK_OVERFLOW;


	return INSTRUCTION_RESULT_OK;
}
