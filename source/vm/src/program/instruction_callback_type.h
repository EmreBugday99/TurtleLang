#pragma once
#include "../data_types/vm_data.h"
#include "instruction_result.h"

typedef enum instruction_result(*instruction_callback)(void*, vm_data);