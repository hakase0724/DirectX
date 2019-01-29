#include "stdafx.h"
#include "ScoreItemPool.h"
#include "ItemMover.h"
#include "PlayScene.h"

using namespace MyDirectX;

void ScoreItemPool::CreatePreScoreItem(int preNum)
{
	for(int i = 0;i < preNum;i++)
	{
		CreateScoreItem();
	}
}

DXGameObject * ScoreItemPool::GetScoreItem(DirectX::XMFLOAT3 pos)
{
	DXGameObject* pGame = nullptr;
	if(mScoreItemList.size() <= 0)
	{
		pGame = CreateScoreItem();
	}
	else
	{
		pGame = mScoreItemList.back();
		mScoreItemList.pop_back();
	}
	pGame->GetTransform()->Position = pos;
	pGame->InitializeComponent();
	pGame->SetEnable(true);
	return pGame;
}

void ScoreItemPool::ReturnScoreItem(DXGameObject * scoreItem)
{
	mScoreItemList.push_back(scoreItem);
}

DXGameObject * ScoreItemPool::CreateScoreItem()
{
	auto scoreItem = mScene->Instantiate();
	scoreItem->SetTag(StaticInstantiateItem);
	auto scoreItemTransform = scoreItem->GetTransform();
	scoreItemTransform->Scale = DirectX::XMFLOAT3(0.25f, 0.25f, 0.25f);
	auto scoreItemTex = scoreItem->AddComponent<DXTexture>();
	scoreItemTex->SetTexture(L"Texture/ScoreItem.png");
	auto scoreItemCom = scoreItem->AddComponent<ScoreItem>();
	scoreItemCom->SetScoreScene(dynamic_cast<PlayScene*>(mScene));
	scoreItemCom->SetScoreItemPool(this);
	auto scoreItemCol = scoreItem->AddComponent<SquareCollider2D>();
	//コライダーは3分の1に
	scoreItemCol->SetOneSide(scoreItemCol->GetOneSide() / 3.0f);
	scoreItem->AddComponent<ItemMover>();
	mScoreItemList.push_back(scoreItem);
	return scoreItem;
}
