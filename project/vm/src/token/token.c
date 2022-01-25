#include "token.h"

token token_create(const token_type type, const int64_t data)
{
	return (token) {
		.type = type,
		.data = data,
	};
}