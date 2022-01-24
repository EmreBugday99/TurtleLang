#include "instruction.h"
#include <stdlib.h>
#include "../token/token_type.h"

instruction_map instruction_map_create(size_t capacity)
{
	return (instruction_map) {
		.map = (instruction_callback*)malloc(capacity * sizeof(instruction_callback)),
		.elements = 0,
		.capacity = capacity
	};
}

void instruction_map_add(instruction_map* map, const unsigned int index, const instruction_callback callback)
{
	if (index > map->capacity)
		instruction_map_increase_capacity(map, index - map->capacity);

	map->map[index] = callback;
	map->elements++;
}

unsigned char instruction_map_remove(instruction_map* map, const unsigned index)
{
	if (index > map->capacity || map->elements <= 0)
		return 0;

	map->map[index] = 0;
	map->elements--;
	return 1;
}

void instruction_map_increase_capacity(instruction_map* map, size_t capacity)
{
	const size_t new_capacity = map->capacity + capacity;

	instruction_map copy_map = instruction_map_create(new_capacity);

	for (size_t i = 0; i < map->capacity; i++)
	{
		copy_map.map[i] = map->map[i];
	}

	free(map->map);
	map->map = NULL;
	map->map = (instruction_callback*)malloc(new_capacity * sizeof(instruction_callback));
	map->capacity = new_capacity;

	for (size_t i = 0; i < map->capacity; i++)
	{
		map->map[i] = copy_map.map[i];
	}
	free(copy_map.map);
}

void instruction_map_fill_standard_library(instruction_map* map)
{
	if (map->capacity < STANDARD_LIBRARY_INSTRUCTION_COUNT)
		instruction_map_increase_capacity(map, STANDARD_LIBRARY_INSTRUCTION_COUNT);

	map->map[TOKEN_NONE] = std_instruction_none;
	map->map[TOKEN_PUSH] = std_instruction_stack_push;
	map->map[TOKEN_POP] = std_instruction_stack_pop;
	map->map[TOKEN_ADD] = std_instruction_stack_add;
	map->map[TOKEN_SUBTRACT] = std_instruction_stack_subtract;
	map->map[TOKEN_MULTIPLICATION] = std_instruction_stack_multiply;
	map->map[TOKEN_DIVISION] = std_instruction_stack_divide;
	map->map[TOKEN_JUMP] = std_instruction_jump;
	map->map[TOKEN_COMPARE] = std_instruction_compare;
	map->map[TOKEN_JUMP_COMPARE] = std_instruction_jump_compare;

	map->elements += STANDARD_LIBRARY_INSTRUCTION_COUNT;
}