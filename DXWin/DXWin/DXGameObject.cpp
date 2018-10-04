#include "stdafx.h"
#include "DXGameObject.h"

using namespace DirectX;
using namespace MyDirectX;

DXGameObject::DXGameObject(DXManager * dxManager, DXInput* input, DXCamera* camera)
{
	mTransform.Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform.Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mTransform.Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	Init(dxManager,input,camera);
}

DXGameObject::DXGameObject(TRANSFORM *transform, DXManager * dxManager, DXInput* input, DXCamera* camera)
{
	mTransform = *transform;
	Init(dxManager, input, camera);
}


DXGameObject::~DXGameObject()
{
	Exit();
}

void DXGameObject::SetTransform(TRANSFORM * transform)
{
	mTransform = *transform;
}

template<typename T>
void DXGameObject::AddComponent()
{
	mComponentList.push_back(std::make_unique<T>());
	mComponentList.back()->Init(mTransform,mDXManager,mDXInput,mDXCamera);
}

HRESULT DXGameObject::Init(DXManager * dxManager, DXInput* input, DXCamera* camera)
{
	mDXManager = dxManager;
	mDXInput = input;
	mDXCamera = camera;
	return S_OK;
}

void DXGameObject::Update()
{
	for(int i = 0;i < mComponentList.size();i++)
	{
		mComponentList[i]->Update();
	}
}

void DXGameObject::Render()
{
	for (int i = 0; i < mComponentList.size(); i++)
	{
		mComponentList[i]->Render();
	}
}

void DXGameObject::Exit()
{
}
