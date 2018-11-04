#include "stdafx.h"
#include "BulletManager.h"

using namespace MyDirectX;

BulletManager::BulletManager()
{
}


BulletManager::~BulletManager()
{
	delete mMeshInfo;
	delete mShaderInfo;
}

void BulletManager::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = mGameObject->GetID();
}

DXGameObject * BulletManager::GetBullet()
{
	return nullptr;
}
