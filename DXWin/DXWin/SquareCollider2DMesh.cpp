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
	//�L���[�u�̒��_�C���f�b�N�X���
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
	//��ӂ̒���
	float oneSide = 1.0f;
	//�����̔����𒸓_���W�ɂ���Έ�ӂ̒����������l�p�`���ł���
	float oneSideHarf = oneSide / 2.0f;
	//�L���[�u�̒��_���
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
	//�L���[�u�̒��_�C���f�b�N�X���
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
