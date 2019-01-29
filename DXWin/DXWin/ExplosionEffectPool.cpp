#include "stdafx.h"
#include "ExplosionEffectPool.h"

using namespace MyDirectX;

void ExplosionEffectPool::CreatePreExplosionEffect(int preNum)
{
	for(int i = 0;i < preNum;i++)
	{
		CreateExplosionEffect();
	}
}

DXGameObject * ExplosionEffectPool::GetExplosionEffect(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 scale)
{
	DXGameObject* pGame = nullptr;
	if (mExplosionEffectList.size() <= 0)
	{
		pGame = CreateExplosionEffect();
	}
	else
	{
		pGame = mExplosionEffectList.back();
		mExplosionEffectList.pop_back();
	}
	auto gameTransform = pGame->GetTransform();
	gameTransform->Position = pos;
	gameTransform->Scale = scale;
	pGame->InitializeComponent();
	pGame->SetEnable(true);
	return pGame;
}

void ExplosionEffectPool::ReturnExplosionEffect(DXGameObject * explosionEffect)
{
	mExplosionEffectList.push_back(explosionEffect);
}

DXGameObject * ExplosionEffectPool::CreateExplosionEffect()
{
	auto explosion = mScene->Instantiate();
	explosion->SetTag(StaticInstantiateItem);
	auto exCom = explosion->AddComponent<ExplosionEffect>();
	exCom->SetPool(this);
	mExplosionEffectList.push_back(explosion);
	return explosion;
}
