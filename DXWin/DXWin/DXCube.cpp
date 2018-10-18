#include "stdafx.h"
#include "DXCube.h"

using namespace MyDirectX;

void DXCube::Initialize(DXGameObject * gameObject)
{
	auto renderer = gameObject->GetComponent<MeshRenderer>();
	if (renderer == nullptr)
	{
		renderer = gameObject->AddComponent<MeshRenderer>();
	}
	renderer->CreateMesh<CubeMesh>();
	renderer->CreateShader<LightingShader>();
}