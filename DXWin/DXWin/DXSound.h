#pragma once
#include <mmsystem.h>
#include <dsound.h>
#include <windows.h>
#include <tchar.h>
namespace MyDirectX
{
	class DXSound
	{
	public:
		DXSound(HWND hwnd);
		DXSound(HWND hwnd, LPWSTR sourcePath);
		~DXSound() {};
		//���ʐݒ�
		void SetVolume(LONG volume) { mDsBuffer->SetVolume(volume); }
		//�����ŏ�����Đ��ł���悤�ɂ���
		void ResetSound();
		void Play();
		void Stop();
	private:
		IDirectSound8* mDirectSound;
		IDirectSoundBuffer8* mDsBuffer;
		bool OpenWave(TCHAR *filepath, WAVEFORMATEX &waveFormatEx, char** ppData, DWORD &dataSize);
	};

}


