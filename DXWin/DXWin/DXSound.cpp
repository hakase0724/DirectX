#include "stdafx.h"
#include "DXSound.h"

#pragma comment ( lib, "winmm.lib" )
#pragma comment (lib ,"dsound.lib")
#pragma comment (lib,"dxguid.lib")

using namespace MyDirectX;
DXSound::DXSound(HWND hwnd)
{
	// Waveファイルオープン
	WAVEFORMATEX wFmt;
	char *pWaveData = 0;
	DWORD waveSize = 0;
	auto path = (LPWSTR)_T("Sound/bgm.wav");
	auto open = OpenWave(path, wFmt, &pWaveData, waveSize);

	HRESULT hr = DirectSoundCreate8(NULL,&mDirectSound,NULL);
	
	mDirectSound->SetCooperativeLevel(hwnd,DSSCL_NORMAL);

	DSBUFFERDESC dsBufferDesc;
	dsBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	dsBufferDesc.dwFlags = 0;
	dsBufferDesc.dwBufferBytes = waveSize;
	dsBufferDesc.dwReserved = 0;
	dsBufferDesc.lpwfxFormat = &wFmt;
	dsBufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer* tmpBuffer = 0;
	hr = mDirectSound->CreateSoundBuffer(&dsBufferDesc,&tmpBuffer,NULL);
	tmpBuffer->QueryInterface(IID_IDirectSoundBuffer8,(void**)&mDsBuffer);
	tmpBuffer->Release();

	// セカンダリバッファにWaveデータ書き込み
	LPVOID lpvWrite = 0;
	DWORD dwLength = 0;
	if (DS_OK == mDsBuffer->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER)) 
	{
		memcpy(lpvWrite, pWaveData, dwLength);
		mDsBuffer->Unlock(lpvWrite, dwLength, NULL, 0);
	}
	delete[] pWaveData; // 元音はもういらない
}


DXSound::~DXSound()
{
	/*if (mDirectSound)mDirectSound->Release();
	if (mDsBuffer)mDsBuffer->Release();*/
}

void DXSound::Play()
{
	mDsBuffer->Play(0, 0, 0);
}

void DXSound::Stop()
{
	mDsBuffer->Stop();
}

bool DXSound::OpenWave(TCHAR * filepath, WAVEFORMATEX & waveFormatEx, char ** ppData, DWORD & dataSize)
{
	if (filepath == 0) return false;

	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;
	// Waveファイルオープン
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpen(filepath, &mmioInfo, MMIO_READ);
	if (!hMmio)
		return false; // ファイルオープン失敗

// RIFFチャンク検索
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}

	// フォーマットチャンク検索
	MMCKINFO formatChunk;
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}
	DWORD fmsize = formatChunk.cksize;
	DWORD size = mmioRead(hMmio, (HPSTR)&waveFormatEx, fmsize);
	if (size != fmsize) {
		mmioClose(hMmio, 0);
		return false;
	}

	mmioAscend(hMmio, &formatChunk, 0);

	// データチャンク検索
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return false;
	}
	*ppData = new char[dataChunk.cksize];
	size = mmioRead(hMmio, (HPSTR)*ppData, dataChunk.cksize);
	if (size != dataChunk.cksize) {
		delete[] * ppData;
		return false;
	}
	dataSize = size;

	// ハンドルクローズ
	mmioClose(hMmio, 0);

	return true;
}
