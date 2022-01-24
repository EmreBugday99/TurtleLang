#pragma once
#ifndef TOKEN_H
#define TOKEN_H

#include "../virtual_machine/vm_data.h"
#include "token_type.h"

typedef struct
{
	token_type type;
	vm_data data;
} token;

token token_create(const token_type type, const vm_data data);

#endif