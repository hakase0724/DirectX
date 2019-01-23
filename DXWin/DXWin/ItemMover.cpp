#include "stdafx.h"
#include "ItemMover.h"
#include "CommonValues.h"
#include "DXGameObject.h"

using namespace MyDirectX;

void ItemMover::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mDXCamera = mGameObject->GetDXCamera();
	mId = mGameObject->GetID();
	mTag = mGameObject->GetTag();
	//何も設定しなかった場合の移動速度
	mMoveSpeed = 0.02f;
}

void ItemMover::Update()
{
	auto transform = mGameObject->GetTransform();
	transform->Position.y -= mMoveSpeed;
	//スクリーン座標取得
	auto screenPos = mDXCamera->WorldToScreenPoint(transform);
	//返ってきた行列の中から座標を取得
	auto screenPosX = screenPos.m128_f32[0];
	auto screenPosY = screenPos.m128_f32[1];
	//画面中央はcHeight / 2
	//画面外に出たら
	if (screenPosY < -cHeight / 2)
	{
		mGameObject->SetEnable(false);
	}
	if (screenPosY > cHeight + cHeight / 2)
	{
		mGameObject->SetEnable(false);
	}
	if (screenPosX < -cWidth / 2)
	{
		mGameObject->SetEnable(false);
	}
	if (screenPosX > cWidth + cWidth / 2)
	{
		mGameObject->SetEnable(false);
	}
}
