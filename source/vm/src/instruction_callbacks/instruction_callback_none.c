#include "instruction_callback_none.h"

enum instruction_result instruction_callback_none(const void* program, const vm_data data)
{
	return INSTRUCTION_RESULT_OK;
}
