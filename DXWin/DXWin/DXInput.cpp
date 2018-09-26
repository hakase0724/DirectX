//http://princess-tiara.biz/directx/?chapter=13 <-参考サイト
#include "stdafx.h"
#include "DXInput.h"
#include "dinput.h"
//未解決エラー吐かれるから定義してまとめたもの
#include "dinputex.h"

#pragma comment(lib , "dinput8.lib")
//GUID系使うのに必要だった
#pragma comment(lib, "dxguid.lib")
//無いとエラー吐かれるんだって
#define INITGUID

//押されているキーとこの値の論理積とると真になる
const int isInputNum = 0x80;
//入力インターフェース
LPDIRECTINPUT8 mInput;
//入力デバイス
LPDIRECTINPUTDEVICE8 mInputDevice;
//入力状態を保持する
char mInputBuffer[256];

//初期化関数
HRESULT InitDirectInput(HWND hwnd)
{
	HINSTANCE hinst = (HINSTANCE)GetWindowLong(hwnd,GWL_HINSTANCE);
	HRESULT hr = DirectInput8Create(hinst,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&mInput,NULL);
	if (FAILED(hr)) return S_FALSE;
	hr = mInput->CreateDevice(GUID_SysKeyboard, &mInputDevice, NULL);
	if (FAILED(hr)) 
	{
		ExitDirectInput();
		return S_FALSE;
	}
	hr = mInputDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		ExitDirectInput();
		return S_FALSE;
	}
	//入力の取り方　前面にいるときのみ取得し入力を独占しない
	hr = mInputDevice->SetCooperativeLevel(hwnd,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr))
	{
		ExitDirectInput();
		return S_FALSE;
	}
	//入力受付
	mInputDevice->Acquire();
	return S_OK;
}
//現在の入力状態を保持する
void SetInputState()
{
	mInputDevice->GetDeviceState(sizeof(mInputBuffer), (LPVOID)&mInputBuffer);
}
//指定したキーの入力状況を確認する
BOOL GetInputState(int key)
{
	if (mInputBuffer[key] & isInputNum) return TRUE;
	else return FALSE;
}
//終了関数
void ExitDirectInput()
{
	//入力拒否
	mInputDevice->Unacquire();
	if (mInput) mInput->Release();
	if (mInputDevice)mInputDevice->Release();
}
