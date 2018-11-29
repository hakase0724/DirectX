#include "stdafx.h"
#include "BossEnemy.h"

using namespace MyDirectX;

void BossEnemy::Initialize()
{
	mCollider->SetEnable(false);
	mState = Entry;
	mGameObject->ResetTransform();
	mWaitCount = mCoolCount;
	mHitPoint = mDefaultHitPoint;
	mBarrageName = BarrageName::AllDirectionsSync;
	mBarrage = mBarrageManager->GetBarrage(mBarrageName);
	mBarrage->Init();
	mTransform = mGameObject->GetTransform();
	mMoveVecX = mBattleStartPos.x - mTransform->Position.x;
	mMoveVecY = mBattleStartPos.y - mTransform->Position.y;
	//ベクトルの正規化
	auto len = sqrtf(mMoveVecX * mMoveVecX + mMoveVecY * mMoveVecY);
	mMoveVecX /= len;
	mMoveVecY /= len;
	mMoveVecX *= MOVESPPED;
	mMoveVecY *= MOVESPPED;
	mHitPoint = 0;
}

void BossEnemy::Update()
{
	switch (mState)
	{
	//ボス登場ステートの処理
	case Entry:
		//ボスの体力バーが動く演出のため体力を増加させる
		if(mHitPoint + mDefaultHitPoint / 100.0 <= mDefaultHitPoint)
		{
			mHitPoint = mHitPoint + mDefaultHitPoint / 100.0;
		}
		else if(mHitPoint + mDefaultHitPoint / 100.0 > mDefaultHitPoint)
		{
			mHitPoint = mDefaultHitPoint;
		}
		//設定した開始位置に到達したら弾幕展開を開始する
		if(abs(mTransform->Position.x - mBattleStartPos.x) <= EPSILON)
		{
			if(abs(mTransform->Position.y - mBattleStartPos.y) <= EPSILON)
			{
				mCollider->SetEnable(true);
				mState = Battle;
				break;
			}
		}
		//画面外から開始位置へ移動
		mTransform->Position.x += mMoveVecX;
		mTransform->Position.y += mMoveVecY;
		break;
	case Battle:
		//毎フレームカウントを行う
		mWaitCount++;
		//弾幕の発射間隔ごとに
		if (mBarrage->IsCoolTime(mWaitCount))
		{
			mWaitCount = 0;
			//弾幕を生成する
			mBarrage->CreateBarrage(mBulletPool, mPlayer, mGameObject);
			if (IsBarrageEnd())
			{
				ChangeBarrageName();
				mBarrage = mBarrageManager->GetBarrage(mBarrageName);
			}
		}
		break;
	case BossDie:
		break;
	default:
		break;
	}
}

void BossEnemy::ChangeBarrageName()
{
	switch (mBarrageName)
	{
	case BarrageName::AllDirectionsSync:
		mBarrageName = BarrageName::TargetPlayer;
		break;
	case BarrageName::TargetPlayer:
		mBarrageName = BarrageName::SixWayRazer;
		break;
	case BarrageName::SixWayRazer:
		mBarrageName = BarrageName::AllDirectionsSync;
		break;
	default:
		break;
	}
}
