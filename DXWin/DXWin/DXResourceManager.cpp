#include "stdafx.h"
#include "DXResourceManager.h"
#include "DXGameObject.h"

using namespace MyDirectX;

DXResourceManager::DXResourceManager(HWND hwnd)
{
	//BGM�Ǘ��N���X
	mBGMDXSound = std::make_unique<DXSound>(hwnd, (LPWSTR)_T("Sound/bgm.wav"));
	//�V���b�g���Ǘ��N���X
	mSEDXSound = std::make_unique<DXSound>(hwnd, (LPWSTR)_T("Sound/Shot.wav"));
	//���j��
	mExplosionEffectSound = std::make_unique<DXSound>(hwnd, (LPWSTR)_T("Sound/ExplosionEffect.wav"));
	//���ʂ�������
	mSEDXSound->SetVolume(-1000);
	//DirectX���\�[�X�Ǘ�
	mDXManager = std::make_unique<DXManager>(hwnd);
	//FPS�J�E���^�[�𐶐�
	mFPSCountor = std::make_unique<FPSCountor>();
	//CSV�ǂݍ��݃N���X
	mCSVLoader = std::make_unique<CSVLoader>();
}

DXGameObject * DXResourceManager::Instantiate()
{
	DXGameObject* game = new DXGameObject(this);
	//�e�I�u�W�F�N�g��ID���~��
	game->SetID(mGameObjectCount);
	mGameObjectCount++;
	return game;
}

