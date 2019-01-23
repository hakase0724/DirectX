#include "stdafx.h"
#include "MeshRenderer.h"

using namespace DirectX;
using namespace MyDirectX;

void MeshRenderer::SetDefaultColor(float r, float g, float b, float a)
{
	mDefaultColor.r = r;
	mDefaultColor.g = g;
	mDefaultColor.b = b;
	mDefaultColor.a = a;
	mColor = mDefaultColor;
}

void MeshRenderer::SetColor(float r, float g, float b, float a)
{
	mColor.r = r;
	mColor.g = g;
	mColor.b = b;
	mColor.a = a;
}

void MeshRenderer::SetColor()
{
	mColor = mDefaultColor;
}

void MeshRenderer::Initialize(DXGameObject * gameObject)
{
	mDXManager = gameObject->GetDXManager();
	mDXCamera = gameObject->GetDXCamera();
	mDeviceContext = mDXManager->GetDeviceContext();
	mGameObject = gameObject;
	mDXFactory = mDXManager->GetDXFactory();
	mDevice = mDXManager->GetDevice();
	mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	mDefaultColor.r = 0;
	mDefaultColor.g = 1;
	mDefaultColor.b = 0;
	mDefaultColor.a = 1;
	mColor = mDefaultColor;
}

void MeshRenderer::Initialize()
{
	mColor = mDefaultColor;
}

void MeshRenderer::Render()
{
	auto transform = mGameObject->GetTransform();
	auto cameraParam = mDXCamera->GetCameraParam();
	cBuffer.mW = mDXCamera->GetWorld(transform);
	cBuffer.mWVP = mDXCamera->GetDXCameraParam(transform);
	cBuffer.vColor = XMVectorSet(mColor.r, mColor.g, mColor.b, mColor.a);
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
	mDeviceContext->IASetPrimitiveTopology(mTopology);
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
	//ブレンドステート設定
	mDXManager->OMSetBlendState(mIsAlphaBlending);
	//描画
	mDeviceContext->DrawIndexed(mDrawNum, 0, 0);
}

void MeshRenderer::Exit()
{
	if (mVertexBuffer)mVertexBuffer->Release();
	if (mVertexLayout)mVertexLayout->Release();
	if (mVertexShader)mVertexShader->Release();
	if (mPixelShader)mPixelShader->Release();
	if (mIndexBuffer)mIndexBuffer->Release();
	if (mConstantBuffer)mConstantBuffer->Release();
	if (mRasterizerState)mRasterizerState->Release();
}

void MeshRenderer::OnCollisionEnter2D(Collider2D* col)
{
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void MeshRenderer::OnCollisionExit2D(Collider2D* col)
{
	SetColor();
}