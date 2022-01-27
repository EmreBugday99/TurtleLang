#include "instruction_callback_stack_multiplication.h"
#include "../data_types/stack.h"
#include "../program/program.h"

enum instruction_result instruction_callback_stack_multiplication(const void* program, const vm_data data)
{
	if (stack_pop(program_get_stack(program)) == RESULT_FALSE)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;
	const vm_data cache1 = stack_get_cache(program_get_stack(program));

	if (stack_pop(program_get_stack(program)) == RESULT_FALSE)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;
	const vm_data cache2 = stack_get_cache(program_get_stack(program));

	stack_push(program_get_stack(program), cache1 * cache2)
	return INSTRUCTION_RESULT_OK;
}