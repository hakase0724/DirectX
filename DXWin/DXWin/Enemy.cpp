#include "stdafx.h"
#include "Enemy.h"
#include "DXGameObjectManager.h"
#include <math.h>
#define pai = acos(-1.0)

using namespace MyDirectX;

void Enemy::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = mGameObject->GetID();
	mWaitCount = mCoolCount;
	auto transform = mGameObject->GetTransform();
	transform->Scale.x /= 2.0f;
	transform->Scale.y /= 2.0f;
	transform->Scale.z /= 2.0f;
	mBulletManager = mGameObject->GetDXGameObjectManager()->GetBulletManager();
	HitPoint = 100000;
	mBulletSpeed = 0.01f;
	mRadianCoefficient = acos(-1.0f) / 180.0f;
	mAngle = 0.0f;
}

void Enemy::Update()
{
	//���t���[���J�E���g���s��
	mWaitCount++;

	if (isCoolTime())
	{
		//�����Ƒ���̍��W����ڕW�֌������x�N�g���쐬
		auto target = mPlayer->GetTransform()->Position;
		auto myPos = mGameObject->GetTransform()->Position;
		//�G���玩�@�ւ̃x�N�g��
		auto vecX = (target.x - myPos.x);
		auto vecY = (target.y - myPos.y);
	
		//�x�N�g���̐��K��
		auto len = sqrtf(vecX * vecX + vecY * vecY);
		vecX /= len;
		vecY /= len;	
		//�e�̑��x��ݒ�
		vecX *= mBulletSpeed;
		vecY *= mBulletSpeed;
		//�x�N�g�������炷
		auto mcos = cos(mAngle * mRadianCoefficient);
		auto msin = sin(mAngle * mRadianCoefficient);
		auto vecX2 = vecX * mcos - vecY * msin;
		auto vecY2 = vecX * msin + vecY * mcos;
		vecX = vecX2;
		vecY = vecY2;
		//�������˂���p�e�X�g�R�[�h
		auto bulletNum = 36;
		for (int i = 0; i < bulletNum; i++)
		{
			auto mcos = cos(mAngle * mRadianCoefficient);
			auto msin = sin(mAngle * mRadianCoefficient);
			auto vecX2 = vecX * mcos - vecY * msin;
			auto vecY2 = vecX * msin + vecY * mcos;
			auto game = mBulletManager->GetBullet(mGameObject->GetTransform(), Tag::EnemyBullet, vecX2, vecY2);
			mAngle += 10.0f;
		}
	}
}

void Enemy::OnCollisionEnter()
{
	HitPoint--;
	//�̗͂��Ȃ��Ȃ����玩�g�̃A�N�e�B�u��؂�
	if (HitPoint <= 0)
	{
		mGameObject->SetEnable(false);
	}
}

bool Enemy::isCoolTime()
{
	if (mWaitCount % mCoolCount == 0)
	{
		mWaitCount = 0;
		return true;
	}
	else
	{
		return false;
	}
}
