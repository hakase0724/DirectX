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
	mDXManager = std::unique_ptr<DXManager>(new DXManager(hwnd));
	//���͊Ǘ�
	mDXInput = std::unique_ptr<DXInput>(new DXInput(hwnd));
}

void DXGameObjectManager::CreateGameObject()
{
	//�J�����𐶐�
	auto cParam = new CameraParam
	(
		DirectX::XMVectorSet(0.0f, 0.0f, -3.5f, 1.0f),
		DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
		DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f),
		cWidth / cHeight
	);
	mDXCamera = std::unique_ptr<DXCamera>(new DXCamera(cParam));

	//�L���[�u�𐶐�
	//�L���[�u�̏���transform
	auto transform = new TRANSFORM(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.5f));
	auto transform2 = new TRANSFORM(XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.5f));
	mDXCube = std::make_unique<DXCube>(transform, mDXManager.get(), mDXInput.get(), mDXCamera.get());
	mDXCube->Init(transform, mDXManager.get(), mDXInput.get(), mDXCamera.get());
	//�����������̂�j��
	auto game = InstantiateGameObjcet();
	game->AddComponent<DXCube>();
	delete cParam;
	delete transform;
	delete transform2;
}

DXGameObject * DXGameObjectManager::InstantiateGameObjcet()
{
	mDXGameObjectArray.emplace_back(std::make_unique<DXGameObject>(mDXManager.get(), mDXInput.get(), mDXCamera.get()));
	return mDXGameObjectArray.back().get();
}

template<typename T>
void DXGameObjectManager::Instantiate()
{
	mDXGameObjectArray.emplace_back(std::make_unique<T>(mDXManager.get(), mDXInput.get(), mDXCamera.get()));
}

template<typename T>
void DXGameObjectManager::Instantiate(TRANSFORM *transform)
{
	mDXGameObjectArray.emplace_back(std::make_unique<T>(transform,mDXManager.get(), mDXInput.get(), mDXCamera.get()));
}

DXGameObjectManager::~DXGameObjectManager(){}

HRESULT DXGameObjectManager::Init(HWND hwnd)
{
	return S_OK;
}

BOOL DXGameObjectManager::Update()
{
	//���݂̓��͏�Ԃ��擾
	mDXInput->SetInputState();	
	mDXCube->Update();
	for(int i = 0;i < mDXGameObjectArray.size();i++)
	{
		mDXGameObjectArray[i]->Update();
	}
	if (mDXInput->GetInputState(DIK_ESCAPE))return FALSE;
	return TRUE;
}

void DXGameObjectManager::Render()
{
	//�o�b�t�@�N���A
	mDXManager->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);
	mDXCube->Render();
	//���������I�u�W�F�N�g�̃����_�����O����
	for (int i = 0; i < mDXGameObjectArray.size(); i++)
	{
		mDXGameObjectArray[i]->Render();
	}
	//��ʕ\��
	mDXManager->EndScene();
}


