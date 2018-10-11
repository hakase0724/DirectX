#include "stdafx.h"
#include "CubeMesh.h"

using namespace MyDirectX;
using namespace DirectX;

CubeMesh::CubeMesh()
{
	//キューブの頂点情報
	VERTEX_DATA CubeVertex[] =
	{
		{ DirectX::XMFLOAT3(-0.3f, -0.3f, 0.3f),  DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT3(-0.3f, -0.3f, 0.3f)},
		{ DirectX::XMFLOAT3(0.3f, -0.3f, 0.3f),   DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), DirectX::XMFLOAT3(0.3f, -0.3f, 0.3f)},
		{ DirectX::XMFLOAT3(0.3f, -0.3f, -0.3f),  DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT3(0.3f, -0.3f, -0.3f)},
		{ DirectX::XMFLOAT3(-0.3f, -0.3f, -0.3f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT3(-0.3f, -0.3f, -0.3f)},
		{ DirectX::XMFLOAT3(-0.3f, 0.3f, 0.3f),   DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(-0.3f, 0.3f, 0.3f)},
		{ DirectX::XMFLOAT3(0.3f, 0.3f, 0.3f),    DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.3f, 0.3f, 0.3f)},
		{ DirectX::XMFLOAT3(0.3f, 0.3f, -0.3f),   DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(0.3f, 0.3f, -0.3f)},
		{ DirectX::XMFLOAT3(-0.3f, 0.3f, -0.3f),  DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT3(-0.3f, 0.3f, -0.3f)},
	};
	vertexNum = ARRAYSIZE(CubeVertex);
	vertics = new VERTEX_DATA[vertexNum];
	for(int i = 0;i < vertexNum;i++)
	{
		vertics[i] = CubeVertex[i];
	}
	//キューブの頂点インデックス情報
	int CubeIndex[] =
	{
		0, 2, 1,
		0, 3, 2,

		0, 5, 4,
		0, 1, 5,

		1, 6, 5,
		1, 2, 6,

		2, 7, 6,
		2, 3, 7,

		0, 4, 7,
		0, 7, 3,

		4, 5, 7,
		5, 6, 7,

	};
	indexNum = ARRAYSIZE(CubeIndex);
	indexes = new int[indexNum];
	for (int i = 0; i < indexNum; i++)
	{
		indexes[i] = CubeIndex[i];
	}
}

CubeMesh::~CubeMesh()
{
	delete vertics;
	delete indexes;
}

UINT MyDirectX::CubeMesh::GetSize()
{
	return sizeof(VERTEX_DATA);
}
