#pragma once
#include "../data_types/vm_data.h"

struct token;

void* token_create(const unsigned char type, const vm_data data);
unsigned char token_get_type(const struct token* token);
void token_set_type(struct token* token, const unsigned char type);
vm_data token_get_data(const struct token* token);
void token_set_data(struct token* token, const vm_data data);
size_t token_get_size(void);