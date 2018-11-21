#include "stdafx.h"
#include "SixWayRazerBarrage.h"
#include "DXGameObject.h"
#include "BulletManager.h"
#include "BulletPool.h"

using namespace MyDirectX;
SixWayRazerBarrage::SixWayRazerBarrage()
{
	mName = BarrageName::SixWayRazer;
	mRazerNum = 6.0f;
	mCoolTime = 10;
	mBulletSpeed = 0.02f;
	mBulletNum = 10;
	mAngle = 360.0f / mRazerNum;
	auto radian = ToRadian(mAngle);
	mCosAngle = cos(radian);
	mSinAngle = sin(radian);
	mCount = 0;
}

bool SixWayRazerBarrage::IsBarrageEnd()
{
	mCount++;
	if (mCount >= mBulletNum)
	{
		mCount = 0;
		return true;
	}
	else
	{
		return false;
	}
}

void SixWayRazerBarrage::CreateBarrage(BulletManager * manager, DXGameObject * player, DXGameObject * enemy)
{
	//�G���玩�@�ւ̃x�N�g��
	auto vecX = 0.0f;
	auto vecY = -1.0f;
	//�x�N�g���̐��K��
	Normalization(vecX, vecY);
	//�e�̑��x��ݒ�
	vecX *= mBulletSpeed;
	vecY *= mBulletSpeed;
	for(int i = 0; i < mRazerNum;i++)
	{
		//�e���o��
		auto game = manager->GetBullet(enemy->GetTransform(), Tag::EnemyBullet, vecX, vecY);
		auto gameTransform = game->GetTransform();
		gameTransform->Scale.x /= 2.0f;
		gameTransform->Scale.y /= 2.0f;
		auto vecX2 = vecX * mCosAngle - vecY * mSinAngle;
		auto vecY2 = vecX * mSinAngle + vecY * mCosAngle;
		vecX = vecX2;
		vecY = vecY2;
	}
	
}

void SixWayRazerBarrage::CreateBarrage(BulletPool * pool, DXGameObject * player, DXGameObject * enemy)
{
	//�G���玩�@�ւ̃x�N�g��
	auto vecX = 0.0f;
	auto vecY = -1.0f;
	//�x�N�g���̐��K��
	Normalization(vecX, vecY);
	//�e�̑��x��ݒ�
	vecX *= mBulletSpeed;
	vecY *= mBulletSpeed;
	for (int i = 0; i < mRazerNum; i++)
	{
		//�e���o��
		auto game = pool->GetBullet(enemy->GetTransform(), Tag::EnemyBullet, vecX, vecY);
		auto gameTransform = game->GetTransform();
		gameTransform->Scale.x /= 2.0f;
		gameTransform->Scale.y /= 2.0f;
		auto vecX2 = vecX * mCosAngle - vecY * mSinAngle;
		auto vecY2 = vecX * mSinAngle + vecY * mCosAngle;
		vecX = vecX2;
		vecY = vecY2;
	}
}
