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
	auto transform = mGameObject->GetTransform();
	if (mDXInput->GetInputState(DIK_NUMPAD8)) transform->Rotation.y += 0.01f;
	if (mDXInput->GetInputState(DIK_NUMPAD2)) transform->Rotation.y -= 0.01f;
	if (mDXInput->GetInputState(DIK_NUMPAD4)) transform->Rotation.x += 0.01f;
	if (mDXInput->GetInputState(DIK_NUMPAD6)) transform->Rotation.x -= 0.01f;
	mGameObject->SetTransform(transform);
}
