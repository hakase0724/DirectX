#include "stdafx.h"
#include "Bullet.h"
#include "CommonValues.h"
#include "BulletPool.h"

using namespace MyDirectX;

void Bullet::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mDXInput = mGameObject->GetDXInput();
	mId = mGameObject->GetID();
	mDXCamera = mGameObject->GetDXCamera();
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
	//スクリーン座標取得
	auto screenPos = mDXCamera->WorldToScreenPoint(transform);
	//返ってきた行列の中から座標を取得
	auto screenPosX = screenPos.m128_f32[0];
	auto screenPosY = screenPos.m128_f32[1];
	//画面中央はcHeight / 2
	//画面外に出たら
	if(screenPosY < -cHeight / 2)
	{
		mGameObject->SetEnable(false);
	}
	if(screenPosY > cHeight + cHeight / 2)
	{
		mGameObject->SetEnable(false);
	}
	if(screenPosX < -cWidth / 2)
	{
		mGameObject->SetEnable(false);
	}
	if (screenPosX > cWidth + cWidth / 2)
	{
		mGameObject->SetEnable(false);
	}
	
	
}

void Bullet::OnCollisionEnter()
{
	mGameObject->SetEnable(false);
}

void Bullet::OnDisable()
{
	ReturnPool();
}

void Bullet::ReturnPool()
{
	mBulletPool->ReturnBullet(mGameObject);
}
