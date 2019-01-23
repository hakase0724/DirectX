#include "stdafx.h"
#include "DXManager.h"
#include "dinput.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace MyDirectX;

DXManager::DXManager(HWND hwnd)
{
	InitDX11(hwnd);
}

DXManager::~DXManager()
{
	ExitDX11();
}

//������
HRESULT DXManager::InitDX11(HWND hwnd)
{
	mHwnd = hwnd;
	HRESULT hr = S_OK;
	RECT rc;
	GetClientRect(mHwnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	UINT flags = 0;
	mDXInput = std::make_unique<DXInput>(hwnd);
	//�J�����𐶐�
	auto cParam = new CAMERA_PARAM
	(
		DirectX::XMVectorSet(0.0f, 0.0f, -3.5f, 1.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f),
		cWidth / cHeight
	);
	mDXCamera = std::make_unique<DXCamera>(cParam);
	//�V�F�[�_�[�ƃ��b�V�������N���X
	mDXFactory = std::make_unique<DXFactory>();
	
#ifdef _DEBUG
	flags = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL fLevel = D3D_FEATURE_LEVEL_11_0;
	mDriverType = D3D_DRIVER_TYPE_HARDWARE;
	//VSync��L���ɂ���
	mIsVsyncEnable = TRUE;
	//�X���b�v�`�F�C���ݒ�
	DXGI_SWAP_CHAIN_DESC sd;
	//�n�������̑S�Ă�0�N���A����
	//�N���A�����㒆�g����ꂸ�ɃA�N�Z�X����ƃG���[�ɂȂ邱�Ƃ��������ߗv���ӂ炵��
	ZeroMemory(&sd,sizeof(sd));
	//�o�b�t�@��
	sd.BufferCount = 1;
	//�𑜓x��
	sd.BufferDesc.Width = width;
	//�𑜓x����
	sd.BufferDesc.Height = height;
	//���t���b�V�����[�g�̍ő�L�����@�ύX�\�ȏꍇ�̂݉�ʂ̃��t���b�V�����[�g�����̒l�ɕύX����
	sd.BufferDesc.RefreshRate.Numerator = 60;
	//���t���b�V�����[�g�̍ŏ��L�����@
	sd.BufferDesc.RefreshRate.Denominator = 1;
	//�\���t�H�[�}�b�g�@4�v�f��������32�r�b�g
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//�o�b�N�o�b�t�@�̃T�[�t�F�X�g�p�@CPU�A�N�Z�X�I�v�V������ݒ肷��@�o�͂Ŏg���悤�ɂ���
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//�o�͂���E�B���h�E�̃n���h��
	sd.OutputWindow = mHwnd;
	//�s�N�Z���P�ʂ̃T���v�����O��
	sd.SampleDesc.Count = 1;
	//�C���[�W�i���@-1�`0�܂Ŏw��ł���
	sd.SampleDesc.Quality = 0;
	//�E�B���h�E���[�h�ŋN������
	sd.Windowed = true;

	//DirectX�̃f�o�C�X�����
	hr = D3D11CreateDeviceAndSwapChain
	(NULL,mDriverType,NULL,flags,&fLevel,1,D3D11_SDK_VERSION,&sd,&mSwapChain,&mDevice,&mLevel,&mDeviceContext);
	if (FAILED(hr)) return S_FALSE;

	//�o�b�N�o�b�t�@�̊m��
	ID3D11Texture2D* back_buff;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buff);
	if (FAILED(hr)) 
	{
		ExitDX11();
		return S_FALSE;
	}


	//�[�x�o�b�t�@�Ŏg���e�N�X�`������
	D3D11_TEXTURE2D_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(depthDesc));
	depthDesc.Width = width;
	depthDesc.Height = height;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;

	ID3D11Texture2D* depthStencil = 0;
	hr = mDevice->CreateTexture2D(&depthDesc, NULL, &depthStencil);

	//�[�x�o�b�t�@�̃r���[��񐶐�
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilView;
	ZeroMemory(&depthStencilView, sizeof(depthStencilView));
	depthStencilView.Format = depthDesc.Format;
	depthStencilView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilView.Texture2D.MipSlice = 0;
	depthStencilView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	hr = mDevice->CreateDepthStencilView(depthStencil, &depthStencilView, &mDepthStencilView);
	if (depthStencil)
	{
		depthStencil->Release();
		depthStencil = 0;
	}

	//�[�x�o�b�t�@�̏�Ԑ���
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, (sizeof(depthStencilDesc)));
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = FALSE;
	hr = mDevice->CreateDepthStencilState(&depthStencilDesc,&mDepthStencilState);

	//�����_�[�^�[�Q�b�g�r���[����
	hr = mDevice->CreateRenderTargetView(back_buff,NULL,&mRenderTargetView);
	
	if (FAILED(hr))
	{
		ExitDX11();
		return S_FALSE;
	}

	//�r���[�|�[�g�ݒ�
	mView.Width = (FLOAT)width;
	mView.Height = (FLOAT)height;
	mView.MinDepth = 0.0f;
	mView.MaxDepth = 1.0f;
	mView.TopLeftX = 0.0f;
	mView.TopLeftY = 0.0f;
	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
	mDeviceContext->RSSetViewports(1, &mView);
	delete cParam;
	back_buff->Release();

	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	mDevice->CreateBlendState(&BlendDesc, &mBlendState);

	mDXRenderDataPool = std::make_unique<DXRenderDataPool>(mDevice,mDeviceContext);
	return S_OK;
}
//�I��
void DXManager::ExitDX11()
{
	//���������m�ۂ��Ă�����̂�S�ĊJ������
	if (mDeviceContext)
	{
		mDeviceContext->ClearState();
		mDeviceContext->Release();
	}
	if (mBlendState) mBlendState->Release();
	if (mRenderTargetView)mRenderTargetView->Release();
	if (mSwapChain) mSwapChain->Release();
	if (mDepthStencilView)mDepthStencilView->Release();
	if (mDepthStencilState)mDepthStencilState->Release();
	if (mDevice) mDevice->Release();
}
//�`��J�n�O�̃o�b�t�@�N���A
void DXManager::BeginScene(float r, float g, float b, float a)
{
	float color[] = {r,g,b,a};
	//��ʃN���A
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, color);
	//�[�x�o�b�t�@�N���A
	mDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}
//�`�揈�����I��������̉�ʂ����[�U�[�Ɍ�����
void DXManager::EndScene()
{
	if(mIsVsyncEnable)
	{
		//VSync�L
		mSwapChain->Present(mVsyncIntarval, 0);
	}
	else
	{
		//VSync��
		mSwapChain->Present(0, 0);
	}
}
//VSync�̗L����؂�ւ���
void DXManager::SetVsyncEnable(bool isEnable)
{
	mIsVsyncEnable = isEnable;
}

void DXManager::OMSetBlendState(bool blendFlg)
{
	if(blendFlg)
	{
		mDeviceContext->OMSetBlendState(mBlendState, NULL, 0xffffffff);
	}
	else
	{
		mDeviceContext->OMSetBlendState(NULL, NULL, 0xffffffff);
	}
}

