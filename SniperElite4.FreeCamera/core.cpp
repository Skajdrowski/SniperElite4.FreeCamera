#include "core.h"

uintptr_t GetEntryPoint()
{
	static uintptr_t addr = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
	return addr;
}

uintptr_t _addr(uintptr_t addr)
{
	return GetEntryPoint() + addr;
}
