#include "Camera.h"
#include "..\FreeCamera.h"
#include "..\core.h"
Camera* GetCamera()
{
	return *(Camera**)(SigScan("4C ? ? ? ? ? ? 45 31 ? 0F 29 ? ? ? 49 89", 3, 4));
}
