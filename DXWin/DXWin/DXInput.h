#pragma once
#include "dinput.h"

namespace MyDirectX
{
	class DXInput
	{
	public:
		HRESULT InitDirectInput(HWND hwnd);
		void SetInputState();
		BOOL GetInputState(int key);
		void ExitDirectInput();
	private:
		const int isInputNum = 0x80;
		LPDIRECTINPUT8 mInput;
		LPDIRECTINPUTDEVICE8 mInputDevice;
		char mInputBuffer[256];
	};
}

