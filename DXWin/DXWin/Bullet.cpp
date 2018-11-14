#include "stdafx.h"
#include "Bullet.h"
#include "CommonValues.h"
#include "BulletManager.h"
#include "DXGameObjectManager.h"

using namespace MyDirectX;

void Bullet::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mDXInput = mGameObject->GetDXInput();
	mId = mGameObject->GetID();
	mDXCamera = mGameObject->GetDXCamera();
	auto manager = mGameObject->GetDXGameObjectManager();
	mBulletManager = mGameObject->GetDXGameObjectManager()->GetBulletManager();
	mTag = mGameObject->GetTag();
}

void Bullet::Initialize()
{
	mId = mGameObject->GetID();
	mTag = mGameObject->GetTag();
}

void Bullet::Update()
{
	auto transform = mGameObject->GetTransform();
	transform->Position.x += mMoveVectol->x;
	transform->Position.y += mMoveVectol->y;
	//transform->Position.y += 0.01f;
	//スクリーン座標取得
	auto screenPos = mDXCamera->WorldToScreenPoint(transform);
	//返ってきた行列の中からy座標を取得
	auto screenPosX = screenPos.m128_f32[0];
	auto screenPosY = screenPos.m128_f32[1];
	//画面中央はcHeight / 2
	//画面外に出たら
	if(screenPosY < -cHeight / 2)
	{
		mBulletManager->ReturnBullet(mGameObject);
	}
	if(screenPosY > cHeight + cHeight / 2)
	{
		mBulletManager->ReturnBullet(mGameObject);
	}
	if(screenPosX < -cWidth / 2)
	{
		mBulletManager->ReturnBullet(mGameObject);
	}
	if (screenPosX > cWidth + cWidth / 2)
	{
		mBulletManager->ReturnBullet(mGameObject);
	}
	
	
}

void Bullet::OnCollisionEnter()
{
	mBulletManager->ReturnBullet(mGameObject);
}
