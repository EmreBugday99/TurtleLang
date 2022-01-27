#include "instruction_callback_stack_compare.h"
#include "../program/program.h"
#include "../data_types/stack.h"

enum instruction_result instruction_callback_stack_compare(void* program, vm_data data)
{
	if (stack_pop(program_get_stack(program)) == RESULT_FALSE)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;
	const vm_data cache1 = stack_get_cache(program_get_stack(program));

	if (stack_pop(program_get_stack(program)) == RESULT_FALSE)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;
	const vm_data cache2 = stack_get_cache(program_get_stack(program));

	vm_data result = 0;
	if (cache1 != cache2)
		result = RESULT_FALSE;
	else
		result = RESULT_TRUE;

	stack_push(program_get_stack(program), result);
	return INSTRUCTION_RESULT_OK;
}