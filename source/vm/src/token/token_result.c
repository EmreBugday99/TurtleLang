#include "token_result.h"

const char* token_result_as_cstr(token_result result)
{
	switch (result)
	{
	case TOKEN_RESULT_OK:
		return "OKAY";
	case TOKEN_RESULT_STACK_OVERFLOW:
		return "STACK OVERFLOW";
	case TOKEN_RESULT_STACK_UNDER_FLOW:
		return "STACK UNDERFLOW";
	case TOKEN_RESULT_DIVISION_BY_ZERO:
		return "DIVISION BY ZERO";
	default:
		return "UNKNOWN";
	}
}