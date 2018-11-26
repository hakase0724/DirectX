#include "stdafx.h"
#include "ShaderFactory.h"
#include <d3dcompiler.h>
#include "DXManager.h"

#pragma comment(lib, "d3dcompiler.lib")
using namespace MyDirectX;

void ShaderFactory::Create(ShaderInfo * info, 
	ID3D11Device * device, 
	ID3D11VertexShader ** vertex, 
	ID3D11PixelShader ** pixel, 
	ID3D11InputLayout ** inputLayout, 
	ID3D11RasterizerState ** rasterizerState,
	ID3D11Buffer ** constantBuffer)
{
	CreateShader(info,device,vertex,pixel,inputLayout);
	CreateConstantBuffer(info, device,constantBuffer);
	CreateRasterizerState(info, device, rasterizerState);
}

void ShaderFactory::CreateShader(ShaderInfo * info, 
	ID3D11Device * device,
	ID3D11VertexShader ** vertex, 
	ID3D11PixelShader ** pixel,
	ID3D11InputLayout ** inputLayout)
{
	HRESULT hr;
	//�V�F�[�_�̐ݒ�
	ID3DBlob* compileVS = NULL;
	ID3DBlob* compilePS = NULL;
	//�V�F�[�_�[�̃R���p�C��
	hr = D3DCompileFromFile(info->shader->PixelName, nullptr, nullptr, info->shader->PixelEntry, info->shader->PixelVersion, 0, 0, &compilePS, NULL);
	if(FAILED(hr))
	{
		return;
	}
	hr = D3DCompileFromFile(info->shader->VertexName, nullptr, nullptr, info->shader->VertexEntry, info->shader->VertexVersion, 0, 0, &compileVS, NULL);
	if (FAILED(hr))
	{
		return;
	}
	//�f�o�C�X�ɃR���p�C�������V�F�[�_�[�����Ă���	
	device->CreateVertexShader(compileVS->GetBufferPointer(), compileVS->GetBufferSize(), NULL, vertex);
	device->CreatePixelShader(compilePS->GetBufferPointer(), compilePS->GetBufferSize(), NULL, pixel);
	//���̓��C�A�E�g�𐶐�����
	device->CreateInputLayout(info->shader->InputLayout, info->shader->LayoutNum, compileVS->GetBufferPointer(), compileVS->GetBufferSize(), inputLayout);
	compileVS->Release();
	compilePS->Release();
}

void ShaderFactory::CreateRasterizerState(ShaderInfo * info, ID3D11Device * device, ID3D11RasterizerState ** rasterizerState)
{
	//���X�^���C�U�ݒ�
	D3D11_RASTERIZER_DESC rd = {};
	//�h��Ԃ��ݒ�@SOLID�͓h��Ԃ�
	rd.FillMode = D3D11_FILL_SOLID;
	//�`��ʐݒ�@���͑O�ʕ`��
	rd.CullMode = D3D11_CULL_FRONT;
	//�\�ʐݒ�@�����v��肷��ƕ\�ƔF���@FALSE���Ƌt�]����
	rd.FrontCounterClockwise = TRUE;
	device->CreateRasterizerState(&rd, rasterizerState);
}

void ShaderFactory::CreateConstantBuffer(ShaderInfo * info, ID3D11Device * device, ID3D11Buffer ** constantBuffer)
{
	//�萔�o�b�t�@����
	D3D11_BUFFER_DESC cb;
	//�o�b�t�@�T�C�Y
	cb.ByteWidth = info->GetSize();
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
	device->CreateBuffer(&cb, NULL, constantBuffer);
}
