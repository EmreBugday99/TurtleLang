#pragma once
#include "../result.h"

struct virtual_machine;

void* vm_create(void);
result vm_start(struct virtual_machine* vm);
void vm_dump_stack(const struct virtual_machine* vm);
void* vm_get_program_list(struct virtual_machine* vm);