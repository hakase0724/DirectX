#include "stdafx.h"
#include "Bomb.h"
#include "DXGameObject.h"
#include "Collider2D.h"
#include "Player.h"

using namespace MyDirectX;

void Bomb::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = mGameObject->GetID();
	mGameObject->SetTag(Item);
	mTag = Item;
}

void Bomb::OnCollisionEnter2D(Collider2D * col)
{
	auto game = col->GetGameObject();
	auto player = game->GetComponent<Player>();
	if (player == nullptr) return;
	player->AddBomb();
	mGameObject->SetEnable(false);
}
