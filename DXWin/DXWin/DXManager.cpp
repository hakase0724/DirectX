#include "stdafx.h"
#include "DXManager.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;

struct VERTEX
{
	XMFLOAT3 mV;
};

struct CONSTANT_BUFFER
{
	XMMATRIX mWVP;
};

//初期化済みか
bool mIsInit = false;
HWND mHwnd = NULL;
D3D_DRIVER_TYPE mDriverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL mLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11Device* mDevice = NULL;
ID3D11DeviceContext* mDeviceContext = NULL;
IDXGISwapChain* mSwapChain = NULL;
ID3D11RenderTargetView* mRenderTargetView = NULL;
ID3D11InputLayout* mVertexLayout;
ID3D11VertexShader* mVertexShader;
ID3D11PixelShader* mPixelShader;
ID3D11Buffer* mConstantBuffer;
ID3D11Buffer* mVertexBuffer;

HRESULT InitDX11(HWND hwnd)
{
	//初期化してたら処理しない
	if (mIsInit) return S_FALSE;
	mHwnd = hwnd;
	HRESULT hr = S_OK;
	RECT rc;
	GetClientRect(mHwnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	UINT flags = 0;
#ifdef _DEBUG
	flags = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL fLevel = D3D_FEATURE_LEVEL_11_0;
	mDriverType = D3D_DRIVER_TYPE_HARDWARE;

	//スワップチェイン設定
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd,sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = mHwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	//DirectXのデバイスを作る
	hr = D3D11CreateDeviceAndSwapChain
	(NULL,mDriverType,NULL,flags,&fLevel,1,D3D11_SDK_VERSION,&sd,&mSwapChain,&mDevice,&mLevel,&mDeviceContext);
	if (FAILED(hr)) return hr;

	ID3D11Texture2D* back_buff = NULL;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buff);
	if (FAILED(hr)) return hr;

	hr = mDevice->CreateRenderTargetView(back_buff,NULL,&mRenderTargetView);
	back_buff->Release();
	if (FAILED(hr)) return hr;

	mDeviceContext->OMSetRenderTargets(1,&mRenderTargetView,NULL);

	//ビューポート設定
	D3D11_VIEWPORT view;
	view.Width = (FLOAT)width;
	view.Height = (FLOAT)height;
	view.MinDepth = 0.0f;
	view.MaxDepth = 1.0f;
	view.TopLeftX = 0.0f;
	view.TopLeftY = 0.0f;
	mDeviceContext->RSSetViewports(1, &view);

	//シェーダの設定
	ID3DBlob* compileVS = NULL;
	ID3DBlob* compilePS = NULL;
	
	if (FAILED(D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &compilePS, NULL))) return S_FALSE;
	if (FAILED(D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &compileVS, NULL))) return S_FALSE;
	mDevice->CreateVertexShader(compileVS->GetBufferPointer(), compileVS->GetBufferSize(), NULL, &mVertexShader);
	mDevice->CreatePixelShader(compilePS->GetBufferPointer(), compilePS->GetBufferSize(), NULL, &mPixelShader);
	
	//頂点レイアウト設定
	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		"POSITION",
		0,
		DXGI_FORMAT_R32G32B32_FLOAT,
		0,
		0,
		D3D11_INPUT_PER_VERTEX_DATA,
		0
	};
	mDevice->CreateInputLayout(layout, 1, compileVS->GetBufferPointer(), compileVS->GetBufferSize(), &mVertexLayout);
	compileVS->Release();
	compilePS->Release();

	//定数バッファ生成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	mDevice->CreateBuffer(&cb, NULL, &mConstantBuffer);

	//頂点データとバッファ生成
	VERTEX vertex[] = {
		XMFLOAT3(-0.2f, 0.5f, 0.0f),
		XMFLOAT3(0.2f, 0.5f, 0.0f),
	};
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(VERTEX) * 2;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertex;
	mDevice->CreateBuffer(&bd, &data, &mVertexBuffer);

	//パイプライン構築
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	mDeviceContext->IASetInputLayout(mVertexLayout);
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	mDeviceContext->VSSetShader(mVertexShader, NULL, 0);
	mDeviceContext->PSSetShader(mPixelShader, NULL, 0);
	mDeviceContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	mIsInit = true;
	return S_OK;
}

void RenderDX11()
{
	//塗りつぶし色の設定と画面クリア
	float color[4] = { 0.0f,0.0f,0.0f,1.0f };
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, color);

	//パラメータ計算
	XMVECTOR eye_pos = XMVectorSet(0.0f,0.0f,-2.0f,1.0f);
	XMVECTOR eye_lookup = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR eye_up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	XMMATRIX view = XMMatrixLookAtLH(eye_pos, eye_lookup, eye_up);
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, cWidth / cHeight,0.1f,100.0f);
	XMMATRIX world = XMMatrixRotationZ(0);

	//データを渡す
	D3D11_MAPPED_SUBRESOURCE data;
	CONSTANT_BUFFER buffer;
	buffer.mWVP = XMMatrixTranspose(world * view * proj);
	mDeviceContext->Map(mConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	memcpy_s(data.pData, data.RowPitch, (void*)(&buffer), sizeof(buffer));
	mDeviceContext->Unmap(mConstantBuffer, 0);

	//描画
	mDeviceContext->Draw(2, 0);
	mSwapChain->Present(0, 0);
}

void ExitDX11()
{
	//初期化してなかったら処理しない
	if (!mIsInit) return;
	if (mDeviceContext)
	{
		mDeviceContext->ClearState();
		mDeviceContext->Release();
	}
	if (mRenderTargetView) mRenderTargetView->Release();
	if (mSwapChain) mSwapChain->Release();
	if (mDevice) mDevice->Release();
	mIsInit = false;
}
