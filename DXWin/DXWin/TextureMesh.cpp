#include "stdafx.h"
#include "TextureMesh.h"

using namespace DirectX;
using namespace MyDirectX;
TextureMesh::TextureMesh()
{
	//一辺の長さ
	float oneSide = cMyOneSide;
	//長さの半分を頂点座標にすれば一辺の長さが同じ四角形ができる
	float oneSideHarf = oneSide / 2.0f;
	//テクスチャの頂点情報
	TEXTURE_VERTEX_DATA TextureVertex[] =
	{
		{ XMFLOAT3(-oneSideHarf, -oneSideHarf, 0.0f),  XMFLOAT2(0.0f, 1.0f)},
		{ XMFLOAT3(oneSideHarf, -oneSideHarf, 0.0f),   XMFLOAT2(1.0f, 1.0f)},
		{ XMFLOAT3(-oneSideHarf, oneSideHarf, 0.0f),   XMFLOAT2(0.0f, 0.0f)},
		{ XMFLOAT3(oneSideHarf, oneSideHarf, 0.0f),    XMFLOAT2(1.0f, 0.0f)},
	};
	vertexNum = ARRAYSIZE(TextureVertex);
	vertexInfo = new TEXTURE_VERTEX_DATA[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		vertexInfo[i] = TextureVertex[i];
	}
	
	//テクスチャの頂点インデックス情報
	int TextureIndex[] =
	{
		0, 2, 3,
		0, 3, 1,
	};
	indexNum = ARRAYSIZE(TextureIndex);
	indexes = new int[indexNum];
	for (int i = 0; i < indexNum; i++)
	{
		indexes[i] = TextureIndex[i];
	}
}


TextureMesh::~TextureMesh()
{
	delete vertics;
	delete vertexInfo;
	delete indexes;
}
