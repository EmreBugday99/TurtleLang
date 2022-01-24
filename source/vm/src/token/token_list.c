#include "token_list.h"
#include <stdio.h>
#include <stdlib.h>

token_list token_list_create(size_t capacity)
{
	return (token_list) {
		.list = (token*)malloc(capacity * sizeof(token)),
			.elements = 0,
			.capacity = capacity
	};
}

void token_list_push(token_list* list, token token_to_push)
{
	if (list->elements == list->capacity)
		token_list_increase_capacity(list, 1);

	list->list[list->elements].type = token_to_push.type;
	list->list[list->elements].data = token_to_push.data;

	list->elements++;
}

vm_result token_list_insert(token_list* list, size_t index, token token_to_insert)
{
	if (index > list->elements)
	{
		printf("Index can't be bigger than token_list elements!");
		return VM_RESULT_FAIL;
	}

	if (list->elements == list->capacity)
		token_list_increase_capacity(list, 1);

	for (size_t i = list->elements - 1; i > index; i--)
	{
		list->list[i].type = list->list[i - 1].type;
		list->list[i].data = list->list[i - 1].data;
	}

	list->list[index].type = token_to_insert.type;
	list->list[index].data = token_to_insert.data;
	list->elements++;
	return VM_RESULT_SUCCESS;
}

vm_result token_list_delete(token_list* list, size_t index)
{
	if (index < 0 || index > list->elements)
		return 0;

	for (size_t i = index; i < list->elements - 1; i++)
	{
		list->list[i] = list->list[i + 1];
	}
	list->list[list->elements].type = TOKEN_NONE;
	list->list[list->elements].data = 0;

	list->elements--;
	return 1;
}

void token_list_copy(const token_list* copy_from, token_list* copy_to)
{
	free(copy_to->list);
	copy_to->capacity = copy_from->capacity;
	copy_to->elements = copy_from->elements;
	copy_to->list = NULL;
	copy_to->list = (token*)malloc(copy_to->capacity * sizeof(token));

	for (size_t i = 0; i < copy_to->capacity; i++)
	{
		copy_to->list[i].type = copy_from->list[i].type;
		copy_to->list[i].data = copy_from->list[i].data;
	}
}

void token_list_increase_capacity(token_list* list, size_t increase_count)
{
	if (list->capacity == 0)
	{
		list->capacity += increase_count;
		list->list = (token*)malloc(list->capacity * sizeof(token));
		return;
	}
	const size_t new_capacity = list->capacity + increase_count;
	list->capacity = new_capacity;

	token_list copy_list = token_list_create(new_capacity);
	token_list_copy(list, &copy_list);

	free(list->list);
	list->list = NULL;

	list->list = (token*)malloc(list->capacity * sizeof(token));
	for (size_t i = 0; i < list->capacity; i++)
	{
		if (i > list->elements)
		{
			list->list[i].type = TOKEN_NONE;
			list->list[i].data = 0;
		}
		else
		{
			list->list[i].type = copy_list.list[i].type;
			list->list[i].data = copy_list.list[i].data;
		}
	}

	free(copy_list.list);
	copy_list.list = NULL;
}