#include "stdafx.h"
#include "DXCube.h"
#include <DirectXMath.h>

using namespace DirectX;
using namespace MyDirectX;

DXCube::DXCube(DXManager * dxManager)
{
	mTransform.Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform.Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform.Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);
	mDXManager = dxManager;
}

DXCube::DXCube(TRANSFORM * transform, DXManager * dxManager)
{
	mTransform = *transform;
	mDXManager = dxManager;
}

DXCube::~DXCube()
{
	Exit();
}

void DXCube::SetTransform(TRANSFORM * transform)
{
	mTransform = *transform;
}

//初期化
bool DXCube::Init()
{
	//入力とカメラを取得
	mDXInput = mDXManager->GetDXInput();
	mDXCamera = mDXManager->GetDXCamera();
	//シェーダとメッシュの情報保持クラスを生成
	mMesh = std::make_unique<CubeMesh>();
	mShader = std::make_unique<NormalShader>();
	//シェーダとメッシュの生成
	mFactory = std::make_unique<DXFactory>();
	mFactory->CreateMesh(mMesh.get(), mDXManager->GetDevice(), &mVertexBuffer, &mIndexBuffer);
	mFactory->CreateShader(mShader.get(), mDXManager->GetDevice(), &mVertexShader, &mPixelShader, &mVertexLayout, &mRasterizerState,&mConstantBuffer);
	//描画する頂点数
	mDrawNum = mMesh.get()->indexNum;
	return true;
}
//毎フレーム行う処理
void DXCube::Update()
{
	if (mDXInput->GetInputState(DIK_A)) mTransform.Position.x -= 0.01f;
	if (mDXInput->GetInputState(DIK_D)) mTransform.Position.x += 0.01f;
	if (mDXInput->GetInputState(DIK_W)) mTransform.Position.y += 0.01f;
	if (mDXInput->GetInputState(DIK_S)) mTransform.Position.y -= 0.01f;
	XMStoreFloat4x4(&cBuffer.gWVP, mDXCamera->GetDXCameraParam(mTransform));
}
//描画処理
void DXCube::Render()
{
	//データを渡す
	mDXManager->GetDeviceContext()->UpdateSubresource(mConstantBuffer, 0, NULL, &cBuffer, 0, 0);
	//パイプライン構築
	UINT stride = sizeof(VERTEX_DATA);
	UINT offset = 0;
	//頂点バッファを設定
	mDXManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	//インデックスバッファーの設定
	mDXManager->GetDeviceContext()->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
	//入力レイアウト設定
	mDXManager->GetDeviceContext()->IASetInputLayout(mVertexLayout);
	//頂点情報の解釈の仕方を設定
	mDXManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//頂点シェーダーを設定
	mDXManager->GetDeviceContext()->VSSetShader(mVertexShader, NULL, 0);
	//ピクセルシェーダーを設定
	mDXManager->GetDeviceContext()->PSSetShader(mPixelShader, NULL, 0);
	//定数バッファを設定
	mDXManager->GetDeviceContext()->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	//ラスタライズステートを設定
	mDXManager->GetDeviceContext()->RSSetState(mRasterizerState);
	//深度バッファ状態を設定
	auto depth = mDXManager->GetDepthStencilState();
	mDXManager->GetDeviceContext()->OMSetDepthStencilState(depth, 0);
	//描画
	mDXManager->GetDeviceContext()->DrawIndexed(mDrawNum, 0, 0);
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