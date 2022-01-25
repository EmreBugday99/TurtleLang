#pragma once
#include "../data_types/vm_data.h"
#include "instruction_callback_type.h"

struct instruction;

void* instruction_create(const instruction_callback callback, const vm_data data);
void instruction_delete(struct instruction* instruction);