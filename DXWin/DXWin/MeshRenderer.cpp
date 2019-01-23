#include "stdafx.h"
#include "MeshRenderer.h"

using namespace DirectX;
using namespace MyDirectX;

void MeshRenderer::SetDefaultColor(float r, float g, float b, float a)
{
	mDefaultColor.r = r;
	mDefaultColor.g = g;
	mDefaultColor.b = b;
	mDefaultColor.a = a;
	mColor = mDefaultColor;
}

void MeshRenderer::SetColor(float r, float g, float b, float a)
{
	mColor.r = r;
	mColor.g = g;
	mColor.b = b;
	mColor.a = a;
}

void MeshRenderer::SetColor()
{
	mColor = mDefaultColor;
}

void MeshRenderer::Initialize(DXGameObject * gameObject)
{
	mDXManager = gameObject->GetDXManager();
	mDXCamera = gameObject->GetDXCamera();
	mDeviceContext = mDXManager->GetDeviceContext();
	mGameObject = gameObject;
	mDXFactory = mDXManager->GetDXFactory();
	mDevice = mDXManager->GetDevice();
	mTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	mDefaultColor.r = 0;
	mDefaultColor.g = 1;
	mDefaultColor.b = 0;
	mDefaultColor.a = 1;
	mColor = mDefaultColor;
}

void MeshRenderer::Initialize()
{
	mColor = mDefaultColor;
}

void MeshRenderer::Render()
{
	auto transform = mGameObject->GetTransform();
	auto cameraParam = mDXCamera->GetCameraParam();
	cBuffer.mW = mDXCamera->GetWorld(transform);
	cBuffer.mWVP = mDXCamera->GetDXCameraParam(transform);
	cBuffer.vColor = XMVectorSet(mColor.r, mColor.g, mColor.b, mColor.a);
	cBuffer.vLightPos = XMVectorSet(-1.0f, 1.0f, -2.0f, 1.0f);
	cBuffer.vEyePos = cameraParam.mPos;
	//�f�[�^��n��
	mDeviceContext->UpdateSubresource(mConstantBuffer, 0, NULL, &cBuffer, 0, 0);
	//�p�C�v���C���\�z
	UINT stride = sizeof(VERTEX_DATA);
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
	//���X�^���C�Y�X�e�[�g��ݒ�
	mDeviceContext->RSSetState(mRasterizerState);
	//�[�x�o�b�t�@��Ԃ�ݒ�
	auto depth = mDXManager->GetDepthStencilState();
	mDeviceContext->OMSetDepthStencilState(depth, 0);
	//�u�����h�X�e�[�g�ݒ�
	mDXManager->OMSetBlendState(mIsAlphaBlending);
	//�`��
	mDeviceContext->DrawIndexed(mDrawNum, 0, 0);
}

void MeshRenderer::Exit()
{
	if (mVertexBuffer)mVertexBuffer->Release();
	if (mVertexLayout)mVertexLayout->Release();
	if (mVertexShader)mVertexShader->Release();
	if (mPixelShader)mPixelShader->Release();
	if (mIndexBuffer)mIndexBuffer->Release();
	if (mConstantBuffer)mConstantBuffer->Release();
	if (mRasterizerState)mRasterizerState->Release();
}

void MeshRenderer::OnCollisionEnter2D(Collider2D* col)
{
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void MeshRenderer::OnCollisionExit2D(Collider2D* col)
{
	SetColor();
}