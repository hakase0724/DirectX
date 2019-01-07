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
	mRenderer->CreateMesh<TextureMesh>();
	mRenderer->CreateShader<TextureShader>();
}

void DXTexture::SetTexture(const wchar_t * fileName)
{
	mRenderer->LoadTexture(const_cast<wchar_t*>(fileName));
}

void DXTexture::SetTexture(wchar_t * fileName)
{
	mRenderer->LoadTexture(fileName);
}

void DXTexture::SetColor(float r, float g, float b, float a)
{
	mRenderer->SetColor(r, g, b, a);
}
