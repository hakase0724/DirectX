#include "stdafx.h"
#include "PowerUpItemPool.h"
#include "DXTexture.h"

#include "ItemMover.h"
using namespace MyDirectX;

void PowerUpItemPool::CreatePrePowerUpItem(int preNum)
{
	for(int i = 0;i < preNum;i++)
	{
		CreatePowerUpItem();
	}
}

DXGameObject * PowerUpItemPool::GetPowerUpItem(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 scale)
{
	DXGameObject* pGame = nullptr;
	if (mPowerUpItemList.size() <= 0)
	{
		pGame = CreatePowerUpItem();
	}
	else
	{
		pGame = mPowerUpItemList.back();
		mPowerUpItemList.pop_back();
	}
	auto gameTransform = pGame->GetTransform();
	gameTransform->Position = pos;
	gameTransform->Scale = scale;
	pGame->InitializeComponent();
	pGame->SetEnable(true);
	return pGame;
}

void PowerUpItemPool::ReturnPowerUpItem(DXGameObject * powerUpItem)
{
	mPowerUpItemList.push_back(powerUpItem);
}

DXGameObject * PowerUpItemPool::CreatePowerUpItem()
{
	auto powerUpItem = mScene->Instantiate();
	powerUpItem->SetTag(StaticInstantiateItem);
	auto bombTex = powerUpItem->AddComponent<DXTexture>();
	bombTex->SetTexture(L"Texture/power1.png");
	auto powerCom = powerUpItem->AddComponent<PowerUpItem>();
	powerCom->SetPool(this);
	auto powerUpItemCol = powerUpItem->AddComponent<SquareCollider2D>();
	//コライダーは3分の1に
	powerUpItemCol->SetOneSide(powerUpItemCol->GetOneSide() / 3.0f);
	powerUpItem->AddComponent<ItemMover>();
	mPowerUpItemList.push_back(powerUpItem);
	return powerUpItem;
}
