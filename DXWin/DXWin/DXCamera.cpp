#include "stdafx.h"
#include "DXCamera.h"

using namespace DirectX;
MyDirectX::DXCamera::DXCamera(){}

MyDirectX::DXCamera::~DXCamera(){}

XMMATRIX MyDirectX::DXCamera::GetDXCameraParam(float xRote, float yRote)
{
	//カメラの位置、上方向、および焦点を使用して、左手座標系のビュー行列を作成
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, mParam.mRatio, 0.1f, 110.0f);
	//視野に基づいて、左手座標系のパースペクティブ射影行列を作成
	XMMATRIX view = XMMatrixLookAtLH(mParam.mPos, mParam.mLookup, mParam.mUp);
	//x軸回転
	XMMATRIX worldX = XMMatrixRotationX(xRote);
	//y軸回転
	XMMATRIX worldY = XMMatrixRotationY(yRote);
	//転置行列を計算 要はカメラの場所や視界を計算するってことだと思う
	return XMMatrixTranspose(worldX * worldY * view * proj);
}

void MyDirectX::DXCamera::SetEyeParamWithRatio(DirectX::XMVECTOR pos, DirectX::XMVECTOR lookup, DirectX::XMVECTOR up, float ratio)
{
	mParam.mPos = pos;
	mParam.mLookup = lookup;
	mParam.mUp = up;
	mParam.mRatio = ratio;
}
