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

//�������ς݂�
bool mIsInit = false;
//�`�悷�钸�_��
int mDrawNum = 0;
//�E�B���h���̃n���h��
HWND mHwnd = NULL;
//�h���C�o�[�̎�ރI�v�V�����@NULL�̓f�o�b�O�p�炵��
D3D_DRIVER_TYPE mDriverType = D3D_DRIVER_TYPE_NULL;
//DirectX�̋@�\�T�|�[�g���x����ݒ肷��@�����DirectX11�̕׋�������11��ݒ肵��
D3D_FEATURE_LEVEL mLevel = D3D_FEATURE_LEVEL_11_0;
//DirectX�̉��z�h���C�o�[�@������������ԑ厖�Ȃ���
ID3D11Device* mDevice = NULL;
//�����_�����O�ɂ��ĐF�X�ݒ�ł�����̂炵��
ID3D11DeviceContext* mDeviceContext = NULL;
//�`�揈���ɕK�v�ȏ�񂪓���o�b�t�@�[�炵��
IDXGISwapChain* mSwapChain = NULL;
//�����_�����O���Ɏg����T�u���\�[�X����
ID3D11RenderTargetView* mRenderTargetView = NULL;
//���̓A�Z���u���X�e�[�W�̓��̓f�[�^�ɃA�N�Z�X�@���͂��ĂȂ񂩂���Ƃ��Ɏg������
ID3D11InputLayout* mVertexLayout;
//���_�V�F�[�_�[�Ǘ�
ID3D11VertexShader* mVertexShader;
//�s�N�Z���V�F�[�_�[�Ǘ�
ID3D11PixelShader* mPixelShader;
//�f�[�^�o�b�t�@�@�V�F�[�_�[�Ƃ̃f�[�^�̂����Ɏg���Ă���
ID3D11Buffer* mConstantBuffer;
//���_�V�F�[�_�[�p�̃o�b�t�@
ID3D11Buffer* mVertexBuffer;
//���X�^���C�U�X�e�[�W�̃��X�^���C�U�X�e�[�g�փA�N�Z�X�@�ʂƂ��o���Ƃ����X�^�`���ŏo���Ă��邩��K�v�炵��
ID3D11RasterizerState* mRasterizerState;

