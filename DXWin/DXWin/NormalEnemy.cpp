#include "stdafx.h"
#include "NormalEnemy.h"

using namespace MyDirectX;

void NormalEnemy::Initialize()
{
	mGameObject->ResetTransform();
	mWaitCount = mCoolCount;
	mHitPoint = mDefaultHitPoint;
	mBarrageName = BarrageName::TargetPlayer;
	mBarrage = mBarrageManager->GetBarrage(mBarrageName);
	mBarrage->Init();
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