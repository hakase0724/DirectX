#include "stdafx.h"
#include "EnemyBase.h"

using namespace MyDirectX;

void EnemyBase::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = mGameObject->GetID();
	mWaitCount = mCoolCount;
}

bool EnemyBase::IsBarrageEnd()
{
	mShotCount++;
	if(mShotCount >= mBarrage->GetShotNum())
	{
		mShotCount = 0;
		return true;
	}
	else return false;
}

void EnemyBase::OnCollisionEnter2D(Collider2D* col)
{
	Damage(1.0);
}

void EnemyBase::Damage(double damage)
{
	mHitPoint -= damage;
	//体力がなくなったら自身のアクティブを切る
	if (mHitPoint <= 0)
	{
		mGameObject->SetEnable(false);
	}
}
