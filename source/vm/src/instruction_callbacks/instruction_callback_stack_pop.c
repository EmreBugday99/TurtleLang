#include "instruction_callback_stack_pop.h"
#include "../data_types/stack.h"
#include "../program/program.h"

enum instruction_result instruction_callback_stack_pop(void* program, vm_data data)
{
	if (stack_pop(program_get_stack(program)) == RESULT_FALSE)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;

	return INSTRUCTION_RESULT_OK;
}