HRESULT InitDX11(HWND hwnd)
{
	//���������Ă��珈�����Ȃ�
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

	//�X���b�v�`�F�C���ݒ�
	DXGI_SWAP_CHAIN_DESC sd;
	//�n�������̑S�Ă�0�N���A����
	ZeroMemory(&sd,sizeof(sd));
	//�o�b�t�@�[��
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
	//�o�b�N�o�b�t�@�[�̃T�[�t�F�X�g�p�@CPU�A�N�Z�X�I�v�V������ݒ肷��@�o�͂Ŏg���悤�ɂ���
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
	if (FAILED(hr)) return hr;
	//�o�b�N�o�b�t�@�[�̊m�ہ@���ʕ`��Ƃ��Ŏg���Ă���
	ID3D11Texture2D* back_buff = NULL;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buff);
	if (FAILED(hr)) return hr;
	//�����_�[�^�[�Q�b�g�r���[����
	hr = mDevice->CreateRenderTargetView(back_buff,NULL,&mRenderTargetView);
	back_buff->Release();
	if (FAILED(hr)) return hr;
	//�����_�[�^�[�Q�b�g��ݒ肷��
	mDeviceContext->OMSetRenderTargets(1,&mRenderTargetView,NULL);

	//�r���[�|�[�g�ݒ�
	D3D11_VIEWPORT view;
	view.Width = (FLOAT)width;
	view.Height = (FLOAT)height;
	view.MinDepth = 0.0f;
	view.MaxDepth = 1.0f;
	view.TopLeftX = 0.0f;
	view.TopLeftY = 0.0f;
	mDeviceContext->RSSetViewports(1, &view);

	//�V�F�[�_�̐ݒ�
	ID3DBlob* compileVS = NULL;
	ID3DBlob* compilePS = NULL;
	//�V�F�[�_�[�̃R���p�C��
	//���s������I������
	if (FAILED(D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &compilePS, NULL))) return S_FALSE;
	if (FAILED(D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &compileVS, NULL))) return S_FALSE;
	//�f�o�C�X�ɃR���p�C�������V�F�[�_�[�����Ă���
	mDevice->CreateVertexShader(compileVS->GetBufferPointer(), compileVS->GetBufferSize(), NULL, &mVertexShader);
	mDevice->CreatePixelShader(compilePS->GetBufferPointer(), compilePS->GetBufferSize(), NULL, &mPixelShader);
	
	//���_���C�A�E�g�ݒ�
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
	//���̓��C�A�E�g�𐶐�����
	mDevice->CreateInputLayout(layout, 1, compileVS->GetBufferPointer(), compileVS->GetBufferSize(), &mVertexLayout);
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
	//�萔�o�b�t�@�[�Ƃ��ăo�C���h
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//CPU�A�N�Z�X�t���O
	//�������݂��ł���
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//���܂Őݒ肵���t���O�ȊO�̂���
	cb.MiscFlags = 0;
	//�\���̂��\���̃o�b�t�@�[��\�����̃T�C�Y(�o�C�g�P��)
	cb.StructureByteStride = 0;
	//�o�b�t�@�[�����@NULL�̂Ƃ���Ƀf�[�^������Ƃ��̒l�ŏ��������Ă����
	mDevice->CreateBuffer(&cb, NULL, &mConstantBuffer);

	//���_�f�[�^�ƃo�b�t�@����
	VERTEX vertex[] = 
	{
		XMFLOAT3(-0.2f, 0.5f, 0.0f),
		XMFLOAT3(0.2f, 0.5f, 0.0f),
		XMFLOAT3(-0.0f, 0.3f, 0.0f)
	};
	//���_���v�Z
	//�z��̗v�f�������߂邽�߂ɔz��S�̂̃T�C�Y��擪�v�f�̃T�C�Y�Ŋ���
	mDrawNum = sizeof(vertex) / sizeof(vertex[0]);
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(VERTEX) * mDrawNum;
	//GPU����ǂݏ������ł���
	bd.Usage = D3D11_USAGE_DEFAULT;
	//���_�o�b�t�@�[�Ƃ��ăo�C���h
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//�p�ӂ��ꂽ�萔��ݒ肵�Ȃ��Ə���ɍœK�������炵��
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	//�T�u���\�[�X�̏������|�C���^�[
	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = vertex;
	mDevice->CreateBuffer(&bd, &data, &mVertexBuffer);

	//���X�^���C�U�ݒ�
	D3D11_RASTERIZER_DESC rd;
	//�h��Ԃ��ݒ�@SOLID�͓h��Ԃ�
	rd.FillMode = D3D11_FILL_SOLID;
	//�`��ʐݒ�@���͗��ʕ`��
	rd.CullMode = D3D11_CULL_NONE;
	//�\�ʐݒ�@�����v��肷��ƕ\�ƔF���@FALSE���Ƌt�]����
	rd.FrontCounterClockwise = TRUE;
	mDevice->CreateRasterizerState(&rd, &mRasterizerState);

	//�p�C�v���C���\�z
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	//���_�o�b�t�@�[��ݒ�
	mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	//���̓��C�A�E�g�ݒ�
	mDeviceContext->IASetInputLayout(mVertexLayout);
	//���_���̉��߂̎d����ݒ�
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//���_�V�F�[�_�[��ݒ�
	mDeviceContext->VSSetShader(mVertexShader, NULL, 0);
	//�s�N�Z���V�F�[�_�[��ݒ�
	mDeviceContext->PSSetShader(mPixelShader, NULL, 0);
	//�萔�o�b�t�@�[��ݒ�
	mDeviceContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	mIsInit = true;
	return S_OK;
}

void RenderDX11()
{
	//�h��Ԃ��F�̐ݒ�Ɖ�ʃN���A
	float color[4] = { 0.0f,0.0f,0.0f,1.0f };
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, color);

	//�J�����p�����[�^�v�Z
	XMVECTOR eye_pos = XMVectorSet(0.0f,0.0f,-2.0f,1.0f);
	XMVECTOR eye_lookup = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	XMVECTOR eye_up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	XMMATRIX view = XMMatrixLookAtLH(eye_pos, eye_lookup, eye_up);
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, cWidth / cHeight,0.1f,100.0f);
	XMMATRIX world = XMMatrixRotationZ(0);

	//�f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE data;
	CONSTANT_BUFFER buffer;
	buffer.mWVP = XMMatrixTranspose(world * view * proj);
	mDeviceContext->Map(mConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	memcpy_s(data.pData, data.RowPitch, (void*)(&buffer), sizeof(buffer));
	mDeviceContext->Unmap(mConstantBuffer, 0);

	//�`��
	mDeviceContext->Draw(mDrawNum, 0);
	mSwapChain->Present(0, 0);
}

void ExitDX11()
{
	//���������ĂȂ������珈�����Ȃ�
	if (!mIsInit) return;
	//���������m�ۂ��Ă�����̂�S�ĊJ������
	if (mDeviceContext)
	{
		mDeviceContext->ClearState();
		mDeviceContext->Release();
	}
	if (mRenderTargetView) mRenderTargetView->Release();
	if (mSwapChain) mSwapChain->Release();
	if (mVertexLayout) mVertexLayout->Release();
	if (mVertexBuffer) mVertexBuffer->Release();
	if (mVertexShader) mVertexShader->Release();
	if (mPixelShader) mPixelShader->Release();
	if (mConstantBuffer) mConstantBuffer->Release();
	if (mRasterizerState) mRasterizerState->Release();
	if (mDevice) mDevice->Release();
	mIsInit = false;
}
