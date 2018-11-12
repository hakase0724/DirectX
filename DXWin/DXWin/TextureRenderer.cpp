#include "stdafx.h"
#include "TextureRenderer.h"
#include "WICTextureLoader.h"
#include "WICTextureLoader.cpp"

using namespace MyDirectX;

void TextureRenderer::Initialize(DXGameObject * gameObject)
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
}

void TextureRenderer::LoadTexture()
{
	//テクスチャの読み込み
	CoInitialize(NULL);
	HRESULT hr = CreateWICTextureFromFile(mDevice, _T("Texture/profile.png"), &mTexture, &mShaderResourceView);
	//サンプラーデスク作成
	D3D11_SAMPLER_DESC smpDesc;
	::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.MipLODBias = 0.0f;
	smpDesc.MaxAnisotropy = 1;
	smpDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	smpDesc.BorderColor[0] = 0;
	smpDesc.BorderColor[1] = 0;
	smpDesc.BorderColor[2] = 0;
	smpDesc.BorderColor[3] = 0;
	smpDesc.MinLOD = 0;
	smpDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = mDevice->CreateSamplerState(&smpDesc, &mSampler);
	CoUninitialize();
}

void TextureRenderer::LoadTexture(const wchar_t * fileName)
{
	//テクスチャの読み込み
	CoInitialize(NULL);
	HRESULT hr = CreateWICTextureFromFile(mDevice, fileName, &mTexture, &mShaderResourceView);
	//サンプラーデスク作成
	D3D11_SAMPLER_DESC smpDesc;
	::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.MipLODBias = 0.0f;
	smpDesc.MaxAnisotropy = 1;
	smpDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	smpDesc.BorderColor[0] = 0;
	smpDesc.BorderColor[1] = 0;
	smpDesc.BorderColor[2] = 0;
	smpDesc.BorderColor[3] = 0;
	smpDesc.MinLOD = 0;
	smpDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = mDevice->CreateSamplerState(&smpDesc, &mSampler);
	CoUninitialize();
}

void TextureRenderer::Render()
{
	auto transform = mGameObject->GetTransform();
	auto cameraParam = mDXCamera->GetCameraParam();
	cTextureBuffer.mWVP = mDXCamera->GetDXCameraParam(transform);
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
	mDeviceContext->PSSetShaderResources(0, 1, &mShaderResourceView);
	mDeviceContext->PSSetSamplers(0, 1, &mSampler);
	//ラスタライズステートを設定
	mDeviceContext->RSSetState(mRasterizerState);
	//深度バッファ状態を設定
	auto depth = mDXManager->GetDepthStencilState();
	mDeviceContext->OMSetDepthStencilState(depth, 0);
	//描画
	mDeviceContext->DrawIndexed(mDrawNum, 0, 0);
}

void TextureRenderer::Exit()
{
	if (mVertexBuffer)mVertexBuffer->Release();
	if (mVertexLayout)mVertexLayout->Release();
	if (mVertexShader)mVertexShader->Release();
	if (mPixelShader)mPixelShader->Release();
	if (mIndexBuffer)mIndexBuffer->Release();
	if (mConstantBuffer)mConstantBuffer->Release();
	if (mRasterizerState)mRasterizerState->Release();
	if (mTexture)mTexture->Release();
	if (mShaderResourceView)mShaderResourceView->Release();
	if (mSampler)mSampler->Release();
}
