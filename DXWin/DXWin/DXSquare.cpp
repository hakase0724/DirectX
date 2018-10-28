#include "stdafx.h"
#include "DXSquare.h"

using namespace MyDirectX;

void DXSquare::Initialize(DXGameObject * gameObject)
{
	auto renderer = gameObject->GetComponent<MeshRenderer>();
	if (renderer == nullptr)
	{
		renderer = gameObject->AddComponent<MeshRenderer>();
	}
	renderer->CreateMesh<SquareMesh>();
	renderer->CreateShader<NonLightingShader>();
}
