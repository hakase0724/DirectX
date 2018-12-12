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

	// �V�F�[�_�p�ɃT���v�����쐬����
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
	//const���O��
	wchar_t* w = const_cast<wchar_t*>(text);
	//�I�u�W�F�N�g�v�[���փA�N�Z�X
	auto pool = mDXManager->GetDXRenderDataPool();
	//�t�H���g�e�N�X�`�����擾
	auto data = pool->GetFontTexture(w, fontName);
	mTexture = data->texture;
	mShaderResorceView = data->shaderView;
	//���������_���炸�炷
	mTransform = *mGameObject->GetTransform();
	mTransform.Position.x += xOffset;
	mTransform.Position.y += yOffset;
}

void TextRenderer::Render()
{
	auto cameraParam = mDXCamera->GetCameraParam();
	cTextureBuffer.mWVP = mDXCamera->GetDXCameraParam(&mTransform);
	cTextureBuffer.mColor = XMVectorSet(mColor.r, mColor.g, mColor.b, mColor.a);
	//�f�[�^��n��
	mDeviceContext->UpdateSubresource(mConstantBuffer, 0, NULL, &cTextureBuffer, 0, 0);
	//�p�C�v���C���\�z
	UINT stride = sizeof(TEXTURE_VERTEX_DATA);
	UINT offset = 0;
	//���_�o�b�t�@��ݒ�
	mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	//�C���f�b�N�X�o�b�t�@�[�̐ݒ�
	mDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
	//���̓��C�A�E�g�ݒ�
	mDeviceContext->IASetInputLayout(mVertexLayout);
	//���_���̉��߂̎d����ݒ�
	mDeviceContext->IASetPrimitiveTopology(mTopology);
	//���_�V�F�[�_�[��ݒ�
	mDeviceContext->VSSetShader(mVertexShader, NULL, 0);
	//�s�N�Z���V�F�[�_�[��ݒ�
	mDeviceContext->PSSetShader(mPixelShader, NULL, 0);
	//�萔�o�b�t�@��ݒ�
	mDeviceContext->VSSetConstantBuffers(0, 1, &mConstantBuffer);
	mDeviceContext->PSSetConstantBuffers(0, 1, &mConstantBuffer);
	//�e�N�X�`���`��ɕK�v�ȃ��\�[�X�̐ݒ�
	mDeviceContext->PSSetShaderResources(0, 1, &mShaderResorceView);
	mDeviceContext->PSSetSamplers(0, 1, &mSampler);
	//���X�^���C�Y�X�e�[�g��ݒ�
	mDeviceContext->RSSetState(mRasterizerState);
	//�[�x�o�b�t�@��Ԃ�ݒ�
	auto depth = mDXManager->GetDepthStencilState();
	mDeviceContext->OMSetDepthStencilState(depth, 0);
	//�`��
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
