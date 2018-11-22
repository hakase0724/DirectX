#include "stdafx.h"
#include "DXExcuter.h"

using namespace MyDirectX;
DXExcuter::DXExcuter()
{
	//�ՓˊǗ��N���X�𐶐�
	mCollisionManager = std::make_unique<CollisionManager>();
	//�V�[���̓o�^����������
	mScene = nullptr;
}

void DXExcuter::SetScene(Scene * scene)
{
	//�V�[�����o�^����Ă�����V�[���̏I�����\�b�h���Ăяo��
	if (mScene != nullptr) mScene->SceneEnd();
	//�V�[����o�^����
	mScene = scene;
	//�o�^�V�[���̊J�n���\�b�h���Ă�
	mScene->SceneStart();
	//���s�Q�[���I�u�W�F�N�g�Ǘ��z����N���A����
	mExcuteObjectsList.clear();
	//���s�Q�[���I�u�W�F�N�g�Ǘ��z��ɃV�[����̃Q�[���I�u�W�F�N�g��ǉ�����
	mExcuteObjectsList = mScene->GetGameObjects();
}

void DXExcuter::Excute()
{
	//�V�[�����o�^����Ė�����Ώ������Ȃ�
	if (!mScene) return;

	/*���t���[���̏������s��*/
	//�V�[���̍X�V����
	mScene->SceneUpdate();
	//�R���C�_�[���i�[
	mCollisionManager->SetGameObjects(mExcuteObjectsList);
	//�Q�[���I�u�W�F�N�g�̍X�V����
	Update();
	//�S�Ă̍X�V�������I�������̍X�V����
	mScene->SceneLateUpdate();
	//�Q�[���I�u�W�F�N�g�̌�X�V����
	LateUpdate();
	//�Փˏ���
	mCollisionManager->Collision();
	//�`�揈��
	Render();
	//1�t���[���I�����̏���
	mScene->SceneEndFrame();
}

void DXExcuter::Update()
{
	for(auto game:mExcuteObjectsList)
	{
		if (!game->GetEnable()) continue;
		game->Update();
	}
}

void DXExcuter::LateUpdate()
{
	for (auto game : mExcuteObjectsList)
	{
		if (!game->GetEnable()) continue;
		game->LateUpdate();
	}
}

void DXExcuter::Render()
{
	mDXRescourceManager->GetDXManager()->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);
	for (auto game : mExcuteObjectsList)
	{
		if (!game->GetEnable()) continue;
		game->Render();
	}
	mDXRescourceManager->GetDXManager()->EndScene();
}
