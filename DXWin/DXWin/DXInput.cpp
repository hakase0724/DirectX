//http://princess-tiara.biz/directx/?chapter=13 <-�Q�l�T�C�g
#include "stdafx.h"
#include "DXInput.h"
#include "dinput.h"
//�������G���[�f����邩���`���Ă܂Ƃ߂�����
#include "dinputex.h"

#pragma comment(lib , "dinput8.lib")
//GUID�n�g���̂ɕK�v������
#pragma comment(lib, "dxguid.lib")
//�����ƃG���[�f�����񂾂���
#define INITGUID

//������Ă���L�[�Ƃ��̒l�̘_���ςƂ�Ɛ^�ɂȂ�
const int isInputNum = 0x80;
//���̓C���^�[�t�F�[�X
LPDIRECTINPUT8 mInput;
//���̓f�o�C�X
LPDIRECTINPUTDEVICE8 mInputDevice;
//���͏�Ԃ�ێ�����
char mInputBuffer[256];

//�������֐�
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
	//���͂̎����@�O�ʂɂ���Ƃ��̂ݎ擾�����͂�Ɛ肵�Ȃ�
	hr = mInputDevice->SetCooperativeLevel(hwnd,DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr))
	{
		ExitDirectInput();
		return S_FALSE;
	}
	//���͎�t
	mInputDevice->Acquire();
	return S_OK;
}
//���݂̓��͏�Ԃ�ێ�����
void SetInputState()
{
	mInputDevice->GetDeviceState(sizeof(mInputBuffer), (LPVOID)&mInputBuffer);
}
//�w�肵���L�[�̓��͏󋵂��m�F����
BOOL GetInputState(int key)
{
	if (mInputBuffer[key] & isInputNum) return TRUE;
	else return FALSE;
}
//�I���֐�
void ExitDirectInput()
{
	//���͋���
	mInputDevice->Unacquire();
	if (mInput) mInput->Release();
	if (mInputDevice)mInputDevice->Release();
}
