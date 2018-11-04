#include "stdafx.h"
#include "Player.h"
#include "DXGameObjectManager.h"

using namespace MyDirectX;



void Player::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mDXInput = mGameObject->GetDXInput();
	auto transform = mGameObject->GetTransform();
	/*transform.Scale.x /= 10.0f;
	transform.Scale.y /= 10.0f;
	transform.Scale.z /= 10.0f;*/
	/*transform.Position.x = -21.0f;
	transform.Position.y = 10.0f;*/
	mGameObject->SetTransform(&transform);
	mId = mGameObject->GetID();
	waitCount = coolCount;
}

void Player::Update()
{
	waitCount++;
	
	if(!isCoolTime())
	{
		
	}
	else if (mDXInput->GetInputState(DIK_Z))
	{
		for(int i = 0;i < 4;i++)
		{
			auto game = mManager->InstantiateTemp();
			auto transform = mGameObject->GetTransform();
			transform.Position.x += transform.Scale.x * (float)(i * 2 - 3);
			transform.Position.y += transform.Scale.y;
			game->SetTransform(&transform);
			game->SetName("Bullet");
			game->SetTag(Tag::PlayerTag);
			auto col = game->AddComponent<SquareCollider2D>();
			col->SetOneSide(col->GetOneSide() / 10.0f);
			game->AddComponent<Bullet>();
		}		
	}	
	if(mDXInput->GetKeyDown(DIK_LEFTARROW))
	{
		auto transform = mGameObject->GetTransform();
		transform.Position.x -= 1.0f;
		mGameObject->SetTransform(&transform);
	}
}

void Player::SetManager(DXGameObjectManager * manager)
{
	mManager = manager;
}

bool Player::isCoolTime()
{
	if(waitCount % coolCount == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
