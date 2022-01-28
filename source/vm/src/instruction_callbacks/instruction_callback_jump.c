#include "instruction_callback_jump.h"
#include "../data_types/list.h"
#include "../program/program.h"

enum instruction_result instruction_callback_jump(void* program, vm_data data)
{
	if (data > list_get_element_count(program))
		return INSTRUCTION_RESULT_INVALID_JUMP_INDEX;

	program_set_instruction_pointer(program, data);
	return INSTRUCTION_RESULT_OK;
}