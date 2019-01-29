#include "stdafx.h"
#include "BombPool.h"
#include "DXTexture.h"
#include "ItemMover.h"

using namespace MyDirectX;

void BombPool::CreatePreBomb(int preNum)
{
	for(int i = 0;i < preNum;i++)
	{
		CreateBomb();
	}
}

DXGameObject * BombPool::GetBomb(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 scale)
{
	DXGameObject* pGame = nullptr;
	if (mBombList.size() <= 0)
	{
		pGame = CreateBomb();
	}
	else
	{
		pGame = mBombList.back();
		mBombList.pop_back();
	}
	auto gameTransform = pGame->GetTransform();
	gameTransform->Position = pos;
	gameTransform->Scale = scale;
	pGame->InitializeComponent();
	pGame->SetEnable(true);
	return pGame;
}

void BombPool::ReturnBomb(DXGameObject * bomb)
{
	mBombList.push_back(bomb);
}

DXGameObject * BombPool::CreateBomb()
{
	auto bomb = mScene->Instantiate();
	bomb->SetTag(StaticInstantiateItem);
	auto bombTex = bomb->AddComponent<DXTexture>();
	bombTex->SetTexture(L"Texture/bomb1.png");
	auto bombCom = bomb->AddComponent<Bomb>();
	bombCom->SetPool(this);
	auto bombCol = bomb->AddComponent<SquareCollider2D>();
	//コライダーは3分の1に
	bombCol->SetOneSide(bombCol->GetOneSide() / 3.0f);
	bomb->AddComponent<ItemMover>();
	mBombList.push_back(bomb);
	return bomb;
}
