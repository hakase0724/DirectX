#include "stdafx.h"
#include "DXSphere.h"

using namespace MyDirectX;

void DXSphere::Initialize(DXGameObject * gameObject)
{
	auto renderer = gameObject->GetComponent<MeshRenderer>();
	if (renderer == nullptr)
	{
		renderer = gameObject->AddComponent<MeshRenderer>();
	}
	renderer->CreateMesh<SphereMesh>();
	renderer->CreateShader<LightingShader>();
	renderer->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}