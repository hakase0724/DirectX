#include "stdafx.h"
#include "CubeMesh.h"

using namespace MyDirectX;
using namespace DirectX;

CubeMesh::CubeMesh()
{
	//一辺の長さ
	float oneSide = 1.0f;
	//長さの半分を頂点座標にすれば一辺の長さが同じ四角形ができる
	float oneSideHarf = oneSide / 2.0f;
	//キューブの頂点情報
	VERTEX_DATA CubeVertex[] =
	{
		{ DirectX::XMFLOAT3(-oneSideHarf, -oneSideHarf, oneSideHarf),  DirectX::XMFLOAT3(-oneSideHarf, -oneSideHarf, oneSideHarf)},
		{ DirectX::XMFLOAT3(oneSideHarf, -oneSideHarf, oneSideHarf),   DirectX::XMFLOAT3(oneSideHarf, -oneSideHarf, oneSideHarf)},
		{ DirectX::XMFLOAT3(oneSideHarf, -oneSideHarf, -oneSideHarf),  DirectX::XMFLOAT3(oneSideHarf, -oneSideHarf, -oneSideHarf)},
		{ DirectX::XMFLOAT3(-oneSideHarf, -oneSideHarf, -oneSideHarf), DirectX::XMFLOAT3(-oneSideHarf, -oneSideHarf, -oneSideHarf)},
		{ DirectX::XMFLOAT3(-oneSideHarf, oneSideHarf, oneSideHarf),   DirectX::XMFLOAT3(-oneSideHarf, oneSideHarf, oneSideHarf)},
		{ DirectX::XMFLOAT3(oneSideHarf, oneSideHarf, oneSideHarf),    DirectX::XMFLOAT3(oneSideHarf, oneSideHarf, oneSideHarf)},
		{ DirectX::XMFLOAT3(oneSideHarf, oneSideHarf, -oneSideHarf),   DirectX::XMFLOAT3(oneSideHarf, oneSideHarf, -oneSideHarf)},
		{ DirectX::XMFLOAT3(-oneSideHarf, oneSideHarf, -oneSideHarf),  DirectX::XMFLOAT3(-oneSideHarf, oneSideHarf, -oneSideHarf)},
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