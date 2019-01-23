#include "stdafx.h"
#include "NormalEnemy.h"
#include "PowerUpItem.h"

using namespace MyDirectX;

void NormalEnemy::Initialize()
{
	mGameObject->ResetTransform();
	mWaitCount = mCoolCount;
	mHitPoint = mDefaultHitPoint;
	mBarrageName = BarrageName::TargetPlayer;
	mBarrage = mBarrageManager->GetBarrage(mBarrageName);
	mBarrage->Init();
	//倒されたときのスコア
	mScore = 10.0;
}

void NormalEnemy::Update()
{
	//毎フレームカウントを行う
	mWaitCount++;
	//弾幕の発射間隔ごとに
	if (mBarrage->IsCoolTime(mWaitCount))
	{
		mWaitCount = 0;
		//弾幕を生成する
		mBarrage->CreateBarrage(mBulletPool, mPlayer, mGameObject);
	}
}

void NormalEnemy::OnDisable()
{
	EnemyBase::OnDisable();
}

