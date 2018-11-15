#include "stdafx.h"
#include "DXTexture.h"

using namespace MyDirectX;

void DXTexture::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = mGameObject->GetID();
	mTag = mGameObject->GetTag();
	mRenderer = gameObject->GetComponent<TextureRenderer>();
	if (mRenderer == nullptr)
	{
		mRenderer = gameObject->AddComponent<TextureRenderer>();
	}
}

void DXTexture::SetTexture(const wchar_t * fileName)
{
	mRenderer->CreateMesh<TextureMesh>();
	mRenderer->CreateShader<TextureShader>();
	mRenderer->LoadTexture(const_cast<wchar_t*>(fileName));
}
