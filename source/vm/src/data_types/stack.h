#pragma once
#include "vm_data.h"
#include <stddef.h>
#include "../result.h"

struct stack;

void* stack_create(size_t capacity);
result stack_push(struct stack* stack, vm_data data);
result stack_pop(struct stack* stack);
result stack_peek(struct stack* stack);
result stack_is_empty(const struct stack* stack);
result stack_is_full(const struct stack* stack);
size_t stack_get_capacity(const struct stack* stack);
size_t stack_get_elements(const struct stack* stack);
vm_data stack_get_cache(const struct stack* stack);
void stack_set_cache(struct stack* stack, const vm_data data);
vm_data stack_get_data(const struct stack* stack, const size_t index);
void stack_delete(struct stack* stack);