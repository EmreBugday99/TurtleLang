#pragma once
#include "instruction_callback_type.h"
#include <stdint.h>

struct instruction;

void* instruction_create(const instruction_callback callback, vm_data data);
void instruction_delete(struct instruction* instruction);
uint64_t instruction_get_size(void);