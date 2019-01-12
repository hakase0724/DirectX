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
	//���t���[���J�E���g���s��
	mWaitCount++;
	//�e���̔��ˊԊu���Ƃ�
	if (mBarrage->IsCoolTime(mWaitCount))
	{
		mWaitCount = 0;
		//�e���𐶐�����
		mBarrage->CreateBarrage(mBulletPool, mPlayer, mGameObject);
	}
}

void NormalEnemy::OnDisable()
{
	EnemyBase::OnDisable();
}

