#include "instructions.h"
#include "../virtual_machine/stack.h"

instruction_result std_instruction_none(program* process, const vm_data* data)
{
	return INSTRUCTION_RESULT_OK;
}
instruction_result std_instruction_stack_push(program* process, const vm_data* data)
{
	if (stack_push(&process->program_stack, *data) == 0)
		return INSTRUCTION_RESULT_STACK_OVERFLOW;

	return INSTRUCTION_RESULT_OK;
}
instruction_result std_instruction_stack_pop(program* process, const vm_data* data)
{
	if (stack_pop(&process->program_stack) == 0)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;

	return INSTRUCTION_RESULT_OK;
}
instruction_result std_instruction_stack_add(program* process, const vm_data* data)
{
	if (stack_pop(&process->program_stack) == 0)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;
	const vm_data data1 = process->program_stack.cache1;

	if (stack_pop(&process->program_stack) == 0)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;
	const vm_data data2 = process->program_stack.cache1;

	// Already popped once, no need to check for stack overflow for push.
	stack_push(&process->program_stack, data1 + data2);

	return INSTRUCTION_RESULT_OK;
}
instruction_result std_instruction_stack_subtract(program* process, const vm_data* data)
{
	if (stack_pop(&process->program_stack) == 0)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;
	const vm_data data1 = process->program_stack.cache1;

	if (stack_pop(&process->program_stack) == 0)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;
	const vm_data data2 = process->program_stack.cache1;

	// Already popped once, no need to check for stack overflow for push.
	stack_push(&process->program_stack, data1 - data2);

	return INSTRUCTION_RESULT_OK;
}
instruction_result std_instruction_stack_multiply(program* process, const vm_data* data)
{
	if (stack_pop(&process->program_stack) == 0)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;
	const vm_data data1 = process->program_stack.cache1;

	if (stack_pop(&process->program_stack) == 0)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;
	const vm_data data2 = process->program_stack.cache1;

	// Already popped once, no need to check for stack overflow for push.
	stack_push(&process->program_stack, data1 * data2);

	return INSTRUCTION_RESULT_OK;
}
instruction_result std_instruction_stack_divide(program* process, const vm_data* data)
{
	if (stack_pop(&process->program_stack) == 0)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;
	const vm_data data1 = process->program_stack.cache1;

	if (stack_pop(&process->program_stack) == 0)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;
	const vm_data data2 = process->program_stack.cache1;

	// Already popped once, no need to check for stack overflow for push.
	stack_push(&process->program_stack, data1 / data2);

	return INSTRUCTION_RESULT_OK;
}
instruction_result std_instruction_jump(program* process, const vm_data* data)
{
	if (*data < 0 || *data > process->instruction_count)
		return INSTRUCTION_RESULT_INVALID_JUMP_INDEX;

	process->instruction_pointer = *data;

	return INSTRUCTION_RESULT_OK;
}
instruction_result std_instruction_compare(program* process, const vm_data* data)
{
	if (stack_pop(&process->program_stack) == 0)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;

	// Already popped once, no need to check for stack overflow for push.
	if (process->program_stack.cache1 == *data)
		stack_push(&process->program_stack, 1);
	else
		stack_push(&process->program_stack, 0);

	return INSTRUCTION_RESULT_OK;
}
instruction_result std_instruction_jump_compare(program* process, const vm_data* data)
{
	if (stack_pop(&process->program_stack) == 0)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;
	const vm_data data1 = process->program_stack.cache1;

	if (stack_pop(&process->program_stack) == 0)
		return INSTRUCTION_RESULT_STACK_UNDER_FLOW;
	const vm_data data2 = process->program_stack.cache1;

	if (data1 == data2)
		process->instruction_pointer = *data;

	return INSTRUCTION_RESULT_OK;
}