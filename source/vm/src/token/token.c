#include "token.h"

token token_create(const token_type type, const vm_data data)
{
	return (token) {
		.type = type,
		.data = data,
	};
}