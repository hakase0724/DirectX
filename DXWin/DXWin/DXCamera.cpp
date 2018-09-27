#include "stdafx.h"
#include "DXCamera.h"

using namespace DirectX;
MyDirectX::DXCamera::DXCamera(){}

MyDirectX::DXCamera::~DXCamera(){}

XMMATRIX MyDirectX::DXCamera::GetDXCameraParam(float xRote, float yRote)
{
	//�J�����̈ʒu�A������A����яœ_���g�p���āA������W�n�̃r���[�s����쐬
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, mParam.mRatio, 0.1f, 110.0f);
	//����Ɋ�Â��āA������W�n�̃p�[�X�y�N�e�B�u�ˉe�s����쐬
	XMMATRIX view = XMMatrixLookAtLH(mParam.mPos, mParam.mLookup, mParam.mUp);
	//x����]
	XMMATRIX worldX = XMMatrixRotationX(xRote);
	//y����]
	XMMATRIX worldY = XMMatrixRotationY(yRote);
	//�]�u�s����v�Z �v�̓J�����̏ꏊ�⎋�E���v�Z������Ă��Ƃ��Ǝv��
	return XMMatrixTranspose(worldX * worldY * view * proj);
}

void MyDirectX::DXCamera::SetEyeParamWithRatio(DirectX::XMVECTOR pos, DirectX::XMVECTOR lookup, DirectX::XMVECTOR up, float ratio)
{
	mParam.mPos = pos;
	mParam.mLookup = lookup;
	mParam.mUp = up;
	mParam.mRatio = ratio;
}
