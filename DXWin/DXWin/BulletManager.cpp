#include "stdafx.h"
#include "BulletManager.h"
#include "DXGameObjectManager.h"

using namespace MyDirectX;

BulletManager::BulletManager(DXGameObjectManager* manager)
{
	mDXGameObjectManager = manager;
}

void BulletManager::CreatePreBullets(int preNum)
{
	for(int i = 0;i < preNum;i++)
	{
		CreateBullet();
	}
}

DXGameObject * BulletManager::GetBullet(TRANSFORM* transform,Tag tag)
{
	DXGameObject* pGame;
	//�I�u�W�F�N�g������Ύg���܂킷
	//�Ȃ���ΐV�������
	if(mBulletList.size() <= 0)
	{
		pGame = CreateBullet();
	}
	else
	{
		pGame = mBulletList.back();
		mBulletList.pop_back();
	}
	auto pGameTransform = pGame->GetTransform();
	auto scale = transform->Scale;
	auto pBullet = pGame->GetComponent<Bullet>();
	pBullet->SetVectol(0, 0.05f);
	//���@�̑傫����1�Ƃ��Ēe�̔䗦�����肷��
	auto scaleRatio = 0.3f;
	scale.x *= scaleRatio;
	scale.y *= scaleRatio;
	scale.z *= scaleRatio;
	pGameTransform->Position = transform->Position;
	//���@����ɃY����
	pGameTransform->Position.y = transform->Position.y + scale.y;
	pGameTransform->Scale = scale;
	pGameTransform->Rotation = transform->Rotation;
	pGame->GetComponent<MeshRenderer>()->SetColor();
	pGame->SetTag(tag);
	pGame->SetEnable(true);
	pGame->InitializeComponent();
	return pGame;
}

DXGameObject * BulletManager::GetBullet(TRANSFORM * transform, Tag tag, float x, float y)
{
	DXGameObject* pGame;
	//�I�u�W�F�N�g������Ύg���܂킷
	//�Ȃ���ΐV�������
	if (mBulletList.size() <= 0)
	{
		pGame = CreateBullet();
	}
	else
	{
		pGame = mBulletList.back();
		mBulletList.pop_back();
	}
	auto pGameTransform = pGame->GetTransform();
	auto scale = transform->Scale;
	auto pBullet = pGame->GetComponent<Bullet>();
	pBullet->SetVectol(x, y);
	//���@�̑傫����1�Ƃ��Ēe�̔䗦�����肷��
	auto scaleRatio = 0.3f;
	scale.x *= scaleRatio;
	scale.y *= scaleRatio;
	scale.z *= scaleRatio;
	pGameTransform->Position = transform->Position;
	pGameTransform->Scale = scale;
	pGameTransform->Rotation = transform->Rotation;
	pGame->GetComponent<MeshRenderer>()->SetColor();
	pGame->SetTag(tag);
	pGame->SetEnable(true);
	pGame->InitializeComponent();
	return pGame;
}

void BulletManager::ReturnBullet(DXGameObject * bullet)
{
	bullet->SetEnable(false);
	mBulletList.push_back(bullet);
}

DXGameObject * BulletManager::CreateBullet()
{
	auto game = mDXGameObjectManager->Instantiate();
	game->SetName("Bullet");
	game->SetTag(Tag::PlayerBullet);
	game->SetEnable(false);
	auto col = game->AddComponent<SquareCollider2D>();
	col->SetOneSide(col->GetOneSide() / 10.0f);
	game->AddComponent<Bullet>();
	auto tex = game->AddComponent<DXTexture>();
	tex->SetTexture(_T("Texture/Bullet3.png"));
	mBulletList.push_back(game);
	return game;
}
