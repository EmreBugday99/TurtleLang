#include "map.h"
#include <stdlib.h>
#include <string.h>
#include "limits.h"
#include "../math/clamp.h"

#define MAP_AVAILABLE 1
#define MAP_NOT_AVAILABLE 0

GENERATE_CLAMP(uint64_t)

struct map
{
	void* map;
	uint64_t capacity;
	uint64_t data_size;
	uint64_t elements;
};

void* map_create(uint64_t capacity, uint64_t data_size)
{
	if (capacity <= 0 || data_size <= 0)
		return NULL;

	struct map* map = malloc(sizeof(struct map));
	if (map == NULL)
		return NULL;

	map->data_size = data_size + sizeof(uint8_t);
	map->capacity = capacity;
	map->elements = 0;
	const uint64_t map_allocation_size = capacity * map->data_size;

	map->map = malloc(map_allocation_size);
	if (map->map == NULL)
	{
		free(map);
		return NULL;
	}
	for (uint64_t i = 0; i < map->capacity; i++)
	{
		uint8_t* map_as_bytes = (uint8_t*)map->map + (i * map->data_size);
		*map_as_bytes = MAP_AVAILABLE;
	}

	return map;
}

void* map_add(struct map* map, uint64_t key, void* data)
{
	if (map == NULL)
		return NULL;

	uint64_t increase_count = _abs64(key - map->capacity);
	math_clamp_uint64_t(&increase_count, 1, ULLONG_MAX);
	// 5 10 | 10 - 5 = 5
	// 1 | 1 - 1 = 0
	if (key >= map->capacity && map_increase_capacity(map, increase_count) == RESULT_FALSE)
		return NULL;

	uint8_t* first_byte = (uint8_t*)map->map + (key * map->data_size);
	if (map_is_key_available(map, key) == RESULT_FALSE)
		return NULL;

	void* memory_location = memcpy(first_byte + sizeof(uint8_t), data, map->data_size - sizeof(unsigned char));
	if (memory_location == NULL)
		return NULL;

	*first_byte = MAP_NOT_AVAILABLE;
	map->elements++;
	return memory_location;
}

void* map_remove(struct map* map, uint64_t key)
{
	if (map == NULL || map->elements <= 0)
		return NULL;

	uint8_t* first_byte = (uint8_t*)map->map + (key * map->data_size);
	*first_byte = MAP_AVAILABLE;

	map->elements--;
	return first_byte + sizeof(uint8_t);
}

void* map_get_unsafe(struct map* map, uint64_t key)
{
	if (map == NULL)
		return NULL;

	return (char*)map->map + 1 + (key * map->data_size);
}

result map_increase_capacity(struct map* map, uint64_t increase_count)
{
	if (map == NULL)
		return RESULT_FALSE;

	struct map* clone_map = map_create(map->capacity, map->data_size - sizeof(int8_t));
	map_clone(map, clone_map);

	// we are going to use this pointer as a last resort backup
	// if we fail to allocate memory properly for the clone_to map.
	void* ptr_to_map = map->map;
	map->map = malloc((map->capacity + increase_count) * sizeof(map->data_size));
	if (map->map == NULL)
	{
		// setting the clone_to map's ptr to it's original memory index.
		map->map = ptr_to_map;
		free(clone_map->map);
		free(clone_map);
		return RESULT_FALSE;
	}

	map->capacity += increase_count;
	void* memory_location = memcpy(map->map, clone_map->map, map->capacity * map->data_size);
	if (memory_location == NULL)
	{
		map->map = ptr_to_map;
		map->capacity = clone_map->capacity;
		free(clone_map->map);
		free(clone_map);
		return RESULT_FALSE;
	}

	uint8_t* memory_as_byte = (uint8_t*)memory_location;
	for (uint64_t i = clone_map->capacity; i < map->capacity * map->data_size; i++)
	{
		uint8_t* byte = memory_as_byte + i;
		*byte = MAP_AVAILABLE;
	}

	// everything worked out fine, we no longer need to keep the memory block for safety reasons.
	free(ptr_to_map);
	free(clone_map->map);
	free(clone_map);
	ptr_to_map = NULL;

	return RESULT_TRUE;
}

result map_clone(struct map* clone_from, struct map* clone_to)
{
	if (clone_from == NULL || clone_from->map == NULL || clone_to == NULL)
		return RESULT_FALSE;

	// we are going to use this pointer as a last resort backup
	// if we fail to allocate memory properly for the clone_to map.
	void* ptr_to_clone_to_map = clone_to->map;

	clone_to->map = malloc(clone_from->capacity * clone_from->data_size);
	if (clone_to->map == NULL)
	{
		// setting the clone_to map's ptr to it's original memory index.
		clone_to->map = ptr_to_clone_to_map;
		return RESULT_FALSE;
	}
	// everything worked out fine, we no longer need to keep the memory block for safety reasons.
	free(ptr_to_clone_to_map);
	ptr_to_clone_to_map = NULL;

	clone_to->capacity = clone_from->capacity;
	clone_to->data_size = clone_from->data_size;
	clone_to->elements = clone_from->elements;

	void* memory_start = memcpy(clone_to->map, clone_from->map, clone_to->capacity * clone_to->data_size);
	if (memory_start == NULL)
		return RESULT_FALSE;

	return RESULT_TRUE;
}

result map_is_key_available(struct map* map, uint64_t key)
{
	if (key > map->capacity)
		return RESULT_FALSE;

	const uint8_t* map_as_bytes = (uint8_t*)map->map + (key * map->data_size);
	if (*map_as_bytes == MAP_AVAILABLE)
		return RESULT_TRUE;

	return RESULT_FALSE;
}