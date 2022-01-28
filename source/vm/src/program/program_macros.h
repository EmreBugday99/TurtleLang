#pragma once

#define FILL_STANDARD_LIBRARY_TO_INSTRUCTION_MAP(instruction_map) \
		struct callback inst_stack_none = { &instruction_callback_none };\
		struct callback inst_stack_push = { &instruction_callback_stack_push };\
		struct callback inst_stack_pop = { &instruction_callback_stack_pop };\
		struct callback inst_stack_add = { &instruction_callback_stack_add };\
		struct callback inst_stack_subtract = { &instruction_callback_stack_subtract };\
		struct callback inst_stack_multiply = { &instruction_callback_stack_multiplication };\
		struct callback inst_stack_divide = { &instruction_callback_stack_division };\
		struct callback inst_jump = { &instruction_callback_jump };\
		struct callback inst_stack_compare = { &instruction_callback_stack_compare };\
		struct callback inst_stack_jump_compare = { &instruction_callback_stack_jump_compare };\
		map_add(instruction_map, TOKEN_NONE, &inst_stack_none);\
		map_add(instruction_map, TOKEN_PUSH, &inst_stack_push);\
		map_add(instruction_map, TOKEN_POP, &inst_stack_pop);\
		map_add(instruction_map, TOKEN_ADD, &inst_stack_add);\
		map_add(instruction_map, TOKEN_SUBTRACT, &inst_stack_subtract);\
		map_add(instruction_map, TOKEN_MULTIPLICATION, &inst_stack_multiply);\
		map_add(instruction_map, TOKEN_DIVISION, &inst_stack_divide);\
		map_add(instruction_map, TOKEN_JUMP, &inst_jump);\
		map_add(instruction_map, TOKEN_COMPARE, &inst_stack_compare);\
		map_add(instruction_map, TOKEN_JUMP_COMPARE, &inst_stack_jump_compare);