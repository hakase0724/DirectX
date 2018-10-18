#include "stdafx.h"
#include "CubeMesh.h"

using namespace MyDirectX;
using namespace DirectX;

CubeMesh::CubeMesh()
{
	//��ӂ̒���
	float oneSide = 1.0f;
	//�����̔����𒸓_���W�ɂ���Έ�ӂ̒����������l�p�`���ł���
	float oneSideHarf = oneSide / 2.0f;
	//�L���[�u�̒��_���
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
	//�L���[�u�̒��_�C���f�b�N�X���
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