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
	if (mDXInput->GetInputState(DIK_A)) transform->Position.x -= 0.01f;
	if (mDXInput->GetInputState(DIK_D)) transform->Position.x += 0.01f;
	if (mDXInput->GetInputState(DIK_W)) transform->Position.y += 0.01f;
	if (mDXInput->GetInputState(DIK_S)) transform->Position.y -= 0.01f;
}
