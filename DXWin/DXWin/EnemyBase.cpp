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

void EnemyBase::OnCollisionEnter()
{
	mHitPoint -= 1.0;
	//�̗͂��Ȃ��Ȃ����玩�g�̃A�N�e�B�u��؂�
	if (mHitPoint <= 0)
	{
		mGameObject->SetEnable(false);
	}
}
