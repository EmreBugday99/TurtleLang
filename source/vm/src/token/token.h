#pragma once
#include <stdint.h>
#include "token_type.h"

typedef int64_t token_data;

typedef struct
{
	token_type type;
	token_data data;
} token;

token token_create(const token_type type, const int64_t data);