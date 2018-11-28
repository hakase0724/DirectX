#include "stdafx.h"
#include "BulletPool.h"
#include "MeshRenderer.h"
#include "DXTexture.h"

using namespace MyDirectX;

void BulletPool::CreatePreBullets(int preNum)
{
	for (int i = 0; i < preNum; i++)
	{
		CreateBullet();
	}
}

DXGameObject * BulletPool::GetBullet(TRANSFORM * transform, Tag tag)
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

DXGameObject * BulletPool::GetBullet(TRANSFORM * transform, Tag tag, float x, float y)
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

void BulletPool::ReturnBullet(DXGameObject * bullet)
{
	mBulletList.push_back(bullet);
}

DXGameObject * BulletPool::CreateBullet()
{
	auto game = mScene->Instantiate();
	game->SetName("Bullet");
	game->SetTag(Tag::PlayerBullet);
	auto col = game->AddComponent<SquareCollider2D>();
	col->SetOneSide(col->GetOneSide() / 10.0f);
	auto bullet = game->AddComponent<Bullet>();
	bullet->SetBulletPool(this);
	auto tex = game->AddComponent<DXTexture>();
	tex->SetTexture(_T("Texture/Bullet3.png"));
	mBulletList.push_back(game);
	return game;
}
