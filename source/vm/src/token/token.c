#include "token.h"
#include <stdlib.h>

struct token
{
	// token_type
	unsigned char type;
	vm_data data;
};

void* token_create(const unsigned char type, const vm_data data)
{
	struct token* new_token = malloc(sizeof(struct token));
	if (new_token == NULL)
		return NULL;

	new_token->type = type;
	new_token->data = data;

	return new_token;
}

unsigned char token_get_type(const struct token* token)
{
	return token->type;
}

void token_set_type(struct token* token, const unsigned char type)
{
	token->type = type;
}

vm_data token_get_data(const struct token* token)
{
	return token->data;
}

void token_set_data(struct token* token, const vm_data data)
{
	token->data = data;
}

size_t token_get_size(void)
{
	return sizeof(struct token);
}