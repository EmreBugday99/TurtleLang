#pragma once
#include "instruction_callback_type.h"
#include <stdint.h>

struct instruction;

void* instruction_create(const uint8_t type, vm_data data);
void instruction_delete(struct instruction* instruction);
uint8_t instruction_get_type(const struct instruction* instruction);
vm_data instruction_get_data(struct instruction* instruction);
uint64_t instruction_get_size(void);
void dump_struct_size(void);