#pragma once

typedef enum
{
	TOKEN_RESULT_OK = 0,
	TOKEN_RESULT_STACK_OVERFLOW,
	TOKEN_RESULT_STACK_UNDER_FLOW,
	TOKEN_RESULT_DIVISION_BY_ZERO
} token_result;

const char* token_result_as_cstr(token_result result);