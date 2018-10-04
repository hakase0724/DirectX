#include "stdafx.h"
#include "DXCamera.h"

using namespace DirectX;
using namespace MyDirectX;
DXCamera::DXCamera(CameraParam *param)
{
	mParam = *param;
}

DXCamera::~DXCamera(){}

XMMATRIX DXCamera::GetDXCameraParam(TRANSFORM transform)
{
	//�J�����̈ʒu�A������A����яœ_���g�p���āA������W�n�̃r���[�s����쐬
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, mParam.mRatio, 0.1f, 110.0f);
	//����Ɋ�Â��āA������W�n�̃p�[�X�y�N�e�B�u�ˉe�s����쐬
	XMMATRIX view = XMMatrixLookAtLH(mParam.mPos, mParam.mLookup, mParam.mUp);
	//x�����S��]
	XMMATRIX worldX = XMMatrixRotationX(transform.Rotation.y);
	//y�����S��]
	XMMATRIX worldY = XMMatrixRotationY(transform.Rotation.x);
	//z�����S��]
	XMMATRIX worldZ = XMMatrixRotationZ(transform.Rotation.z);
	//�ړ��v�Z
	XMMATRIX move = XMMatrixTranslation(transform.Position.x,transform.Position.y,transform.Position.z);
	//�X�P�[���v�Z
	XMMATRIX scale = XMMatrixScalingFromVector(XMVectorSet(transform.Scale.x, transform.Scale.y, transform.Scale.z, 0.0f));
	//�]�u�s����v�Z �v�̓J�����̏ꏊ�⎋�E���v�Z������Ă��Ƃ��Ǝv��
	return XMMatrixTranspose(scale * worldX * worldY * worldZ * move * view * proj);
}

DirectX::XMMATRIX MyDirectX::DXCamera::GetWorld(TRANSFORM transform)
{
	//x�����S��]
	XMMATRIX worldX = XMMatrixRotationX(transform.Rotation.y);
	//y�����S��]
	XMMATRIX worldY = XMMatrixRotationY(transform.Rotation.x);
	//z�����S��]
	XMMATRIX worldZ = XMMatrixRotationZ(transform.Rotation.z);
	//�ړ��v�Z
	XMMATRIX move = XMMatrixTranslation(transform.Position.x, transform.Position.y, transform.Position.z);
	//�X�P�[���v�Z
	XMMATRIX scale = XMMatrixScalingFromVector(XMVectorSet(transform.Scale.x, transform.Scale.y, transform.Scale.z, 0.0f));
	return XMMatrixTranspose(scale * worldX * worldY * worldZ * move);
}

void DXCamera::SetEyeParamWithRatio(DirectX::XMVECTOR pos, DirectX::XMVECTOR lookup, DirectX::XMVECTOR up, float ratio)
{
	mParam.mPos = pos;
	mParam.mLookup = lookup;
	mParam.mUp = up;
	mParam.mRatio = ratio;
}

void DXCamera::SetRotation(float x, float y)
{
	mParam.mXRote = x;
	mParam.mYRote = y;
}

void DXCamera::SetPos(float x, float y, float z)
{
	mParam.mPos += XMVectorSet(x, y, z,0.0f);
}
