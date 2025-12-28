#pragma once

struct Camera;

class FreeCamera {
public:
	static void Init();
	static void Thread();
private:
	static Camera* cam;
	static unsigned int ms_bEnabled;
	static uintptr_t CordsInstruction;
};