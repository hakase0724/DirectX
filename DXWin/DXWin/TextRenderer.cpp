#include "stdafx.h"
#include "TextRenderer.h"

using namespace DirectX;
using namespace MyDirectX;

void TextRenderer::Initialize(DXGameObject * gameObject)
{
	mDXManager = gameObject->GetDXManager();
	mDXCamera = gameObject->GetDXCamera();
	mDeviceContext = mDXManager->GetDeviceContext();
	mGameObject = gameObject;
	mDXFactory = mDXManager->GetDXFactory();
	mDevice = mDXManager->GetDevice();
	mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	mDefaultColor.r = 1;
	mDefaultColor.g = 1;
	mDefaultColor.b = 1;
	mDefaultColor.a = 1;
	mColor = mDefaultColor;

	// シェーダ用にサンプラを作成する
	D3D11_SAMPLER_DESC samDesc;
	ZeroMemory(&samDesc, sizeof(samDesc));
	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samDesc.AddressU = samDesc.AddressV = samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.MaxAnisotropy = 1;
	samDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samDesc.MaxLOD = D3D11_FLOAT32_MAX;

	mGameObject->GetDXManager()->GetDevice()->CreateSamplerState(&samDesc, &mSampler);
	CreateMesh<TextureMesh>();
	CreateShader<TextureShader>();
}

void TextRenderer::CreateText(const wchar_t * text,float xOffset, float yOffset, WCHAR * fontName)
{
	//constを外す
	wchar_t* w = const_cast<wchar_t*>(text);
	//オブジェクトプールへアクセス
	auto pool = mDXManager->GetDXRenderDataPool();
	//フォントテクスチャを取得
	auto data = pool->GetFontTexture(w, fontName);
	mTexture = data->texture;
	mShaderResorceView = data->shaderView;
	//文字を原点からずらす
	mTransform = *mGameObject->GetTransform();
	mTransform.Position.x += xOffset;
	mTransform.Position.y += yOffset;
}

void TextRenderer::Render()
{
	auto cameraParam = mDXCamera->GetCameraParam();
	cTextureBuffer.mWVP = mDXCamera->GetDXCameraParam(&mTransform);
	cTextureBuffer.mColor = XMVectorSet(mColor.r, mColor.g, mColor.b, mColor.a);
	//データを渡す
	mDeviceContext->UpdateSubresource(mConstantBuffer, 0, NULL, &cTextureBuffer, 0, 0);
	//パイプライン構築
	UINT stride = sizeof(TEXTURE_VERTEX_DATA);
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
	//テクスチャ描画に必要なリソースの設定
	mDeviceContext->PSSetShaderResources(0, 1, &mShaderResorceView);
	mDeviceContext->PSSetSamplers(0, 1, &mSampler);
	//ラスタライズステートを設定
	mDeviceContext->RSSetState(mRasterizerState);
	//深度バッファ状態を設定
	auto depth = mDXManager->GetDepthStencilState();
	mDeviceContext->OMSetDepthStencilState(depth, 0);
	//描画
	mDeviceContext->DrawIndexed(mDrawNum, 0, 0);
}

void TextRenderer::Exit()
{
	if (mVertexBuffer)mVertexBuffer->Release();
	if (mVertexLayout)mVertexLayout->Release();
	if (mVertexShader)mVertexShader->Release();
	if (mPixelShader)mPixelShader->Release();
	if (mIndexBuffer)mIndexBuffer->Release();
	if (mConstantBuffer)mConstantBuffer->Release();
	if (mRasterizerState)mRasterizerState->Release();
	if (mSampler)mSampler->Release();
}
