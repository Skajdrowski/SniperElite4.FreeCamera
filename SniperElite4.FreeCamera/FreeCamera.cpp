#include "core.h"
#include "FreeCamera.h"
#include "se4/Camera.h"
#include "SettingsMgr.h"

unsigned int FreeCamera::ms_bEnabled = 0;

void FreeCamera::Init()
{
	CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Thread), nullptr, 0, nullptr);
}

void FreeCamera::Thread()
{
	while (true)
	{
		Camera* cam = GetCamera();
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraEnableKey) & 0x1)
			ms_bEnabled += 1;

		if (ms_bEnabled == 1)
		{
			Nop(_addr(0x11E93F9), 2);
			Nop(_addr(0x11E9401), 3);
			Nop(_addr(0x11E9407), 3);
			ms_bEnabled = 2;
		}
		else if (ms_bEnabled == 2)
		{
			if (cam)
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
		}
		else if (ms_bEnabled == 3)
		{
			Patch(_addr(0x11E93F9), {0x89, 0x01});
			Patch(_addr(0x11E9401), {0x89, 0x41, 0x04});
			Patch(_addr(0x11E9407), {0x89, 0x41, 0x08});
			ms_bEnabled = 0;
		}

		Sleep(1);
	}
}
