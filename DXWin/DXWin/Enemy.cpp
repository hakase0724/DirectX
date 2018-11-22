#include "stdafx.h"
#include "Enemy.h"
#include "DXGameObjectManager.h"
#include <math.h>

using namespace MyDirectX;

void Enemy::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = mGameObject->GetID();
	mWaitCount = mCoolCount;
	HitPoint = 1000.0;
	//�e���N���X����
	mBarrageManager = std::make_unique<BarrageManager>();
	mBarrageName = BarrageName::SixWayRazer;
	mBarrage = mBarrageManager->GetBarrage(mBarrageName);
}

void Enemy::Initialize()
{
	//mGameObject->ResetTransform();
	mWaitCount = mCoolCount;
	HitPoint = 1000.0;
	mBarrageName = BarrageName::SixWayRazer;
	mBarrage = mBarrageManager->GetBarrage(mBarrageName);
}

void Enemy::Update()
{
	//���t���[���J�E���g���s��
	mWaitCount++;
	//�e���̔��ˊԊu���Ƃ�
	if(mBarrage->IsCoolTime(mWaitCount))
	{
		mWaitCount = 0;
		//�e���𐶐�����
		mBarrage->CreateBarrage(mBulletPool, mPlayer, mGameObject);
		if (mBarrage->IsBarrageEnd()) 
		{
			ChangeBarrageName();
			mBarrage = mBarrageManager->GetBarrage(mBarrageName);
		}
	}
}

void Enemy::OnCollisionEnter()
{
	HitPoint -= 1.0;
	//�̗͂��Ȃ��Ȃ����玩�g�̃A�N�e�B�u��؂�
	if (HitPoint <= 0)
	{
		mGameObject->SetEnable(false);
	}
}

void Enemy::ChangeBarrageName()
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
