#include "stdafx.h"
#include "Player.h"
#include "DXGameObjectManager.h"

using namespace MyDirectX;

void Player::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mDXInput = mGameObject->GetDXInput();
	auto transform = mGameObject->GetTransform();
	transform->Scale.x /= 2.0f;
	transform->Scale.y /= 2.0f;
	transform->Scale.z /= 2.0f;
	mId = mGameObject->GetID();
	mGameObject->SetDefaultTransform(transform);
	mWaitCount = mCoolCount;
	HitPoint = 4.0;
}

void Player::Initialize()
{
	mGameObject->ResetTransform();
	mWaitCount = mCoolCount;
	HitPoint = 4.0f;
}

void Player::Update()
{
	//毎フレームカウントを行う
	mWaitCount++;
	
	if(!isCoolTime())
	{
		//発射しない
	}
	else if (mDXInput->GetInputState(DIK_Z))
	{
		//複数発射する用テストコード
		auto bulletNum = 4;
		for(int i = 0;i < bulletNum;i++)
		{
			auto game = mBulletPool->GetBullet(mGameObject->GetTransform(), Tag::PlayerBullet);
			auto gameTransform = game->GetTransform();
			//各弾同士の間隔
			auto offset = gameTransform->Scale.x;
			gameTransform->Position.x += offset * (i - (float)bulletNum / 3.0f);
		}
	}	
	else if(!mDXInput->GetInputState(DIK_Z))
	{
		//発射しなかった場合は発射可能状態にしておく
		mWaitCount = mCoolCount - 1;
	}
}

void Player::OnCollisionEnter()
{
	HitPoint -= 1.0;
	//体力がなくなったら自身のアクティブを切る
	if(HitPoint <= 0)
	{
		mGameObject->SetEnable(false);
	}
}

bool Player::isCoolTime()
{
	if(mWaitCount % mCoolCount == 0)
	{
		mWaitCount = 0;
		return true;
	}
	else
	{
		return false;
	}
}
