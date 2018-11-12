#include "stdafx.h"
#include "DXGameObject.h"
#include "DXGameObjectManager.h"

using namespace DirectX;
using namespace MyDirectX;

DXGameObject::DXGameObject(DXManager * dxManager, DXGameObjectManager * dxGameObjectManager)
{
	mTransform = std::make_unique<TRANSFORM>();
	mTransform->Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform->Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform->Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	mDXManager = dxManager;
	mDXInput = mDXManager->GetDXInput();
	mDXCamera = mDXManager->GetDXCamera();
	mDXGameObjectManager = dxGameObjectManager;
	mName = "GameObject";
}

DXGameObject::DXGameObject(TRANSFORM * transform, DXManager * dxManager, DXGameObjectManager * dxGameObjectManager)
{
	mTransform = std::make_unique<TRANSFORM>();
	mTransform->Position = transform->Position;
	mTransform->Rotation = transform->Rotation;
	mTransform->Scale = transform->Scale;
	mDXManager = dxManager;
	mDXInput = mDXManager->GetDXInput();
	mDXCamera = mDXManager->GetDXCamera();
	mDXGameObjectManager = dxGameObjectManager;
	mName = "GameObject";
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

//持っているコンポーネントの初期化処理を行う
void DXGameObject::InitializeComponent()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->Initialize();
	}
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

//持っているコンポーネントの更新処理が終わった後での更新処理
void DXGameObject::LateUpdate()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->LateUpdate();
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

//衝突した時の処理
void DXGameObject::OnCollisionEnter()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->OnCollisionEnter();
	}
}

//衝突が終わった時の処理
void DXGameObject::OnCollisionExit()
{
	for (auto itr = mComponentsList.begin(); itr != mComponentsList.end(); ++itr)
	{
		auto pItr = *itr;
		pItr->OnCollisionExit();
	}
}
