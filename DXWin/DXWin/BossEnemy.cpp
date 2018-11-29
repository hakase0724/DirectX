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
	//�x�N�g���̐��K��
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
	//�{�X�o��X�e�[�g�̏���
	case Entry:
		//�{�X�̗̑̓o�[���������o�̂��ߑ̗͂𑝉�������
		if(mHitPoint + mDefaultHitPoint / 100.0 <= mDefaultHitPoint)
		{
			mHitPoint = mHitPoint + mDefaultHitPoint / 100.0;
		}
		else if(mHitPoint + mDefaultHitPoint / 100.0 > mDefaultHitPoint)
		{
			mHitPoint = mDefaultHitPoint;
		}
		//�ݒ肵���J�n�ʒu�ɓ��B������e���W�J���J�n����
		if(abs(mTransform->Position.x - mBattleStartPos.x) <= EPSILON)
		{
			if(abs(mTransform->Position.y - mBattleStartPos.y) <= EPSILON)
			{
				mCollider->SetEnable(true);
				mState = Battle;
				break;
			}
		}
		//��ʊO����J�n�ʒu�ֈړ�
		mTransform->Position.x += mMoveVecX;
		mTransform->Position.y += mMoveVecY;
		break;
	case Battle:
		//���t���[���J�E���g���s��
		mWaitCount++;
		//�e���̔��ˊԊu���Ƃ�
		if (mBarrage->IsCoolTime(mWaitCount))
		{
			mWaitCount = 0;
			//�e���𐶐�����
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
