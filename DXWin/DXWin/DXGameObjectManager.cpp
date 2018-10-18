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
	auto test = Create<DXSquare>();
	test->AddComponent<Mover>();
	test->AddComponent<SquareCollider2D>();

	auto test2 = Create<DXSquare>();
	auto transfrom = test2->GetTransform();
	transfrom.Position = XMFLOAT3(-2.0f, 0.0f, 0.0f);
	test2->SetTransform(&transfrom);
	test2->AddComponent<SquareCollider2D>();

	auto test3 = Create<DXSquare>();
	auto transfrom2 = test3->GetTransform();
	transfrom2.Position = XMFLOAT3(2.0f, 0.0f, 0.0f);
	test3->SetTransform(&transfrom2);
	test3->AddComponent<SquareCollider2D>();
}

//�Q�[���I�u�W�F�N�g�����z��Ɋi�[�A������Q�[���I�u�W�F�N�g�̃|�C���^��Ԃ�
DXGameObject * DXGameObjectManager::Instantiate()
{
	mGameObjectsList.push_back(std::make_unique<DXGameObject>(mDXManager.get()));
	return mGameObjectsList.back().get();
}

DXGameObject * DXGameObjectManager::CreateCube()
{
	auto cube = Instantiate();
	cube->AddComponent<DXCube>();
	return cube;
}

DXGameObject * DXGameObjectManager::CreateSphere()
{
	auto sphere = Instantiate();
	sphere->AddComponent<DXSphere>();
	return sphere;
}

DXGameObject * DXGameObjectManager::CreateSquare()
{
	auto square = Instantiate();
	square->AddComponent<DXSquare>();
	return square;
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
	if (mDXManager->GetDXInput()->GetInputState(DIK_ESCAPE))return FALSE;
	return TRUE;
}

void DXGameObjectManager::LateUpdate()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		itr->get()->LateUpdate();
	}
}

void DXGameObjectManager::FixedUpdate()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		itr->get()->FixedUpdate();
	}
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


