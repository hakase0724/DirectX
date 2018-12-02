#include "stdafx.h"
#include "DXResourceManager.h"
#include "DXGameObject.h"

using namespace MyDirectX;

DXResourceManager::DXResourceManager(HWND hwnd)
{
	//DirectSoundクラス
	mBGMDXSound = std::make_unique<DXSound>(hwnd, (LPWSTR)_T("Sound/bgm.wav"));
	mSEDXSound = std::make_unique<DXSound>(hwnd, (LPWSTR)_T("Sound/Shot.wav"));
	mSEDXSound->SetVolume(-1000);
	//DirectXリソース管理
	mDXManager = std::make_unique<DXManager>(hwnd);
	//FPSカウンターを生成
	mFPSCountor = std::make_unique<FPSCountor>();
	mCSVLoader = std::make_unique<CSVLoader>();
}

DXGameObject * DXResourceManager::Instantiate()
{
	DXGameObject* game = new DXGameObject(this);
	//各オブジェクトにIDを降る
	game->SetID(mGameObjectCount);
	mGameObjectCount++;
	return game;
}

