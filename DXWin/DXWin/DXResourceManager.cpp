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

DXResourceManager::~DXResourceManager()
{
}

DXGameObject * DXResourceManager::Instantiate()
{
	DXGameObject* game = new DXGameObject(mDXManager.get());
	game->SetID(mGameObjectCount);
	game->SetEnable(true);
	mGameObjectCount++;
	return game;
}

bool DXResourceManager::IsEnd()
{
	if(mDXManager->GetDXInput()->GetInputState(DIK_ESCAPE))
	{
		return false;
	}
	return true;
}
