#include "stdafx.h"
#include "DXSphere.h"

using namespace DirectX;
using namespace MyDirectX;

DXSphere::~DXSphere()
{
	Exit();
}


void DXSphere::Initialize(DXGameObject * gameObject)
{
	mDXManager = gameObject->GetDXManager();
	mDXInput = gameObject->GetDXInput();
	mDXCamera = gameObject->GetDXCamera();
	mTransform = gameObject->GetTransform();
	mDeviceContext = mDXManager->GetDeviceContext();
	mGameObject = gameObject;
	Init();
}

bool DXSphere::Init()
{
	//シェーダとメッシュ生成に必要なパラメータ
	mMesh = std::make_unique<SphereMesh>();
	mShader = std::make_unique<LightingShader>();
	//一文を短くして可読性を上げる
	auto factory = mDXManager->GetDXFactory();
	auto device = mDXManager->GetDevice();
	//シェーダとメッシュ生成
	factory->CreateMesh(mMesh.get(), device, &mVertexBuffer, &mIndexBuffer);
	factory->CreateShader(mShader.get(), device, &mVertexShader, &mPixelShader, &mVertexLayout, &mRasterizerState, &mConstantBuffer);
	//描画する頂点数
	mDrawNum = mMesh.get()->indexNum;
	return true;
}

void DXSphere::Render()
{
	mTransform = mGameObject->GetTransform();
	auto cameraParam = mDXCamera->GetCameraParam();
	cBuffer.mW = mDXCamera->GetWorld(mTransform);
	cBuffer.mWVP = mDXCamera->GetDXCameraParam(mTransform);
	cBuffer.vColor = XMVectorSet(0, 1, 0, 1);
	cBuffer.vLightPos = XMVectorSet(-1.0f, 1.0f, -2.0f, 1.0f);
	cBuffer.vEyePos = cameraParam.mPos;

	//データを渡す
	mDXManager->GetDeviceContext()->UpdateSubresource(mConstantBuffer, 0, NULL, &cBuffer, 0, 0);
	//パイプライン構築
	UINT stride = sizeof(VERTEX_DATA);
	UINT offset = 0;
	//頂点バッファを設定
	mDXManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	//インデックスバッファの設定
	mDXManager->GetDeviceContext()->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
	//入力レイアウト設定
	mDXManager->GetDeviceContext()->IASetInputLayout(mVertexLayout);
	//頂点情報の解釈の仕方を設定
	mDXManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//頂点シェーダーを設定
	mDXManager->GetDeviceContext()->VSSetShader(mVertexShader, NULL, 0);
	//ピクセルシェーダーを設定
	mDXManager->GetDeviceContext()->PSSetShader(mPixelShader, NULL, 0);
	//定数バッファを設定
	mDXManager->GetDeviceContext()->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	mDXManager->GetDeviceContext()->PSSetConstantBuffers(0, 1, &mConstantBuffer);
	//ラスタライズステートを設定
	mDXManager->GetDeviceContext()->RSSetState(mRasterizerState);
	//深度バッファ状態を設定
	auto depth = mDXManager->GetDepthStencilState();
	mDXManager->GetDeviceContext()->OMSetDepthStencilState(depth, 0);
	//描画
	mDXManager->GetDeviceContext()->DrawIndexed(mDrawNum, 0,0);
}

void DXSphere::Exit()
{
	if (mVertexBuffer)mVertexBuffer->Release();
	if (mVertexLayout)mVertexLayout->Release();
	if (mVertexShader)mVertexShader->Release();
	if (mPixelShader)mPixelShader->Release();
	if (mIndexBuffer)mIndexBuffer->Release();
	if (mConstantBuffer)mConstantBuffer->Release();
	if (mRasterizerState)mRasterizerState->Release();
}