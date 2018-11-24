#include "stdafx.h"
#include "BossEnemy.h"

using namespace MyDirectX;

void BossEnemy::Initialize()
{
	mGameObject->ResetTransform();
	mWaitCount = mCoolCount;
	mHitPoint = mDefaultHitPoint;
	mBarrageName = BarrageName::AllDirectionsSync;
	mBarrage = mBarrageManager->GetBarrage(mBarrageName);
	mBarrage->Init();
}

void BossEnemy::Update()
{
	//–ˆƒtƒŒ[ƒ€ƒJƒEƒ“ƒg‚ðs‚¤
	mWaitCount++;
	//’e–‹‚Ì”­ŽËŠÔŠu‚²‚Æ‚É
	if (mBarrage->IsCoolTime(mWaitCount))
	{
		mWaitCount = 0;
		//’e–‹‚ð¶¬‚·‚é
		mBarrage->CreateBarrage(mBulletPool, mPlayer, mGameObject);
		if (IsBarrageEnd())
		{
			ChangeBarrageName();
			mBarrage = mBarrageManager->GetBarrage(mBarrageName);
		}
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
