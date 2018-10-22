#include "stdafx.h"
#include "DXGameObjectManager.h"

using namespace MyDirectX;
using namespace DirectX;
DXGameObjectManager::DXGameObjectManager(HWND hwnd)
{
	CreateResources(hwnd);
	CreateGameObject();
	StoreCollider2D();
}

DXGameObjectManager::~DXGameObjectManager()
{
	for(auto col:mCollider2DList)
	{
		col->Exit();
		delete col;
	}
}

void DXGameObjectManager::CreateResources(HWND hwnd)
{
	//DirectX���\�[�X�Ǘ�
	mDXManager = std::make_unique<DXManager>(hwnd);
}

void DXGameObjectManager::CreateGameObject()
{
	auto test = Create<DXSquare>();
	test->SetName("MoveObject");
	test->AddComponent<Mover>();
	test->AddComponent<SquareCollider2D>();

	auto test2 = Create<DXSquare>();
	test2->SetName("NotMoveObject");
	auto transfrom = test2->GetTransform();
	transfrom.Position = XMFLOAT3(-2.0f, 0.0f, 0.0f);
	test2->SetTransform(&transfrom);
	test2->AddComponent<SquareCollider2D>();

	/*auto test3 = Create<DXSquare>();
	test3->SetName("NotMoveObject2");
	auto transfrom2 = test3->GetTransform();
	transfrom2.Position = XMFLOAT3(0.0f, 1.5f, 0.0f);
	test3->SetTransform(&transfrom2);
	test3->AddComponent<SquareCollider2D>();*/
}

void DXGameObjectManager::StoreCollider2D()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto com = itr->get()->GetComponent<Collider2D>();
		if (com != nullptr) mCollider2DList.push_back(com);
	}
}

//�Q�[���I�u�W�F�N�g�����z��Ɋi�[�A������Q�[���I�u�W�F�N�g�̃|�C���^��Ԃ�
DXGameObject * DXGameObjectManager::Instantiate()
{
	mGameObjectsList.push_back(std::make_unique<DXGameObject>(mDXManager.get()));
	return mGameObjectsList.back().get();
}
//�L���[�u����
DXGameObject * DXGameObjectManager::CreateCube()
{
	auto cube = Instantiate();
	cube->AddComponent<DXCube>();
	return cube;
}
//�X�t�B�A����
DXGameObject * DXGameObjectManager::CreateSphere()
{
	auto sphere = Instantiate();
	sphere->AddComponent<DXSphere>();
	return sphere;
}
//�l�p�`����
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
	//��������Փ˔���
	for(auto col:mCollider2DList)
	{
		for(auto col2:mCollider2DList)
		{
			if (col == col2) continue;
			col->isCollision(col2);
		}
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


