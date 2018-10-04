#include "stdafx.h"
#include "DXCube.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "PrimitiveVertexInfo.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace MyDirectX;

DXCube::DXCube(DXManager * dxManager,DXInput* input, DXCamera* camera)
{
	mTransform.Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform.Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform.Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	mDXManager = dxManager;
	mDXInput = input;
	mDXCamera = camera;
}


DXCube::DXCube(TRANSFORM * transform, DXManager * dxManager, DXInput* input, DXCamera* camera)
{
	mTransform = *transform;
	mDXManager = dxManager;
	mDXInput = input;
	mDXCamera = camera;
}

DXCube::~DXCube()
{
	Exit();
}

void DXCube::SetTransform(TRANSFORM * transform)
{
	mTransform = *transform;
}

//������
bool DXCube::Init(TRANSFORM* transform, DXManager* dxManager, DXInput* input, DXCamera* camera)
{	
	mTransform = *transform;
	mDXManager = dxManager;
	mDXInput = input;
	mDXCamera = camera;
	if (FAILED(CreateShader())) return S_FALSE;
	if (FAILED(CreateConstantBuffer())) return S_FALSE;
	if (FAILED(CreateVertex())) return S_FALSE;
	if (FAILED(CreateIndex())) return S_FALSE;
	return S_OK;
}
//���t���[���s������
void DXCube::Update()
{
	XMStoreFloat4x4(&cBuffer.gWVP, mDXCamera->GetDXCameraParam(mTransform));
}
//�`�揈��
void DXCube::Render()
{
	//�f�[�^��n��
	mDXManager->GetDeviceContext()->UpdateSubresource(mConstantBuffer, 0, NULL, &cBuffer, 0, 0);

	//�p�C�v���C���\�z
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	//���_�o�b�t�@��ݒ�
	mDXManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	//�C���f�b�N�X�o�b�t�@�[�̐ݒ�
	mDXManager->GetDeviceContext()->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
	//���̓��C�A�E�g�ݒ�
	mDXManager->GetDeviceContext()->IASetInputLayout(mVertexLayout);
	//���_���̉��߂̎d����ݒ�
	mDXManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//���_�V�F�[�_�[��ݒ�
	mDXManager->GetDeviceContext()->VSSetShader(mVertexShader, NULL, 0);
	//�s�N�Z���V�F�[�_�[��ݒ�
	mDXManager->GetDeviceContext()->PSSetShader(mPixelShader, NULL, 0);
	//�萔�o�b�t�@��ݒ�
	mDXManager->GetDeviceContext()->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	//���X�^���C�Y�X�e�[�g��ݒ�
	mDXManager->GetDeviceContext()->RSSetState(mRasterizerState);
	//�[�x�o�b�t�@��Ԃ�ݒ�
	auto depth = mDXManager->GetDepthStencilState();
	mDXManager->GetDeviceContext()->OMSetDepthStencilState(depth, 0);
	//�`��
	mDXManager->GetDeviceContext()->DrawIndexed(mDrawNum, 0, 0);
}
//�������
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
//�V�F�[�_�[�Ɠ��̓��C�A�E�g�쐬
HRESULT DXCube::CreateShader()
{
	//�V�F�[�_�̐ݒ�
	ID3DBlob* compileVS = NULL;
	ID3DBlob* compilePS = NULL;
	//�V�F�[�_�[�̃R���p�C��
	//���s������I������
	HRESULT hr = D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "PS", "ps_5_0", 0, 0, &compilePS, NULL);
	if (FAILED(hr))
	{
		return S_FALSE;
	}
	hr = D3DCompileFromFile(L"shader.hlsl", nullptr, nullptr, "VS", "vs_5_0", 0, 0, &compileVS, NULL);
	if (FAILED(hr))
	{
		return S_FALSE;
	}
	//�f�o�C�X�ɃR���p�C�������V�F�[�_�[�����Ă���	
	hr = mDXManager->GetDevice()->CreateVertexShader(compileVS->GetBufferPointer(), compileVS->GetBufferSize(), NULL, &mVertexShader);
	if (FAILED(hr))
	{
		return S_FALSE;
	}
	hr = mDXManager->GetDevice()->CreatePixelShader(compilePS->GetBufferPointer(), compilePS->GetBufferSize(), NULL, &mPixelShader);
	if (FAILED(hr))
	{
		return S_FALSE;
	}
	//���_���C�A�E�g�ݒ�
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	//���̓��C�A�E�g�𐶐�����
	hr = mDXManager->GetDevice()->CreateInputLayout(layout, 2, compileVS->GetBufferPointer(), compileVS->GetBufferSize(), &mVertexLayout);
	if (FAILED(hr)) return S_FALSE;
	else
	{
		compileVS->Release();
		compilePS->Release();
		return S_OK;
	}	
}
//�萔�o�b�t�@�쐬
HRESULT DXCube::CreateConstantBuffer()
{
	//�萔�o�b�t�@����
	D3D11_BUFFER_DESC cb;
	//�o�b�t�@�T�C�Y
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	//�z�肷��ǂݏ������@�@
	cb.Usage = D3D11_USAGE_DEFAULT;
	//�p�C�v���C���ɂǂ̂悤�Ƀo�C���h���邩
	//�萔�o�b�t�@�Ƃ��ăo�C���h
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//CPU�A�N�Z�X�t���O
	cb.CPUAccessFlags = 0;
	//���܂Őݒ肵���t���O�ȊO�̂���
	cb.MiscFlags = 0;
	//�\���̂��\���̃o�b�t�@��\�����̃T�C�Y(�o�C�g�P��)
	cb.StructureByteStride = 0;
	//�o�b�t�@�����@NULL�̂Ƃ���Ƀf�[�^������Ƃ��̒l�ŏ��������Ă����
	HRESULT hr = mDXManager->GetDevice()->CreateBuffer(&cb, NULL, &mConstantBuffer);
	if (FAILED(hr)) return S_FALSE;
	else return S_OK;
}
//���_�f�[�^�쐬
HRESULT DXCube::CreateVertex()
{
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(VERTEX) * ARRAYSIZE(CubeVertex);
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
	data.pSysMem = CubeVertex;
	HRESULT hr = mDXManager->GetDevice()->CreateBuffer(&bd, &data, &mVertexBuffer);
	if (FAILED(hr)) return S_FALSE;
	else return S_OK;
}
//�C���f�b�N�X�쐬
HRESULT DXCube::CreateIndex()
{
	mDrawNum = ARRAYSIZE(CubeIndex);
	D3D11_BUFFER_DESC bd_index;
	bd_index.ByteWidth = sizeof(int) * mDrawNum;
	bd_index.Usage = D3D11_USAGE_DEFAULT;
	bd_index.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd_index.CPUAccessFlags = 0;
	bd_index.MiscFlags = 0;
	bd_index.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_index;
	data_index.pSysMem = CubeIndex;
	HRESULT hr = mDXManager->GetDevice()->CreateBuffer(&bd_index, &data_index, &mIndexBuffer);
	if (FAILED(hr)) return S_FALSE;
	else return S_OK;
}
//���X�^���C�Y�X�e�[�g�쐬
HRESULT DXCube::CreateRasterizeState()
{
	//���X�^���C�U�ݒ�
	D3D11_RASTERIZER_DESC rd = {};
	//�h��Ԃ��ݒ�@SOLID�͓h��Ԃ�
	rd.FillMode = D3D11_FILL_SOLID;
	//�`��ʐݒ�@���͑O�ʕ`��
	rd.CullMode = D3D11_CULL_FRONT;
	//�\�ʐݒ�@�����v��肷��ƕ\�ƔF���@FALSE���Ƌt�]����
	rd.FrontCounterClockwise = TRUE;
	mDXManager->GetDevice()->CreateRasterizerState(&rd, &mRasterizerState);

	return S_OK;
}
