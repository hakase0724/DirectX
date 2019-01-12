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
	mScore = 10.0;
}

void NormalEnemy::Update()
{
	//–ˆƒtƒŒ[ƒ€ƒJƒEƒ“ƒg‚ðs‚¤
	mWaitCount++;
	//’e–‹‚Ì”­ŽËŠÔŠu‚²‚Æ‚É
	if (mBarrage->IsCoolTime(mWaitCount))
	{
		mWaitCount = 0;
		//’e–‹‚ð¶¬‚·‚é
		mBarrage->CreateBarrage(mBulletPool, mPlayer, mGameObject);
	}
}

void NormalEnemy::OnDisable()
{
	EnemyBase::OnDisable();
}

