#pragma once
#include "../data_types/vm_data.h"
#include "instruction_result.h"

// param1: stack ptr, param2: vm_data
typedef enum instruction_result(*instruction_callback)(void*, vm_data);