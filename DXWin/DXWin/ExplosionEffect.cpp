#include "stdafx.h"
#include "ExplosionEffect.h"
#include "DXGameObject.h"
#include "DXTexture.h"
#include "DXAnimation.h"
#include "ExplosionEffectPool.h"

using namespace MyDirectX;

void ExplosionEffect::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	auto exTex = mGameObject->AddComponent<DXTexture>();
	auto exAnim = mGameObject->AddComponent<DXAnimation>();
	exAnim->SetAnimationTexture(exTex);
	exAnim->SetAnimationFile(_T("Texture/explosion1.png"));
	exAnim->SetAnimationFile(_T("Texture/explosion2.png"));
	exAnim->SetAnimationFile(_T("Texture/explosion3.png"));
	exAnim->SetAnimationFile(_T("Texture/explosion4.png"));
	exAnim->SetLoop(false);
	exAnim->SetTextureChangeCount(2);
}

void ExplosionEffect::OnDisable()
{
	mPool->ReturnExplosionEffect(mGameObject);
}
