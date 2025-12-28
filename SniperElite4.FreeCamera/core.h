#pragma once
#include "utils/MemoryMgr.h"
#include "utils/Patterns.h"

using namespace Memory::VP;

uintptr_t GetEntryPoint();
uintptr_t _addr(uintptr_t addr);
uintptr_t SigScan(const char* pattern, uint32_t pad = 0, uint32_t lenght = 0);