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
	mGameObject->SetTransform(&transform);
	mId = mGameObject->GetID();
}

void Player::Update()
{
	if (mDXInput->GetKeyDown(DIK_SPACE))
	{
		auto game = mManager->InstantiateTemp();
		auto transform = new TRANSFORM();
		/*transform->Scale.x /= 10.0f;
		transform->Scale.y /= 10.0f;
		transform->Scale.z /= 10.0f;*/
		game->SetTransform(transform);
		game->SetName("TEST");
		game->AddComponent<SquareCollider2D>();
		game->AddComponent<TestComponent>();
	}
		
}

void Player::SetManager(DXGameObjectManager * manager)
{
	mManager = manager;
}
