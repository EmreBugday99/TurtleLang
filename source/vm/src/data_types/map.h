#pragma once

#define MAP_INCLUDES\
	#include <stdlib.h>\
	#include <string.h>\
	#include <stdint.h>\
	#include <stdio.h>

#ifdef MAP_IMPLEMENTATION

#define MAP_FALSE 0
#define MAP_TRUE 1
#define MAP_AVAILABLE 0
#define MAP_NOT_AVAILABLE 1
#define MAP_LIST 2

#define GENERATE_MAP(T)\
	struct map_##T\
	{\
	T* map;\
	uint8_t* keys;\
	uint64_t capacity;\
	uint64_t elements;\
	};\
	GENERATE_MAP_CREATE(T)\
	GENERATE_MAP_INITIALIZER(T)\
	GENERATE_MAP_CLONE(T)\
	GENERATE_MAP_INCREASE_CAPACITY(T)\
	GENERATE_MAP_ADD(T)\
	GENERATE_MAP_GET_UNSAFE(T)\
	GENERATE_MAP_REMOVE(T)\
	GENERATE_MAP_KEY_AVAILABLE(T)

#define GENERATE_MAP_CREATE(T)\
	struct map_##T map_create_##T(uint64_t capacity)\
	{\
		return (struct map_##T)\
		{\
		.map = (T*)malloc(sizeof(T) * capacity),\
		.keys = (uint8_t*)malloc(sizeof(uint8_t) * capacity),\
		.capacity = capacity,\
		.elements = 0\
		};\
	}

#define GENERATE_MAP_INITIALIZER(T)\
	void map_initialize_##T(struct map_##T* map)\
	{\
		for (uint64_t i = 0; i <= map->capacity; i++)\
		{\
			uint8_t* ptr_to_key = map->keys + i;\
			*ptr_to_key = MAP_AVAILABLE;\
		}\
	}

#define GENERATE_MAP_ADD(T)\
	T* map_add_##T(struct map_##T* map, uint64_t key, T data)\
	{\
		if (key >= map->capacity)\
		{\
			uint64_t increase_count = key - map->capacity;\
			if (increase_count <= 0)\
				increase_count = 1;\
			if (map_increase_capacity_##T(map, increase_count) == MAP_FALSE)\
				return NULL;\
		}\
		if (map->keys[key] == MAP_NOT_AVAILABLE)\
			return NULL;\
		T* copy_location_data = memcpy(map->map + key, &data, sizeof(T));\
		if (copy_location_data == NULL)\
			return NULL;\
		uint8_t* ptr_to_key = map->keys + key; \
		*ptr_to_key = MAP_NOT_AVAILABLE;\
		map->elements++;\
		return map->map + key;\
	}

#define GENERATE_MAP_CLONE(T)\
	uint8_t map_clone_##T(struct map_##T* clone_from, struct map_##T* clone_to)\
	{\
		free(clone_to->map);\
		free(clone_to->keys);\
		clone_to->map = NULL;\
		clone_to->keys = NULL;\
		\
		clone_to->map = malloc(clone_from->capacity * sizeof(T));\
		clone_to->keys = malloc(clone_from->capacity * sizeof(uint8_t));\
		\
		if (clone_to->map == NULL || clone_to->keys == NULL)\
		{\
			free(clone_to->map);\
			free(clone_to->keys);\
			return MAP_FALSE;\
		}\
		clone_to->capacity = clone_from->capacity;\
		clone_to->elements = clone_from->elements;\
		\
		T* copy_location_map = memcpy(clone_to->map, clone_from->map, clone_from->capacity * sizeof(T));\
		uint8_t* copy_location_keys = memcpy(clone_to->keys, clone_from->keys, clone_from->capacity * sizeof(uint8_t));\
		if (copy_location_map == NULL || copy_location_keys == NULL)\
		{\
			/*Sames as free(clone_to->map)*/\
			free(copy_location_map);\
			/*Sames as free(clone_to->keys)*/\
			free(copy_location_keys);\
			return MAP_FALSE;\
		}\
		return MAP_TRUE;\
	}

#define GENERATE_MAP_INCREASE_CAPACITY(T)\
	uint8_t map_increase_capacity_##T(struct map_##T* map, uint64_t increase_count)\
	{\
		struct map_##T clone_map = map_create_##T(map->capacity);\
		if (map_clone_##T(map, &clone_map) == 0)\
			return MAP_FALSE;\
		\
		const uint64_t new_capacity = map->capacity + increase_count;\
		\
		map->map = malloc(new_capacity * sizeof(T));\
		map->keys = malloc(new_capacity * sizeof(uint8_t));\
		\
		T* copy_location_data = memcpy(map->map, clone_map.map, new_capacity * sizeof(T));\
		T* copy_location_keys = memcpy(map->keys, clone_map.keys, new_capacity * sizeof(uint8_t));\
		for (uint64_t i = map->capacity; i < new_capacity; i++)\
		{\
			uint8_t* ptr_to_key = map->keys + i;\
			*ptr_to_key = MAP_AVAILABLE;\
		}\
		\
		if (copy_location_data == NULL || copy_location_keys == NULL)\
		{\
			/*Sames as free(map->map)*/\
			free(copy_location_data);\
			/*Sames as free(map->keys)*/\
			free(copy_location_keys);\
			return MAP_FALSE;\
		}\
		map->capacity = new_capacity;\
		return MAP_TRUE;\
	}

#define GENERATE_MAP_GET_UNSAFE(T)\
	T map_get_unsafe_##T(struct map_##T* map, uint64_t key)\
	{\
		return map->map[key];\
	}

#define GENERATE_MAP_REMOVE(T)\
	void map_remove_##T(struct map_##T* map, uint64_t key)\
	{\
		uint8_t* ptr_to_key = map->keys + key;\
		*ptr_to_key = MAP_NOT_AVAILABLE;\
	}

#define GENERATE_MAP_KEY_AVAILABLE(T)\
	uint8_t map_is_available_##T(struct map_##T* map, uint64_t key)\
	{\
		return map->keys[key];\
	}
#endif