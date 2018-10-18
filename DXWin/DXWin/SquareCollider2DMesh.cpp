#include "stdafx.h"
#include "SquareCollider2DMesh.h"

using namespace MyDirectX;

void SquareCollider2DMesh::SetColliderParam(Point2D * leftTop, Point2D * rightTop, Point2D * leftBottom, Point2D * rightBottom)
{
	VERTEX_DATA vertex[] =
	{
		{ DirectX::XMFLOAT3(leftBottom->x, leftBottom->y, 0.0f),  DirectX::XMFLOAT3(leftBottom->x, leftBottom->y, 0.0f)},
		{ DirectX::XMFLOAT3(rightBottom->x, rightBottom->y, 0.0f),   DirectX::XMFLOAT3(rightBottom->x, rightBottom->y, 0.0f)},
		{ DirectX::XMFLOAT3(leftTop->x, leftTop->y, 0.0f),   DirectX::XMFLOAT3(leftTop->x, leftTop->y, 0.0f)},
		{ DirectX::XMFLOAT3(rightTop->x, rightTop->y, 0.0f),    DirectX::XMFLOAT3(rightTop->x, rightTop->y, 0.0f)},
	};

	vertexNum = ARRAYSIZE(vertex);
	vertics = new VERTEX_DATA[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		vertics[i] = vertex[i];
	}
	//キューブの頂点インデックス情報
	int index[] =
	{
		0, 2, 3,
		0, 3, 1,
	};
	indexNum = ARRAYSIZE(index);
	indexes = new int[indexNum];
	for (int i = 0; i < indexNum; i++)
	{
		indexes[i] = index[i];
	}
}

void SquareCollider2DMesh::SetColliderParam()
{
	//一辺の長さ
	float oneSide = 1.0f;
	//長さの半分を頂点座標にすれば一辺の長さが同じ四角形ができる
	float oneSideHarf = oneSide / 2.0f;
	//キューブの頂点情報
	VERTEX_DATA vertex[] =
	{
		{ DirectX::XMFLOAT3(-oneSideHarf, -oneSideHarf, oneSideHarf),  DirectX::XMFLOAT3(-oneSideHarf, -oneSideHarf, oneSideHarf)},
		{ DirectX::XMFLOAT3(oneSideHarf, -oneSideHarf, oneSideHarf),   DirectX::XMFLOAT3(oneSideHarf, -oneSideHarf, oneSideHarf)},
		{ DirectX::XMFLOAT3(-oneSideHarf, oneSideHarf, oneSideHarf),   DirectX::XMFLOAT3(-oneSideHarf, oneSideHarf, oneSideHarf)},
		{ DirectX::XMFLOAT3(oneSideHarf, oneSideHarf, oneSideHarf),    DirectX::XMFLOAT3(oneSideHarf, oneSideHarf, oneSideHarf)},
	};
	vertexNum = ARRAYSIZE(vertex);
	vertics = new VERTEX_DATA[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		vertics[i] = vertex[i];
	}
	//キューブの頂点インデックス情報
	int index[] =
	{
		0, 2, 3,
		0, 3, 1,
	};
	indexNum = ARRAYSIZE(index);
	indexes = new int[indexNum];
	for (int i = 0; i < indexNum; i++)
	{
		indexes[i] = index[i];
	}
}

SquareCollider2DMesh::~SquareCollider2DMesh()
{
}
