#pragma once
#include "dinput.h"

namespace MyDirectX
{
	class DXInput
	{
	public:
		DXInput(HWND hwnd);
		~DXInput();
		HRESULT InitDirectInput(HWND hwnd);
		void SetInputState();
		//1ƒtƒŒ[ƒ€‘O‚Ì“ü—Íî•ñ‚ğŠi”[
		void SetPreBuffer();
		//‰Ÿ‚µ‚Â‚Ã‚¯‚Ä‚¢‚é
		BOOL GetInputState(int key);
		//‰Ÿ‚³‚ê‚½uŠÔ
		BOOL GetKeyDown(int key);
		//—£‚³‚ê‚½uŠÔ
		BOOL GetKeyUp(int key);
		void ExitDirectInput();
	private:
		const int isInputNum = 0x80;
		LPDIRECTINPUT8 mInput;
		LPDIRECTINPUTDEVICE8 mInputDevice;
		char mInputBuffer[256];
		char mPreInputBuffer[256];
	};
}

