#include "stdafx.h"
#include "DXManager.h"
#include "dinput.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace MyDirectX;
using namespace Microsoft::WRL;

struct VERTEX
{
	XMFLOAT3 V;
	XMFLOAT4 C;
};

struct CONSTANT_BUFFER
{
	XMMATRIX mWVP;
};

DXManager::DXManager(){}

HRESULT DXManager::InitDX11(HWND hwnd)
{
	//�J�����𐶐��������ݒ�
	mDXCamera = std::unique_ptr<DXCamera>(new DXCamera());
	mDXCamera->SetEyeParamWithRatio
	(
		XMVectorSet(0.0f, 1.0f, -2.3f, 1.0f),
		XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
		XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f),
		cWidth / cHeight
	);
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
	//���t���b�V�����[�g�̍ő�L�����@�v��60fps�����Ă��Ƃ��Ǝv��
	sd.BufferDesc.RefreshRate.Numerator = 60;
	//���t���b�V�����[�g�̍ŏ��L�����@���Ȃ��Ƃ�1fps�͕ۏ؂�����Ă��Ƃ��ȁE�E�E�H
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

	//�o�b�N�o�b�t�@�̊m�ہ@���ʕ`��Ƃ��Ŏg���Ă���
	std::unique_ptr<ID3D11Texture2D> back_buff;
	auto pBack_Buff = back_buff.get();;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBack_Buff);
	if (FAILED(hr)) 
	{
		ExitDX11();
		return S_FALSE;
	}

	//�����_�[�^�[�Q�b�g�r���[����
	hr = mDevice->CreateRenderTargetView(pBack_Buff,NULL,&mRenderTargetView);
	
	if (FAILED(hr))
	{
		ExitDX11();
		return S_FALSE;
	}

	//���͏�����
	mDXInput = std::unique_ptr<DXInput>(new DXInput());
	hr = mDXInput->InitDirectInput(hwnd);
	if (FAILED(hr))
	{
		ExitDX11();
		return S_FALSE;
	}

	//�r���[�|�[�g�ݒ�
	D3D11_VIEWPORT view;
	view.Width = (FLOAT)width;
	view.Height = (FLOAT)height;
	view.MinDepth = 0.0f;
	view.MaxDepth = 1.0f;
	view.TopLeftX = 0.0f;
	view.TopLeftY = 0.0f;	

	//�V�F�[�_�̐ݒ�
	ID3DBlob* compileVS = NULL;
	ID3DBlob* compilePS = NULL;
	//�V�F�[�_�[�̃R���p�C��
	//���s������I������
	hr = D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &compilePS, NULL);
	if (FAILED(hr))
	{
		ExitDX11();
		return S_FALSE;
	}
	hr = D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &compileVS, NULL);
	if (FAILED(hr))
	{
		ExitDX11();
		return S_FALSE;
	}
	//�f�o�C�X�ɃR���p�C�������V�F�[�_�[�����Ă���
	mDevice->CreateVertexShader(compileVS->GetBufferPointer(), compileVS->GetBufferSize(), NULL, &mVertexShader);
	mDevice->CreatePixelShader(compilePS->GetBufferPointer(), compilePS->GetBufferSize(), NULL, &mPixelShader);
	
	//���_���C�A�E�g�ݒ�
	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		{
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			0,
			12,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		}
	};
	//���̓��C�A�E�g�𐶐�����
	mDevice->CreateInputLayout(layout, 2, compileVS->GetBufferPointer(), compileVS->GetBufferSize(), &mVertexLayout);
	compileVS->Release();
	compilePS->Release();

	//�萔�o�b�t�@����
	D3D11_BUFFER_DESC cb;
	//�o�b�t�@�T�C�Y
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	//�z�肷��ǂݏ������@�@
	//GPU����ǂݍ��݂̂�CPU����͏������݂݂̂��ł���悤�ɂȂ�@1�t���[������CPU���畡����X�V���z�肳���ꍇ�ɐݒ肷��
	cb.Usage = D3D11_USAGE_DYNAMIC;
	//�p�C�v���C���ɂǂ̂悤�Ƀo�C���h���邩
	//�萔�o�b�t�@�Ƃ��ăo�C���h
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//CPU�A�N�Z�X�t���O
	//�������݂��ł���
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//���܂Őݒ肵���t���O�ȊO�̂���
	cb.MiscFlags = 0;
	//�\���̂��\���̃o�b�t�@��\�����̃T�C�Y(�o�C�g�P��)
	cb.StructureByteStride = 0;
	//�o�b�t�@�����@NULL�̂Ƃ���Ƀf�[�^������Ƃ��̒l�ŏ��������Ă����
	mDevice->CreateBuffer(&cb, NULL, &mConstantBuffer);

	//���_�f�[�^�ƃo�b�t�@����
	VERTEX vertex[] = 
	{
		{ XMFLOAT3(-0.5f, -0.5f, 0.5f),  XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, 0.5f),   XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f),  XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f),   XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(0.5f, 0.5f, 0.5f),    XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(0.5f, 0.5f, -0.5f),   XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, -0.5f),  XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
	};
	
	mDrawNum = ARRAYSIZE(vertex);
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(VERTEX) * mDrawNum;
	//GPU����ǂݏ������ł���
	bd.Usage = D3D11_USAGE_DEFAULT;
	//���_�o�b�t�@�Ƃ��ăo�C���h
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//�p�ӂ��ꂽ�萔��ݒ肵�Ȃ��Ə���ɍœK�������炵��
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	//�T�u���\�[�X�̏������|�C���^�[
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertex;
	mDevice->CreateBuffer(&bd, &data, &mVertexBuffer);

	//�|���S���̃C���f�b�N�X���
	int index[] =
	{
		0, 2, 1,
		0, 3, 2,

		0, 5, 4,
		0, 1, 5,

		1, 6, 5,
		1, 2, 6,

		2, 7, 6,
		2, 3, 7,

		0, 4, 7,
		0, 7, 3,

		4, 5, 7,
		5, 6, 7,

	};
	mDrawNum = ARRAYSIZE(index);
	D3D11_BUFFER_DESC bd_index;
	bd_index.ByteWidth = sizeof(int) * mDrawNum;
	bd_index.Usage = D3D11_USAGE_DEFAULT;
	bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd_index.CPUAccessFlags = 0;
	bd_index.MiscFlags = 0;
	bd_index.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_index;
	data_index.pSysMem = index;
	mDevice->CreateBuffer(&bd_index, &data_index, &mIndexBuffer);

	//���X�^���C�U�ݒ�
	D3D11_RASTERIZER_DESC rd = {};
	//�h��Ԃ��ݒ�@SOLID�͓h��Ԃ�
	rd.FillMode = D3D11_FILL_SOLID;
	//�`��ʐݒ�@���͑O�ʕ`��
	rd.CullMode = D3D11_CULL_FRONT;
	//�\�ʐݒ�@�����v��肷��ƕ\�ƔF���@FALSE���Ƌt�]����
	rd.FrontCounterClockwise = TRUE;
	mDevice->CreateRasterizerState(&rd, &mRasterizerState);

	//�p�C�v���C���\�z
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	//���_�o�b�t�@��ݒ�
	mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	//�C���f�b�N�X�o�b�t�@�[�̐ݒ�
	mDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
	//���̓��C�A�E�g�ݒ�
	mDeviceContext->IASetInputLayout(mVertexLayout.Get());
	//���_���̉��߂̎d����ݒ�
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//���_�V�F�[�_�[��ݒ�
	mDeviceContext->VSSetShader(mVertexShader.Get(), NULL, 0);
	//�s�N�Z���V�F�[�_�[��ݒ�
	mDeviceContext->PSSetShader(mPixelShader.Get(), NULL, 0);
	//���X�^���C�Y�X�e�[�g�̐ݒ�
	mDeviceContext->RSSetState(mRasterizerState.Get());
	//�萔�o�b�t�@��ݒ�
	mDeviceContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	//�����_�[�^�[�Q�b�g��ݒ肷��
	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, NULL);
	//�r���[�|�[�g�̐ݒ�
	mDeviceContext->RSSetViewports(1, &view);
	return S_OK;
}
BOOL MyDirectX::DXManager::UpdateDX11()
{
	//���͎擾
	mDXInput->SetInputState();
	if (mDXInput->GetInputState(DIK_UP)) xRote += 0.001f;
	if (mDXInput->GetInputState(DIK_DOWN)) xRote -= 0.001f;
	if (mDXInput->GetInputState(DIK_RIGHT)) yRote -= 0.001f;
	if (mDXInput->GetInputState(DIK_LEFT)) yRote += 0.001f;
	if (mDXInput->GetInputState(DIK_ESCAPE)) return FALSE;
	else return TRUE;
}
void DXManager::RenderDX11()
{
	//�w�i�h��Ԃ�
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, mColor);
	//�f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE data;
	CONSTANT_BUFFER buffer;
	buffer.mWVP = mDXCamera->GetDXCameraParam(xRote, yRote);
	//�`���~
	mDeviceContext->Map(mConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	//�f�[�^�X�V
	memcpy_s(data.pData, data.RowPitch, (void*)(&buffer), sizeof(buffer));
	//�`��ĊJ
	mDeviceContext->Unmap(mConstantBuffer, 0);
	//�`��
	mDeviceContext->DrawIndexed(mDrawNum, 0, 0);
	//���ʕ`�悵�����̂�\�ɓW�J����
	mSwapChain->Present(0, 0);
}
void DXManager::ExitDX11()
{
	//���������m�ۂ��Ă�����̂�S�ĊJ������
	mDXInput->ExitDirectInput();
	if (mDeviceContext)
	{
		mDeviceContext->ClearState();
		mDeviceContext.Reset();
	}
	if (mRenderTargetView) mRenderTargetView->Release();
	if (mSwapChain) mSwapChain.Reset();
	if (mVertexLayout) mVertexLayout.Reset();
	if (mVertexBuffer) mVertexBuffer->Release();
	if (mVertexShader) mVertexShader.Reset();
	if (mPixelShader) mPixelShader.Reset();
	if (mConstantBuffer) mConstantBuffer->Release();
	if (mRasterizerState) mRasterizerState.Reset();
	if (mIndexBuffer) mIndexBuffer->Release();
	if (mDevice) mDevice.Reset();
}

