#include "stdafx.h"
#include "DXGameObject.h"

using namespace DirectX;
using namespace MyDirectX;

DXGameObject::DXGameObject(DXManager * dxManager)
{
	mTransform.Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform.Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform.Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	mDXManager = dxManager;
	mDXInput = mDXManager->GetDXInput();
	mDXCamera = mDXManager->GetDXCamera();
}

DXGameObject::DXGameObject(TRANSFORM *transform, DXManager * dxManager)
{
	mTransform = *transform;
	mDXManager = dxManager;
	mDXInput = mDXManager->GetDXInput();
	mDXCamera = mDXManager->GetDXCamera();
}


DXGameObject::~DXGameObject()
{
	Exit();
}

//���g�̏�����
HRESULT DXGameObject::Init(DXManager * dxManager)
{
	mDXManager = dxManager;
	mDXInput = mDXManager->GetDXInput();
	mDXCamera = mDXManager->GetDXCamera();
	return S_OK;
}

//�����Ă���R���|�[�l���g�̍X�V�������s��
void DXGameObject::Update()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->Update();
	}
}

//�����Ă���R���|�[�l���g�̕`�揈�����s��
void DXGameObject::Render()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->Render();
	}
}

//�����Ă���R���|�[�l���g�̉���������s��
void DXGameObject::Exit()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->Exit();
		delete pItr;
	}
}
