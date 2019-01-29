#include "stdafx.h"
#include "ScoreItem.h"
#include "DXGameObject.h"
#include "Collider2D.h"
#include "Player.h"
#include "ScoreItemPool.h"
#include "PlayScene.h"

using namespace MyDirectX;

void ScoreItem::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = mGameObject->GetID();
}

void ScoreItem::Initialize()
{
	mTag = mGameObject->GetTag();
}

void ScoreItem::OnCollisionEnter2D(Collider2D * col)
{
	auto game = col->GetGameObject();
	auto player = game->GetComponent<Player>();
	if (player == nullptr) return;
	mPlayScene->AddScore(mAddScore);
	mGameObject->SetEnable(false);
}

void ScoreItem::OnDisable()
{
	if(mPool != nullptr) mPool->ReturnScoreItem(mGameObject);
}
