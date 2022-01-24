#include "instruction_results.h"

const char* instruction_result_as_cstr(const instruction_result result)
{
	switch (result)
	{
	case INSTRUCTION_RESULT_OK:
		return "OKAY";
	case INSTRUCTION_RESULT_UNKNOWN_ERROR:
		return "UNKNOWN ERROR";
	case INSTRUCTION_RESULT_STACK_OVERFLOW:
		return "STACK OVERFLOW";
	case INSTRUCTION_RESULT_STACK_UNDER_FLOW:
		return "STACK UNDERFLOW";
	case INSTRUCTION_RESULT_DIVISION_BY_ZERO:
		return "DIVISION BY ZERO";
	case INSTRUCTION_RESULT_INVALID_JUMP_INDEX:
		return "INVALID JUMP INDEX";
	default:
		return "UNKNOWN";
	}
}