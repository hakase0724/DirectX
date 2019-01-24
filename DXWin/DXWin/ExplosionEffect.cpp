#include "stdafx.h"
#include "ExplosionEffect.h"
#include "DXGameObject.h"

using namespace MyDirectX;

void ExplosionEffect::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mRenderer = nullptr;
}

void ExplosionEffect::Initialize()
{
	if (mRenderer == nullptr) mRenderer = mGameObject->GetComponent<TextureRenderer>();
	mRenderer->SetAlphaBlendingFlg(true);
	mColor.r = 1.0f;
	mColor.g = 1.0f;
	mColor.b = 1.0f;
	mColor.a = 1.0f;
}

void ExplosionEffect::Update()
{
	auto transform = mGameObject->GetTransform();
	transform->Rotation.z += mRotationValue;
	transform->Scale.x *= (1 + mScaleUpRate);
	transform->Scale.y *= (1 + mScaleUpRate);
	transform->Scale.z *= (1 + mScaleUpRate);
	mColor.a -= mAlphaValue;
	mRenderer->SetColor(mColor.r, mColor.g, mColor.b, mColor.a);
	if (mColor.a <= 0)mGameObject->SetEnable(false);
}
