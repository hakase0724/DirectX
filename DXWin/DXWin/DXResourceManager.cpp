#include "stdafx.h"
#include "DXResourceManager.h"

using namespace MyDirectX;

DXResourceManager::DXResourceManager(HWND hwnd)
{
	//DirectSound�N���X
	mDXSound = std::make_unique<DXSound>(hwnd);
	//DirectX���\�[�X�Ǘ�
	mDXManager = std::make_unique<DXManager>(hwnd);
	//FPS�J�E���^�[�𐶐�
	mFPSCountor = std::make_unique<FPSCountor>();
}

DXGameObject * DXResourceManager::Instantiate()
{
	DXGameObject* game = new DXGameObject(mDXManager.get());
	game->SetID(mGameObjectCount);
	mGameObjectCount++;
	return game;
}

