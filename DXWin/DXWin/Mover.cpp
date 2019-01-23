#include "stdafx.h"
#include "Mover.h"

using namespace MyDirectX;

void Mover::Initialize(DXGameObject * gameObject)
{
	mDXInput = gameObject->GetDXInput();
	mGameObject = gameObject;
}

void Mover::Update()
{
	auto transform = mGameObject->GetTransform();
	if (mDXInput->GetKey(DIK_LEFTARROW)) transform->Position.x -= mMoveSpeed;
	if (mDXInput->GetKey(DIK_RIGHTARROW)) transform->Position.x += mMoveSpeed;
	if (mDXInput->GetKey(DIK_UPARROW)) transform->Position.y += mMoveSpeed;
	if (mDXInput->GetKey(DIK_DOWNARROW)) transform->Position.y -= mMoveSpeed;
}
