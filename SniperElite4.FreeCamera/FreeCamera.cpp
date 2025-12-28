#include "core.h"
#include "FreeCamera.h"
#include "se4/Camera.h"
#include "SettingsMgr.h"

Camera* FreeCamera::cam = nullptr;
unsigned int FreeCamera::ms_bEnabled = 0;
uintptr_t FreeCamera::CordsInstruction = 0;

void FreeCamera::Init()
{
	CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Thread), nullptr, 0, nullptr);
}

void FreeCamera::Thread()
{
	while (true)
	{
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraEnableKey) & 0x1)
			ms_bEnabled += 1;

		if (ms_bEnabled == 1)
		{
			if (!cam)
				cam = GetCamera();

			if (!CordsInstruction)
				CordsInstruction = SigScan("89 ? 49 89 ? 8B ? ? 89 ? ? 8B ? ? 89 ? ? 8B ? ? 89 ? ? 8B ? ? 89 ? ? 8B ? ? 89 ? ? 8B ? ? 89 ? ? 8B ? ? 89 ? ? 8B ? ? 89 ? ? 8B ? ? 89 ? ? 8B ? ? 89 ? ? 8B ? ? 89 ? ? F2");

			Nop(CordsInstruction, 2);
			Nop(CordsInstruction + 8, 3);
			Nop(CordsInstruction + 14, 3);
			ms_bEnabled = 2;
		}
		else if (ms_bEnabled == 2)
		{
			float speed = SettingsMgr->fFreeCameraSpeed;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeySlowDown))
				speed /= SettingsMgr->fFreeCameraModifierScale;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeySpeedUp))
				speed *= SettingsMgr->fFreeCameraModifierScale;

			Vector fwd = cam->Rotation.GetForward();
			Vector up = cam->Rotation.GetUp();
			Vector right = cam->Rotation.GetRight();
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyForward))
				cam->Position += fwd * speed * 1;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyBack))
				cam->Position += fwd * speed * -1;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyUp))
				cam->Position += up * speed * 1;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyDown))
				cam->Position += up * speed * -1;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRight))
				cam->Position += right * speed * 1;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyLeft))
				cam->Position += right * speed * -1;
		}
		else if (ms_bEnabled == 3)
		{
			Patch(CordsInstruction, {0x89, 0x01});
			Patch(CordsInstruction + 8, {0x89, 0x41, 0x04});
			Patch(CordsInstruction + 14, {0x89, 0x41, 0x08});
			ms_bEnabled = 0;
		}

		Sleep(1);
	}
}
