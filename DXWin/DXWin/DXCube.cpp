#include "stdafx.h"
#include "DXCube.h"

using namespace DirectX;
using namespace MyDirectX;

DXCube::~DXCube()
{
	Exit();
}

void DXCube::Initialize(DXGameObject * gameObject)
{
	mDXManager = gameObject->GetDXManager();
	mDXInput = gameObject->GetDXInput();
	mDXCamera = gameObject->GetDXCamera();
	mTransform = gameObject->GetTransform();
	mDeviceContext = mDXManager->GetDeviceContext();
	mGameObject = gameObject;
	Init();
}

//������
bool DXCube::Init()
{
	//�V�F�[�_�ƃ��b�V�������ɕK�v�ȃp�����[�^
	mMesh = std::make_unique<CubeMesh>();
	mShader = std::make_unique<LightingShader>();
	//�ꕶ��Z�����ĉǐ����グ��
	auto factory = mDXManager->GetDXFactory();
	auto device = mDXManager->GetDevice();
	//�V�F�[�_�ƃ��b�V������
	factory->CreateMesh(mMesh.get(), device, &mVertexBuffer, &mIndexBuffer);
	factory->CreateShader(mShader.get(),device,&mVertexShader,&mPixelShader,&mVertexLayout,&mRasterizerState,&mConstantBuffer);
	//�`�悷�钸�_��
	mDrawNum = mMesh.get()->indexNum;
	return true;
}

//�`�揈��
void DXCube::Render()
{
	mTransform = mGameObject->GetTransform();
	auto cameraParam = mDXCamera->GetCameraParam();
	cBuffer.mW = mDXCamera->GetWorld(mTransform);
	cBuffer.mWVP = mDXCamera->GetDXCameraParam(mTransform);
	cBuffer.vColor = XMVectorSet(0, 1, 0, 1);
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
	mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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
	//�`��
	mDeviceContext->DrawIndexed(mDrawNum, 0, 0);
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