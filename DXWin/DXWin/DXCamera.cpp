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
	//カメラの位置、上方向、および焦点を使用して、左手座標系のビュー行列を作成
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, mParam.mRatio, 0.1f, 110.0f);
	//視野に基づいて、左手座標系のパースペクティブ射影行列を作成
	XMMATRIX view = XMMatrixLookAtLH(mParam.mPos, mParam.mLookup, mParam.mUp);
	//x軸中心回転
	XMMATRIX worldX = XMMatrixRotationX(transform.Rotation.y);
	//y軸中心回転
	XMMATRIX worldY = XMMatrixRotationY(transform.Rotation.x);
	//z軸中心回転
	XMMATRIX worldZ = XMMatrixRotationZ(transform.Rotation.z);
	//移動計算
	XMMATRIX move = XMMatrixTranslation(transform.Position.x,transform.Position.y,transform.Position.z);
	//スケール計算
	XMMATRIX scale = XMMatrixScalingFromVector(XMVectorSet(transform.Scale.x, transform.Scale.y, transform.Scale.z, 0.0f));
	//転置行列を計算 要はカメラの場所や視界を計算するってことだと思う
	return XMMatrixTranspose(scale * worldX * worldY * worldZ * move * view * proj);
}

DirectX::XMMATRIX MyDirectX::DXCamera::GetWorld(TRANSFORM transform)
{
	//x軸中心回転
	XMMATRIX worldX = XMMatrixRotationX(transform.Rotation.y);
	//y軸中心回転
	XMMATRIX worldY = XMMatrixRotationY(transform.Rotation.x);
	//z軸中心回転
	XMMATRIX worldZ = XMMatrixRotationZ(transform.Rotation.z);
	//移動計算
	XMMATRIX move = XMMatrixTranslation(transform.Position.x, transform.Position.y, transform.Position.z);
	//スケール計算
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
