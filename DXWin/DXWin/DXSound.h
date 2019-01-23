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
		//‰¹—Êİ’è
		void SetVolume(LONG volume) { mDsBuffer->SetVolume(volume); }
		//‰¹‚ğÅ‰‚©‚çÄ¶‚Å‚«‚é‚æ‚¤‚É‚·‚é
		void ResetSound();
		void Play();
		void Stop();
	private:
		IDirectSound8* mDirectSound;
		IDirectSoundBuffer8* mDsBuffer;
		bool OpenWave(TCHAR *filepath, WAVEFORMATEX &waveFormatEx, char** ppData, DWORD &dataSize);
	};

}


