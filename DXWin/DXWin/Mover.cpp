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
	mTransform = mGameObject->GetTransform();
	if (mDXInput->GetInputState(DIK_A)) mTransform.Position.x -= 0.01f;
	if (mDXInput->GetInputState(DIK_D)) mTransform.Position.x += 0.01f;
	if (mDXInput->GetInputState(DIK_W)) mTransform.Position.y += 0.01f;
	if (mDXInput->GetInputState(DIK_S)) mTransform.Position.y -= 0.01f;
	if (mDXInput->GetInputState(DIK_UP)) mTransform.Position.z += 0.01f;
	if (mDXInput->GetInputState(DIK_DOWN)) mTransform.Position.z -= 0.01f;
	if (mDXInput->GetInputState(DIK_LEFT)) mTransform.Rotation.x += 0.01f;
	if (mDXInput->GetInputState(DIK_RIGHT)) mTransform.Rotation.x -= 0.01f;
	mGameObject->SetTransform(&mTransform);
}
