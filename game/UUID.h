#pragma once
#include <stdint.h>
#include "Context.h"

#if defined(CH_LINUX)
uint64_t GenerateUUID_Linux();
#define GenerateUUID GenerateUUID_Linux
#elif defined(CH_WINDOWS)
uint64_t GenerateUUID_Win();
#define GenerateUUID GenerateUUID_Win
#endif
