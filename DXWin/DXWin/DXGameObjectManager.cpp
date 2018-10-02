#include "stdafx.h"
#include "DXGameObjectManager.h"
#include "dinput.h"

using namespace MyDirectX;
using namespace DirectX;
DXGameObjectManager::DXGameObjectManager(HWND hwnd)
{
	//DirectX���\�[�X�Ǘ�
	mDXManager = std::unique_ptr<DXManager>(new DXManager(hwnd));

	//���͊Ǘ�
	mDXInput = std::unique_ptr<DXInput>(new DXInput(hwnd));

	//�J�����𐶐�
	auto cParam = new CameraParam
	(
		DirectX::XMVectorSet(0.0f, 1.0f, -2.3f, 1.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f),
		cWidth / cHeight
	);
	mDXCamera = std::unique_ptr<DXCamera>(new DXCamera(cParam));

	//�L���[�u�𐶐�
	mDXCube = std::unique_ptr<DXCube>(new DXCube(mDXManager.get()));
	//�L���[�u�̏���transform
	auto transform = new TRANSFORM(XMFLOAT3(-1.0f,0.0f,0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.5f, 1.5f, 1.5f));
	mDXCube2 = std::unique_ptr<DXCube>(new DXCube(transform, mDXManager.get()));
	transform = new TRANSFORM(XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.5f, 0.5f));
	mDXCube3 = std::unique_ptr<DXCube>(new DXCube(transform, mDXManager.get()));

	//�����������̂�j��
	delete cParam;
	delete transform;
}


DXGameObjectManager::~DXGameObjectManager()
{

}

HRESULT DXGameObjectManager::Init(HWND hwnd)
{
	return S_OK;
}

BOOL DXGameObjectManager::Update()
{
	//���݂̓��͏�Ԃ��擾
	mDXInput->SetInputState();	
	auto cube = mDXCube2->GetTransform();
	if (mDXInput->GetInputState(DIK_W)) cube.Position.y += 0.01f;
	if (mDXInput->GetInputState(DIK_A)) cube.Position.x -= 0.01f;
	if (mDXInput->GetInputState(DIK_S)) cube.Position.y -= 0.01f;
	if (mDXInput->GetInputState(DIK_D)) cube.Position.x += 0.01f;
	mDXCube2->SetTransform(cube);
	mDXCube->Update(mDXInput.get(), mDXCamera.get());
	mDXCube2->Update(mDXInput.get(), mDXCamera.get());
	mDXCube3->Update(mDXInput.get(), mDXCamera.get());
	if (mDXInput->GetInputState(DIK_ESCAPE))return FALSE;
	return TRUE;
}

void DXGameObjectManager::Render()
{
	//�o�b�t�@�N���A
	mDXManager->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	//���������I�u�W�F�N�g�̃����_�����O����
	mDXCube->Render();
	mDXCube2->Render();
	mDXCube3->Render();
	//��ʕ\��
	mDXManager->EndScene();
}
