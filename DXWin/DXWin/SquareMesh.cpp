#include "stdafx.h"
#include "SquareMesh.h"

using namespace MyDirectX;
using namespace DirectX;

SquareMesh::SquareMesh()
{
	//一辺の長さ
	float oneSide = cMyOneSide;
	//長さの半分を頂点座標にすれば一辺の長さが同じ四角形ができる
	float oneSideHarf = oneSide / 2.0f;
	//キューブの頂点情報
	VERTEX_DATA SquareVertex[] =
	{
		{ XMFLOAT3(-oneSideHarf, -oneSideHarf, 0.0f),  XMFLOAT3(-oneSideHarf, -oneSideHarf, 0.0f)},
		{ XMFLOAT3(oneSideHarf, -oneSideHarf, 0.0f),   XMFLOAT3(oneSideHarf, -oneSideHarf, 0.0f)},
		{ XMFLOAT3(-oneSideHarf, oneSideHarf, 0.0f),   XMFLOAT3(-oneSideHarf, oneSideHarf, 0.0f)},
		{ XMFLOAT3(oneSideHarf, oneSideHarf, 0.0f),    XMFLOAT3(oneSideHarf, oneSideHarf, 0.0f)},
	};
	vertexNum = ARRAYSIZE(SquareVertex);
	vertics = new VERTEX_DATA[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		vertics[i] = SquareVertex[i];
	}
	//キューブの頂点インデックス情報
	int SquareIndex[] =
	{
		0, 2, 3,
		0, 3, 1,
	};
	indexNum = ARRAYSIZE(SquareIndex);
	indexes = new int[indexNum];
	for (int i = 0; i < indexNum; i++)
	{
		indexes[i] = SquareIndex[i];
	}
}


SquareMesh::~SquareMesh()
{
	delete vertics;
	delete indexes;
}
