#include "stdafx.h"
#include "SquareMesh.h"

using namespace MyDirectX;
using namespace DirectX;

SquareMesh::SquareMesh()
{
	//��ӂ̒���
	float oneSide = cMyOneSide;
	//�����̔����𒸓_���W�ɂ���Έ�ӂ̒����������l�p�`���ł���
	float oneSideHarf = oneSide / 2.0f;
	//�L���[�u�̒��_���
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
	//�L���[�u�̒��_�C���f�b�N�X���
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
