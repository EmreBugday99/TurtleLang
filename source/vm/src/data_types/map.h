#pragma once
#include <stdint.h>
#include "../result.h"

/*		Byte Alignment
 *	available
 *  indicator   data
 *  -			--------
 *  0			********
 *  -			--------
 */

struct map;

void* map_create(uint64_t capacity, uint64_t data_size);
void* map_add(struct map* map, uint64_t key, void* data);
void* map_remove(struct map* map, uint64_t key);
void* map_get_unsafe(struct map* map, uint64_t key);
result map_increase_capacity(struct map* map, uint64_t increase_count);
result map_clone(struct map* clone_from, struct map* clone_to);
result map_is_key_available(struct map* map, uint64_t key);
