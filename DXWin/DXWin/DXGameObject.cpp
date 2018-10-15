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

//自身の初期化
HRESULT DXGameObject::Init(DXManager * dxManager)
{
	mDXManager = dxManager;
	mDXInput = mDXManager->GetDXInput();
	mDXCamera = mDXManager->GetDXCamera();
	return S_OK;
}

//持っているコンポーネントの更新処理を行う
void DXGameObject::Update()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->Update();
	}
}

//持っているコンポーネントの描画処理を行う
void DXGameObject::Render()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->Render();
	}
}

//持っているコンポーネントの解放処理を行う
void DXGameObject::Exit()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->Exit();
		delete pItr;
	}
}
