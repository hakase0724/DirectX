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
	mMoveVectol = new Vec2(0, 0);
}

void Bullet::Initialize()
{
	mId = mGameObject->GetID();
	mTag = mGameObject->GetTag();
	mFixedXAxiz = nullptr;
	mFixedYAxiz = nullptr;
	isXFixed = false;
	isYFixed = false;
}

void Bullet::Update()
{
	auto transform = mGameObject->GetTransform();
	transform->Position.x += mMoveVectol->x;
	transform->Position.y += mMoveVectol->y;
	//座標固定フラグが立っていれば座標を上書きする
	if(isXFixed)
	{
		transform->Position.x = *mFixedXAxiz;
	}
	if(isYFixed)
	{
		transform->Position.y = *mFixedYAxiz;
	}
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

void Bullet::OnCollisionEnter2D(Collider2D* col)
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
