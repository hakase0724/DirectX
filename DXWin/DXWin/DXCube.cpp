#include "stdafx.h"
#include "DXCube.h"

using namespace DirectX;
using namespace MyDirectX;

DXCube::~DXCube()
{
	Exit();
}

void DXCube::Initialize(DXGameObject * gameObject)
{
	mDXManager = gameObject->GetDXManager();
	mDXInput = gameObject->GetDXInput();
	mDXCamera = gameObject->GetDXCamera();
	mTransform = gameObject->GetTransform();
	mDeviceContext = mDXManager->GetDeviceContext();
	mGameObject = gameObject;
	Init();
}

//初期化
bool DXCube::Init()
{
	//シェーダとメッシュ生成に必要なパラメータ
	mMesh = std::make_unique<CubeMesh>();
	mShader = std::make_unique<LightingShader>();
	//一文を短くして可読性を上げる
	auto factory = mDXManager->GetDXFactory();
	auto device = mDXManager->GetDevice();
	//シェーダとメッシュ生成
	factory->CreateMesh(mMesh.get(), device, &mVertexBuffer, &mIndexBuffer);
	factory->CreateShader(mShader.get(),device,&mVertexShader,&mPixelShader,&mVertexLayout,&mRasterizerState,&mConstantBuffer);
	//描画する頂点数
	mDrawNum = mMesh.get()->indexNum;
	return true;
}

//描画処理
void DXCube::Render()
{
	mTransform = mGameObject->GetTransform();
	auto cameraParam = mDXCamera->GetCameraParam();
	cBuffer.mW = mDXCamera->GetWorld(mTransform);
	cBuffer.mWVP = mDXCamera->GetDXCameraParam(mTransform);
	cBuffer.vColor = XMVectorSet(0, 1, 0, 1);
	cBuffer.vLightPos = XMVectorSet(-1.0f, 1.0f, -2.0f, 1.0f);
	cBuffer.vEyePos = cameraParam.mPos;
	//データを渡す
	mDeviceContext->UpdateSubresource(mConstantBuffer, 0, NULL, &cBuffer, 0, 0);
	//パイプライン構築
	UINT stride = sizeof(VERTEX_DATA);
	UINT offset = 0;
	//頂点バッファを設定
	mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	//インデックスバッファーの設定
	mDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
	//入力レイアウト設定
	mDeviceContext->IASetInputLayout(mVertexLayout);
	//頂点情報の解釈の仕方を設定
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//頂点シェーダーを設定
	mDeviceContext->VSSetShader(mVertexShader, NULL, 0);
	//ピクセルシェーダーを設定
	mDeviceContext->PSSetShader(mPixelShader, NULL, 0);
	//定数バッファを設定
	mDeviceContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	mDeviceContext->PSSetConstantBuffers(0, 1, &mConstantBuffer);
	//ラスタライズステートを設定
	mDeviceContext->RSSetState(mRasterizerState);
	//深度バッファ状態を設定
	auto depth = mDXManager->GetDepthStencilState();
	mDeviceContext->OMSetDepthStencilState(depth, 0);
	//描画
	mDeviceContext->DrawIndexed(mDrawNum, 0, 0);
}
//解放処理
void DXCube::Exit()
{
	if (mVertexBuffer)mVertexBuffer->Release();
	if (mVertexLayout)mVertexLayout->Release();
	if (mVertexShader)mVertexShader->Release();
	if (mPixelShader)mPixelShader->Release();
	if (mIndexBuffer)mIndexBuffer->Release();
	if (mConstantBuffer)mConstantBuffer->Release();
	if (mRasterizerState)mRasterizerState->Release();
}