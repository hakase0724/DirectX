#include "stdafx.h"
#include "DXGameObjectManager.h"

using namespace MyDirectX;
using namespace DirectX;
DXGameObjectManager::DXGameObjectManager(HWND hwnd)
{
	CreateResources(hwnd);
	CreateGameObject();
}

void DXGameObjectManager::CreateResources(HWND hwnd)
{
	//DirectX���\�[�X�Ǘ�
	mDXManager = std::make_unique<DXManager>(hwnd);
}

void DXGameObjectManager::CreateGameObject()
{
	//������X�t�B�A����
	auto sphere = Instantiate();
	sphere->AddComponent<DXSphere>();
	sphere->AddComponent<Mover>();
	//�����ʒu���Ⴄ�L���[�u����
	auto cube = Instantiate();
	auto transform = cube->GetTransform();
	transform.Position = XMFLOAT3(1.0f, 0.0f, 0.0f);
	cube->SetTransform(&transform);
	cube->AddComponent<DXCube>();
	cube->AddComponent<Mover>();
}

//�Q�[���I�u�W�F�N�g�����z��Ɋi�[�A������Q�[���I�u�W�F�N�g�̃|�C���^��Ԃ�
DXGameObject * DXGameObjectManager::Instantiate()
{
	mGameObjectsList.push_back(std::make_unique<DXGameObject>(mDXManager.get()));
	return mGameObjectsList.back().get();
}

BOOL DXGameObjectManager::Update()
{
	//���݂̓��͏�Ԃ��擾
	mDXManager->GetDXInput()->SetInputState();
	//���������I�u�W�F�N�g�̍X�V����
	for(auto itr = mGameObjectsList.begin();itr != mGameObjectsList.end();++itr)
	{
		itr->get()->Update();
	}
	if (mDXManager->GetDXInput()->GetInputState(DIK_ESCAPE))
		return FALSE;
	return TRUE;
}

void DXGameObjectManager::Render()
{
	//�o�b�t�@�N���A
	mDXManager->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);
	//���������I�u�W�F�N�g�̃����_�����O����
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		itr->get()->Render();
	}
	//��ʕ\��
	mDXManager->EndScene();
}


