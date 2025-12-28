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

uintptr_t SigScan(const char* pattern, uint32_t pad, uint32_t lenght)
{
	hook::pattern Pattern(pattern);
	uintptr_t OpcodeAddr = Pattern.count(1).get(0).get_uintptr(pad);

	if (lenght != 0)
	{
		int32_t RIPOffset;
		Read(OpcodeAddr, RIPOffset);
		uintptr_t Addr = OpcodeAddr + lenght + RIPOffset;
		return Addr;
	}
	return OpcodeAddr;
}
