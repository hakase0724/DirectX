#include "stdafx.h"
#include "DXSquare.h"

using namespace MyDirectX;

void DXSquare::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = mGameObject->GetID();
	mTag = mGameObject->GetTag();
	auto renderer = gameObject->GetComponent<MeshRenderer>();
	if (renderer == nullptr)
	{
		renderer = gameObject->AddComponent<MeshRenderer>();
	}
	renderer->CreateMesh<SquareMesh>();
	renderer->CreateShader<NonLightingShader>();
}
