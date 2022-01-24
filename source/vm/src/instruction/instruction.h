#pragma once
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "instructions.h"

typedef struct
{
	instruction_callback callback;
	vm_data data;
} instruction;

typedef struct
{
	instruction_callback* map;
	size_t elements;
	size_t capacity;
} instruction_map;

instruction_map instruction_map_create(size_t capacity);
void instruction_map_add(instruction_map* map, const unsigned int index, const instruction_callback callback);
unsigned char instruction_map_remove(instruction_map* map, const unsigned index);
void instruction_map_increase_capacity(instruction_map* map, size_t capacity);
void instruction_map_fill_standard_library(instruction_map* map);

#endif