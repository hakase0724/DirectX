#include "stdafx.h"
#include "DXGameManager.h"

using namespace MyDirectX;
DXGameManager::DXGameManager(HWND hwnd)
{
	//�V�[�����o�^�p�|�C���^
	std::unique_ptr<Scene> scene;
	//�@�\�N���X���܂Ƃ߂�����
	mDXResourceManager = std::make_unique<DXResourceManager>(hwnd);
	//�Q�[�����[�v�����s����N���X
	mDXExcuter = std::make_unique<DXExcuter>();
	mDXExcuter->SetDXResourceManager(mDXResourceManager.get());
	
	//�^�C�g���V�[������
	auto title = new TitleScene();
	title->SetDXResourceManager(mDXResourceManager.get());
	title->Init();
	scene.reset(title);
	mSceneList.push_back(std::move(scene));
	//�v���C�V�[������
	auto play = new PlayScene();
	play->SetDXResourceManager(mDXResourceManager.get());
	play->Init();
	scene.reset(play);
	mSceneList.push_back(std::move(scene));
	//���U���g�V�[������
	auto result = new ResultScene();
	result->SetDXResourceManager(mDXResourceManager.get());
	result->Init();
	scene.reset(result);
	mSceneList.push_back(std::move(scene));
	//���t���b�V�����[�g�ɉ����Đ��������Ԋu��ݒ肷��
	auto hdc = GetDC(hwnd);
	auto rate = GetDeviceCaps(hdc, VREFRESH);
	int intarval = 0;
	if (rate <= 60) intarval = 1;
	if (rate >= 120) intarval = 2;
	SetVsyncIntarval(intarval);
}

void DXGameManager::Initialize()
{
	mSceneIndex = 0;
	mSceneCount = mSceneList.size();
	mDXExcuter->SetScene(mSceneList[mSceneIndex].get());
}

bool DXGameManager::Update()
{
	//���݂̓��͂��擾
	mDXResourceManager->SetInputState();
	//FPS�v�Z
	mDXResourceManager->UpdateFPS();
	//���������s
	mDXExcuter->Excute();
	//�G�X�P�[�v��������Ă�����I������
	if (mDXResourceManager->GetKey(DIK_ESCAPE))return false;
	//�V�[�����I�����Ă�����؂�ւ���
	if (mDXExcuter->IsSceneEnd()) SceneChange();
	//���t���[���̂��߂Ɍ��݂̓��͏󋵂�ۑ�
	mDXResourceManager->SetPreBuffer();
	return true;
}

void DXGameManager::SceneChange()
{
	mSceneIndex = (++mSceneIndex) % mSceneCount;
	mDXExcuter->SetScene(mSceneList[mSceneIndex].get());
}
