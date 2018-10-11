#include "stdafx.h"
#include "DXGameObjectManager.h"
#include "dinput.h"

using namespace MyDirectX;
using namespace DirectX;
DXGameObjectManager::DXGameObjectManager(HWND hwnd)
{
	CreateResources(hwnd);
	CreateGameObject();
}

void DXGameObjectManager::CreateResources(HWND hwnd)
{
	//DirectX���\�[�X�Ǘ�
	mDXManager = std::make_unique<DXManager>(hwnd);
}

void DXGameObjectManager::CreateGameObject()
{
	//�L���[�u�𐶐�
	//�L���[�u�̏���transform
	//auto transform = new TRANSFORM(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.5f));
	mDXCube = std::make_unique<DXCube>(mDXManager.get());
	mDXCube->Init();
	//delete transform;
}

DXGameObjectManager::~DXGameObjectManager(){}

HRESULT DXGameObjectManager::Init(HWND hwnd)
{
	return S_OK;
}

BOOL DXGameObjectManager::Update()
{
	//���݂̓��͏�Ԃ��擾
	mDXManager->GetDXInput()->SetInputState();
	//���������I�u�W�F�N�g�̍X�V����
	mDXCube->Update();
	if (mDXManager->GetDXInput()->GetInputState(DIK_ESCAPE))
		return FALSE;
	return TRUE;
}

void DXGameObjectManager::Render()
{
	//�o�b�t�@�N���A
	mDXManager->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);
	//���������I�u�W�F�N�g�̃����_�����O����
	mDXCube->Render();
	//��ʕ\��
	mDXManager->EndScene();
}


