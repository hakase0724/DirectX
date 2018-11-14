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
	if (mDXInput->GetInputState(DIK_LEFTARROW)) transform->Position.x -= mMoveSpeed;
	if (mDXInput->GetInputState(DIK_RIGHTARROW)) transform->Position.x += mMoveSpeed;
	if (mDXInput->GetInputState(DIK_UPARROW)) transform->Position.y += mMoveSpeed;
	if (mDXInput->GetInputState(DIK_DOWNARROW)) transform->Position.y -= mMoveSpeed;
}
