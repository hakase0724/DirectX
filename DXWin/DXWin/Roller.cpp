#include "stdafx.h"
#include "Roller.h"

using namespace MyDirectX;

void Roller::Initialize(DXGameObject * gameObject)
{
	mDXInput = gameObject->GetDXInput();
	mGameObject = gameObject;
}

void Roller::Update()
{
	mTransform = mGameObject->GetTransform();
	if (mDXInput->GetInputState(DIK_NUMPAD8)) mTransform.Rotation.y += 0.01f;
	if (mDXInput->GetInputState(DIK_NUMPAD2)) mTransform.Rotation.y -= 0.01f;
	if (mDXInput->GetInputState(DIK_NUMPAD4)) mTransform.Rotation.x += 0.01f;
	if (mDXInput->GetInputState(DIK_NUMPAD6)) mTransform.Rotation.x -= 0.01f;
	mGameObject->SetTransform(&mTransform);
}
