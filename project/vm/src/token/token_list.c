#include "token_list.h"
#include <stdio.h>
#include <stdlib.h>

token_list token_list_create(size_t capacity)
{
	return (token_list) {
		.tokens = (token*)malloc(capacity * sizeof(token)),
			.elements = 0,
			.capacity = capacity
	};
}

void token_list_push(token_list* list, token token_to_push)
{
	if (list->elements == list->capacity)
		token_list_increase_capacity(list, 1);

	list->tokens[list->elements].type = token_to_push.type;
	list->tokens[list->elements].data = token_to_push.data;

	list->elements++;
}

unsigned char token_list_insert(token_list* list, size_t index, token token_to_insert)
{
	if (index > list->elements)
	{
		printf("Index can't be bigger than token_list elements!");
		return 0;
	}

	if (list->elements == list->capacity)
		token_list_increase_capacity(list, 1);

	for (size_t i = list->elements - 1; i > index; i--)
	{
		list->tokens[i].type = list->tokens[i - 1].type;
		list->tokens[i].data = list->tokens[i - 1].data;
	}

	list->tokens[index].type = token_to_insert.type;
	list->tokens[index].data = token_to_insert.data;
	list->elements++;
	return 1;
}

unsigned char token_list_delete(token_list* list, size_t index)
{
	if (index < 0 || index > list->elements)
		return 0;

	for (size_t i = index; i < list->elements - 1; i++)
	{
		list->tokens[i] = list->tokens[i + 1];
	}
	list->tokens[list->elements].type = TOKEN_NONE;
	list->tokens[list->elements].data = 0;

	list->elements--;
	return 1;
}

void token_list_copy(const token_list* copy_from, token_list* copy_to)
{
	free(copy_to->tokens);
	copy_to->capacity = copy_from->capacity;
	copy_to->elements = copy_from->elements;
	copy_to->tokens = NULL;
	copy_to->tokens = (token*)malloc(copy_to->capacity * sizeof(token));

	for (size_t i = 0; i < copy_to->capacity; i++)
	{
		copy_to->tokens[i].type = copy_from->tokens[i].type;
		copy_to->tokens[i].data = copy_from->tokens[i].data;
	}
}

void token_list_increase_capacity(token_list* list, size_t increase_count)
{
	if (list->capacity == 0)
	{
		list->capacity += increase_count;
		list->tokens = (token*)malloc(list->capacity * sizeof(token));
		return;
	}
	const size_t new_capacity = list->capacity + increase_count;
	list->capacity = new_capacity;

	token_list copy_list = token_list_create(new_capacity);
	token_list_copy(list, &copy_list);

	free(list->tokens);
	list->tokens = NULL;

	list->tokens = (token*)malloc(list->capacity * sizeof(token));
	for (size_t i = 0; i < list->capacity; i++)
	{
		if (i > list->elements)
		{
			list->tokens[i].type = TOKEN_NONE;
			list->tokens[i].data = 0;
		}
		else
		{
			list->tokens[i].type = copy_list.tokens[i].type;
			list->tokens[i].data = copy_list.tokens[i].data;
		}
	}

	free(copy_list.tokens);
	copy_list.tokens = NULL;
}