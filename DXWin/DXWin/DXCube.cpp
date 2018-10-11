#include "stdafx.h"
#include "DXCube.h"
#include <DirectXMath.h>

using namespace DirectX;
using namespace MyDirectX;

DXCube::DXCube(DXManager * dxManager)
{
	mTransform.Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform.Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform.Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);
	mDXManager = dxManager;
}

DXCube::DXCube(TRANSFORM * transform, DXManager * dxManager)
{
	mTransform = *transform;
	mDXManager = dxManager;
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
bool DXCube::Init()
{
	//���͂ƃJ�������擾
	mDXInput = mDXManager->GetDXInput();
	mDXCamera = mDXManager->GetDXCamera();
	//�V�F�[�_�ƃ��b�V���̏��ێ��N���X�𐶐�
	mMesh = std::make_unique<CubeMesh>();
	mShader = std::make_unique<NormalShader>();
	//�V�F�[�_�ƃ��b�V���̐���
	mFactory = std::make_unique<DXFactory>();
	mFactory->CreateMesh(mMesh.get(), mDXManager->GetDevice(), &mVertexBuffer, &mIndexBuffer);
	mFactory->CreateShader(mShader.get(), mDXManager->GetDevice(), &mVertexShader, &mPixelShader, &mVertexLayout, &mRasterizerState,&mConstantBuffer);
	//�`�悷�钸�_��
	mDrawNum = mMesh.get()->indexNum;
	return true;
}
//���t���[���s������
void DXCube::Update()
{
	if (mDXInput->GetInputState(DIK_A)) mTransform.Position.x -= 0.01f;
	if (mDXInput->GetInputState(DIK_D)) mTransform.Position.x += 0.01f;
	if (mDXInput->GetInputState(DIK_W)) mTransform.Position.y += 0.01f;
	if (mDXInput->GetInputState(DIK_S)) mTransform.Position.y -= 0.01f;
	XMStoreFloat4x4(&cBuffer.gWVP, mDXCamera->GetDXCameraParam(mTransform));
}
//�`�揈��
void DXCube::Render()
{
	//�f�[�^��n��
	mDXManager->GetDeviceContext()->UpdateSubresource(mConstantBuffer, 0, NULL, &cBuffer, 0, 0);
	//�p�C�v���C���\�z
	UINT stride = sizeof(VERTEX_DATA);
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