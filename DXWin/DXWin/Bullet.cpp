#include "stdafx.h"
#include "Bullet.h"

using namespace MyDirectX;

void Bullet::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mDXInput = mGameObject->GetDXInput();
	mId = mGameObject->GetID();
}

void Bullet::Update()
{
	auto transform = mGameObject->GetTransform();
	transform.Position.y += 0.01f;
	mGameObject->SetTransform(&transform);
	if(mDXInput->GetKeyDown(DIK_RETURN))
	{
		mGameObject->SetEnable(false);
	}
}

void Bullet::OnCollisionEnter(CollisionInfo * info)
{
	mGameObject->SetEnable(false);
}
