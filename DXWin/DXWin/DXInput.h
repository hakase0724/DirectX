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
		//1フレーム前の入力情報を格納
		void SetPreBuffer();
		//押しつづけている
		BOOL GetInputState(int key);
		//押された瞬間
		BOOL GetKeyDown(int key);
		//離された瞬間
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

