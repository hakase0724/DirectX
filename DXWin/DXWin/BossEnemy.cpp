#include "stdafx.h"
#include "BossEnemy.h"
#include <random>

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
	mMoveVecX *= MOVE_SPPED;
	mMoveVecY *= MOVE_SPPED;
	//���o�Ŏg�p���邽�߂�0�ŏ�����
	mHitPoint = 0;
	//�{�X��|�����Ƃ��̃X�R�A
	mScore = 100.0;
	mDropItemType = NoDrop;
	mCreateExplosionNum = 0;
	mLastExplosionEffect = nullptr;
	//�����_���[���I���ɂ���
	auto renderer = mGameObject->GetComponent<TextureRenderer>();
	renderer->SetEnable(true);
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
			mHitPoint += mDefaultHitPoint / 100.0;
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
		mWaitCount++;
		//�Ƃ肠����2�t�����ƂɃG�t�F�N�g���o���Ă݂�
		if(mWaitCount % 2 == 0)
		{
			mWaitCount = 0;
			auto transform = *mGameObject->GetTransform();
			mCreateExplosionNum++;
			//�{�X�Ƃ��Ԃ��Č��ɂ������班���J�����ɋ߂Â���
			transform.Position.z -= 0.1f;
			if(mCreateExplosionNum < mExplosionNum)
			{
				//���j�����ꏊ�������_���ŃY����
				transform.Position.x += GetRangeRand(-0.5f, 0.5f);
				transform.Position.y += GetRangeRand(-0.5f, 0.5f);
				mPlayScene->CreateExplosionEffect(transform.Position);
			}
			else if(mCreateExplosionNum == mExplosionNum)
			{
				mLastExplosionEffect = mPlayScene->CreateExplosionEffect(transform.Position, transform.Scale);
				//�����_���[���I�t�ɂ���
				auto renderer = mGameObject->GetComponent<TextureRenderer>();
				renderer->SetEnable(false);
			}
		}
		//�ŏI���j�G�t�F�N�g����������Ă��Ȃ���΂����ŏI���
		if (mLastExplosionEffect == nullptr) break;
		//�ŏI���j�G�t�F�N�g���I��������{�X�̎��S�t���O�𗧂Ă�
		if (!mLastExplosionEffect->GetEnable())
		{
			mPlayScene->BossDie();
			mGameObject->SetEnable(false);
		}
		break;
	default:
		break;
	}
}

void BossEnemy::Damage(double damage)
{
	mHitPoint -= damage;
	if (mHitPoint <= 0)
	{
		mState = BossDie;
		//�V�[���ɓo�^����Ă���I�u�W�F�N�g���擾
		auto gameObjects = mGameObject->GetScene()->GetGameObjects();
		for (auto &game : *gameObjects)
		{
			//��A�N�e�B�u�Ȃ疳��
			if (!game->GetEnable()) continue;
			auto tag = game->GetTag();
			//�G�e�ȊO����
			if (tag != EnemyBullet) continue;
			mPlayScene->CreateScoreItem(game->GetTransform()->Position);
			game->SetEnable(false);
		}
		mCollider->SetEnable(false);
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

float BossEnemy::GetRangeRand(float minValue, float maxValue)
{
	//�V�[�h�l����������
	std::random_device rnd;
	//�����Z���k�E�c�C�X�^�����g���ė��������
	std::mt19937_64 mt64(rnd());
	//�͈͓��̗��U���z�����
	std::uniform_real_distribution<float> genRandFloat(minValue, maxValue);
	//���z�̒����琶�������������g����1�����l�����o��
	return genRandFloat(mt64);
}
