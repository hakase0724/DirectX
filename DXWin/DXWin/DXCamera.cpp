#include "stdafx.h"
#include "DXCamera.h"

using namespace DirectX;
using namespace MyDirectX;

DXCamera::DXCamera(CameraParam * param)
{
	mParam = *param;
	XMVECTOR one = XMVectorSet(1920 / 2.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR two = XMVectorSet(0.0f, -1080.0f / 2.0f, 0.0f, 0.0f);
	XMVECTOR three = XMVectorSet(1920 / 2.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR four = XMVectorSet(1920 / 2.0f, 1080.0f / 2.0f, 0.0f, 1.0f);
	mWorldToScreenPointMatrix = new XMMATRIX(one,two,three,four);
}

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

XMMATRIX MyDirectX::DXCamera::GetWorld(TRANSFORM transform)
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

XMVECTOR DXCamera::WorldToScreenPoint(TRANSFORM* transform)
{
	auto vector = XMVectorSet(transform->Position.x, transform->Position.y, transform->Position.z, 1.0f);
	auto screen = XMVector3Transform(vector, *mWorldToScreenPointMatrix);
	return screen;
}

//��ʔ䗦�ƃJ�����̃p�����[�^��ݒ肷��
void DXCamera::SetEyeParamWithRatio(XMVECTOR pos, XMVECTOR lookup, XMVECTOR up, float ratio)
{
	mParam.mPos = pos;
	mParam.mLookup = lookup;
	mParam.mUp = up;
	mParam.mRatio = ratio;
}
//�J��������
void DXCamera::SetRotation(float x, float y)
{
	mParam.mXRote = x;
	mParam.mYRote = y;
}
//�J�����̈ʒu�𓮂���
void DXCamera::SetPos(float x, float y, float z)
{
	mParam.mPos += XMVectorSet(x, y, z,0.0f);
}
