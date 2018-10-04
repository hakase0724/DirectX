#pragma once
#include "DXManager.h"
#include <DirectXMath.h>
//�v���~�e�B�u�̒��_�A���_�C���f�b�N�X��ێ�
namespace MyDirectX
{
	//�L���[�u�̒��_���
	VERTEX CubeVertex[] =
	{
		{ DirectX::XMFLOAT3(-0.3f, -0.3f, 0.3f),  DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(0.3f, -0.3f, 0.3f),   DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(0.3f, -0.3f, -0.3f),  DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-0.3f, -0.3f, -0.3f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-0.3f, 0.3f, 0.3f),   DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(0.3f, 0.3f, 0.3f),    DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(0.3f, 0.3f, -0.3f),   DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ DirectX::XMFLOAT3(-0.3f, 0.3f, -0.3f),  DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
	};

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
}
