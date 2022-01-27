#include "list.h"
#include <stdlib.h>
#include <string.h>

struct list
{
	uint64_t capacity;
	uint64_t elements;
	uint64_t data_size;
	void* list;
};

void* list_create(const size_t capacity, const size_t data_size)
{
	if (capacity <= 0 || data_size <= 0)
		return NULL;

	struct list* new_list = malloc(sizeof(struct list));
	if (new_list == NULL)
		return NULL;

	new_list->capacity = capacity;
	new_list->elements = 0;
	new_list->data_size = data_size;
	new_list->list = malloc(capacity * data_size);
	if (new_list->list == NULL)
	{
		free(new_list);
		return NULL;
	}

	return new_list;
}

void* list_add(struct list* list, const void* data)
{
	if (list->elements == list->capacity)
		list_increase_capacity(list, LIST_CAPACITY_INCREASE_AMOUNT);

	char* start = (char*)list->list + (list->elements * list->data_size);

	void* copied_data = memcpy(start, data, list->data_size);
	if (copied_data == NULL)
		return NULL;

	list->elements++;
	return copied_data;
}

void* list_insert(struct list* list, const void* data, size_t index)
{
	if (index > list->elements)
		return NULL;

	// Safety List is a clone of the list that we are inserting.
	// If anything fucks up during the insertion operation, we reset the fucked up list to the safety clone list.
	struct list* safety_list_clone = list_create(list->capacity, list->data_size);
	if (list_clone(list, safety_list_clone) == RESULT_FALSE)
	{
		list_destroy(safety_list_clone);
		return NULL;
	}

	if (list->elements == list->capacity
		&& list_increase_capacity(list, LIST_CAPACITY_INCREASE_AMOUNT) == RESULT_FALSE)
	{
		list_clone(safety_list_clone, list);
		list_destroy(safety_list_clone);
		return NULL;
	}

	for (size_t i = list->elements; i > index; i--)
	{
		char* destination = (char*)list->list + (i * list->data_size);
		const char* source = (char*)list->list + ((i - 1) * list->data_size);

		void* copy_location = memcpy(destination, source, list->data_size);
		if (copy_location == NULL)
		{
			list_clone(safety_list_clone, list);
			return NULL;
		}
	}
	char* destination = (char*)list->list + (index * list->data_size);
	void* copy_location = memcpy(destination, data, list->data_size);
	if (copy_location == NULL)
	{
		list_clone(safety_list_clone, list);
		list_destroy(safety_list_clone);
		return NULL;
	}

	list_destroy(safety_list_clone);
	list->elements++;
	return copy_location;
}

result list_remove(struct list* list, size_t index)
{
	if (index < 0 || index > list->elements)
		return RESULT_FALSE;

	// Safety List is a clone of the list that we are inserting.
	// If anything fucks up during the insertion operation, we reset the fucked up list to the safety clone list.
	struct list* safety_list_clone = list_create(list->capacity, list->data_size);
	if (list_clone(list, safety_list_clone) == RESULT_FALSE)
	{
		list_destroy(safety_list_clone);
		return RESULT_FALSE;
	}

	for (size_t i = index; i < list->elements - 1; i++)
	{
		char* destination = (char*)list->list + (i * list->data_size);
		char* source = (char*)list->list + ((i + 1) * list->data_size);

		void* copy_location = memcpy(destination, source, list->data_size);
		if (copy_location == NULL)
		{
			list_clone(safety_list_clone, list);
			list_destroy(safety_list_clone);
			return RESULT_FALSE;
		}
	}

	list->elements--;
	return RESULT_TRUE;
}

void* list_get(struct list* list, const size_t index)
{
	if (index > list->elements || index < 0)
		return RESULT_FALSE;

	return list_get_unsafe(list, index);
}

void* list_get_unsafe(struct list* list, const size_t index)
{
	return (char*)list->list + (index * list->data_size);
}

uint64_t list_get_element_count(const struct list* list)
{
	return list->elements;
}

uint64_t list_get_capacity(const struct list* list)
{
	return list->capacity;
}

uint64_t list_get_data_size(const struct list* list)
{
	return list->data_size;
}

result list_clone(const struct list* list_clone_from, struct list* list_clone_to)
{
	const size_t data_size_to_copy = list_clone_from->capacity * list_clone_from->data_size;

	free(list_clone_to->list);
	list_clone_to->capacity = list_clone_from->capacity;
	list_clone_to->elements = list_clone_from->elements;
	list_clone_to->data_size = list_clone_from->data_size;
	list_clone_to->list = NULL;
	list_clone_to->list = malloc(data_size_to_copy);
	if (list_clone_to->list == NULL)
		return RESULT_FALSE;

	void* copy_location = memcpy(list_clone_to->list, list_clone_from->list, data_size_to_copy);
	if (copy_location == NULL)
		return RESULT_FALSE;

	return RESULT_TRUE;
}

result list_increase_capacity(struct list* list, const size_t increase_amount)
{
	const size_t new_capacity = list->capacity + increase_amount;
	const size_t new_allocation_size = new_capacity * list->data_size;
	const size_t clone_size = list->capacity * list->data_size;

	struct list* clone_list = list_create(list->capacity, list->data_size);
	if (clone_list == NULL)
		return RESULT_FALSE;

	if (list_clone(list, clone_list) == RESULT_FALSE)
	{
		list_destroy(clone_list);
		return RESULT_FALSE;
	}

	free(list->list);
	list->list = NULL;
	list->list = malloc(new_allocation_size);
	if (list->list == NULL)
	{
		list_destroy(clone_list);
		return RESULT_FALSE;
	}
	list->capacity = new_capacity;

	void* copy_location = memcpy(list->list, clone_list->list, clone_size);
	if (copy_location == NULL)
	{
		list_destroy(clone_list);
		return RESULT_FALSE;
	}

	list_destroy(clone_list);
	return RESULT_TRUE;
}

void list_destroy(struct list* list)
{
	free(list->list);
	list->list = NULL;

	free(list);
	list = NULL;
}