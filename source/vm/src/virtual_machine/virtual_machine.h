#pragma once
#include <stddef.h>

struct virtual_machine;

void* vm_create(void);
void vm_execute_token(struct virtual_machine* vm, const void* token);
void vm_start(struct virtual_machine* vm);
void vm_dump_stack(const struct virtual_machine* vm);
void* vm_get_token_list(const struct virtual_machine* vm);
size_t vm_get_token_pointer(const struct virtual_machine* vm);
void vm_set_token_pointer(struct virtual_machine* vm, const size_t token_pointer);
void* vm_get_stack(const struct virtual_machine* vm);