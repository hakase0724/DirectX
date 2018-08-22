#include "stdafx.h"
#include "DXManager.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

//初期化済みか
bool mIsInit = false;
HWND mHwnd = NULL;
D3D_DRIVER_TYPE mDriverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL mLevel = D3D_FEATURE_LEVEL_11_0;
ID3D11Device* mDevice = NULL;
ID3D11DeviceContext* mDeviceContext = NULL;
IDXGISwapChain* mSwapChain = NULL;
ID3D11RenderTargetView* mRenderTargetView = NULL;

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
	D3D11_VIEWPORT view;
	view.Width = (FLOAT)width;
	view.Height = (FLOAT)height;
	view.MinDepth = 0.0f;
	view.MaxDepth = 1.0f;
	view.TopLeftX = 0.0f;
	view.TopLeftY = 0.0f;
	mDeviceContext->RSSetViewports(1, &view);
	mIsInit = true;
	return S_OK;
}

void RenderDX11()
{
	float color[4] = { 0.0f,0.0f,0.0f,0.0f };
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, color);
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
