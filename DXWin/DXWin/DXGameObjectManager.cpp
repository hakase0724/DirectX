#include "stdafx.h"
#include "DXGameObjectManager.h"
#include "DXManager.h"

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
	auto test = InstantiateTemp();
	test->SetName("MoveObject");
	test->SetTag(Tag::PlayerTag);
	test->AddComponent<Mover>();
	auto col = test->AddComponent<SquareCollider2D>();
	auto player = test->AddComponent<Player>();
	player->SetManager(this);
	col->SetOneSide(col->GetOneSide() / 10.0f);

	/*auto test3 = InstantiateTemp();
	test3->SetName("NotMoveObject2");
	auto transfrom2 = test3->GetTransform();
	transfrom2.Position = XMFLOAT3(0.0f,1.0f, 0.0f);
	test3->SetTransform(&transfrom2);
	test3->SetTag(Tag::EnemyTag);
	test3->AddComponent<SquareCollider2D>();*/
}

void DXGameObjectManager::StoreCollider2D()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (!game->GetEnable()) continue;
		auto com = game->GetComponent<Collider2D>();
		
		if (com != nullptr) mCollider2DList.push_back(com);

	}
}

bool DXGameObjectManager::IsCollisionJudge(Tag shooter, Tag bullet)
{
	//�����^�O�Ȃ画�肵�Ȃ�
	if (shooter == bullet) return false;
	//���@�Ǝ��@�̒e�͔��肵�Ȃ�
	if (shooter == Tag::PlayerTag && bullet == Tag::PlayerBullet) return false;
	//�G�@�ƓG�@�̒e�͔��肵�Ȃ�
	if (shooter == Tag::EnemyTag && bullet == Tag::EnemyBullet) return false;
	return true;
}

//�Q�[���I�u�W�F�N�g�����z��Ɋi�[�A������Q�[���I�u�W�F�N�g�̃|�C���^��Ԃ�
DXGameObject * DXGameObjectManager::Instantiate()
{
	mGameObjectsList.push_back(std::make_unique<DXGameObject>(mDXManager.get()));
	mGameObjectCounter++;
	auto game = mGameObjectsList.back().get();
	game->SetID(mGameObjectCounter);
	game->SetEnable(true);
	return game;
}
//�Q�[�����Ő�������
DXGameObject * DXGameObjectManager::InstantiateTemp()
{
	mTempGameObjectsList.push_back(std::make_unique<DXGameObject>(mDXManager.get(),this));
	mGameObjectCounter++;
	auto game = mTempGameObjectsList.back().get();
	game->SetID(mGameObjectCounter);
	game->AddComponent<DXSquare>();
	game->SetEnable(true);
	return game;
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
	mCollider2DList.clear();
	StoreCollider2D();
	//���������I�u�W�F�N�g�̍X�V����
	for(auto itr = mGameObjectsList.begin();itr != mGameObjectsList.end();++itr)
	{
		auto game = itr->get();
		if(game->GetEnable()) itr->get()->Update();
	}
	if (mDXManager->GetDXInput()->GetInputState(DIK_ESCAPE))return FALSE;
	return TRUE;
}

void DXGameObjectManager::LateUpdate()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (game->GetEnable()) itr->get()->LateUpdate();
	}
	//�����蔻��
	for(auto col:mCollider2DList)
	{
		auto col1Tag = col->GetTag();
		//���@�܂��͓G�@�̃R���C�_�[�̂ݒ��o
		if (col1Tag == Tag::PlayerBullet) continue;
		if (col1Tag == Tag::EnemyBullet) continue;
		for(auto col2:mCollider2DList)
		{
			if (!IsCollisionJudge(col1Tag, col2->GetTag())) continue;
			col->IsCollision(col2);
		}
	}
}

void DXGameObjectManager::FixedUpdate()
{
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (game->GetEnable()) itr->get()->FixedUpdate();
	}
}

void DXGameObjectManager::Render()
{
	//�o�b�t�@�N���A
	mDXManager->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);
	//���������I�u�W�F�N�g�̃����_�����O����
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (game->GetEnable()) itr->get()->Render();
	}
	//��ʕ\��
	mDXManager->EndScene();
	//1�t���[�����ɒǉ��������ꂽ���̂�����ΊǗ����X�g�ɒǉ�����
	for (auto itr = mTempGameObjectsList.begin(); itr != mTempGameObjectsList.end(); ++itr)
	{
		//���g�̂Ȃ����̂͒ǉ����Ȃ�
		if (*itr == nullptr) continue;
		mGameObjectsList.push_back(std::move(*itr));
	}
	mTempGameObjectsList.clear();
	mDXManager->GetDXInput()->SetPreBuffer();
}

bool DXGameObjectManager::IsEnable(UINT id)
{
	bool result = false;
	for (auto itr = mGameObjectsList.begin(); itr != mGameObjectsList.end(); ++itr)
	{
		auto game = itr->get();
		if (game->GetID() != id) continue;
		if(game->GetEnable())
		{
			result = true;
			break;
		}
	}
	return result;
}


