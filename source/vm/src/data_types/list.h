#pragma once
#include <stddef.h>
#include "../result.h"
#include <stdint.h>

#define LIST_CAPACITY_INCREASE_AMOUNT 4

struct list;

void* list_create(const size_t capacity, const size_t data_size);
void* list_add(struct list* list, const void* data);
void* list_insert(struct list* list, const void* data, size_t index);
result list_remove(struct list* list, size_t index);
void* list_get(struct list* list, const size_t index);
void* list_get_unsafe(struct list* list, const size_t index);
uint64_t list_get_element_count(const struct list* list);
uint64_t list_get_capacity(const struct list* list);
uint64_t list_get_data_size(const struct list* list);
result list_clone(const struct list* list_clone_from, struct list* list_clone_to);
result list_increase_capacity(struct list* list, const size_t increase_amount);
void list_destroy(struct list* list);