#include "stdafx.h"
#include "AllDirectionSync.h"
#include "DXGameObject.h"
#include "BulletPool.h"

using namespace MyDirectX;

AllDirectionSync::AllDirectionSync()
{
	mName = BarrageName::AllDirectionsSync;
	mCoolTime = 60;
	mBulletSpeed = 0.01f;
	mAngle = 10.0f;
	mBulletNum = 36;
	mShotNum = 1;
	auto radian = ToRadian(mAngle);
	mCosAngle = cos(radian);
	mSinAngle = sin(radian);
	mCount = 0;
}

void AllDirectionSync::CreateBarrage(BulletPool * pool, DXGameObject * player, DXGameObject * enemy)
{
	//�����Ƒ���̍��W����ڕW�֌������x�N�g���쐬
	auto target = player->GetTransform()->Position;
	auto myPos = enemy->GetTransform()->Position;
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
	//�������˂���p�e�X�g�R�[�h
	for (int i = 0; i < mBulletNum; i++)
	{
		auto vecX2 = vecX * mCosAngle - vecY * mSinAngle;
		auto vecY2 = vecX * mSinAngle + vecY * mCosAngle;
		vecX = vecX2;
		vecY = vecY2;
		//�e���o��
		auto game = pool->GetBullet(enemy->GetTransform(), Tag::EnemyBullet, vecX, vecY);
		auto gameTransform = game->GetTransform();
		gameTransform->Scale.x /= 2.0f;
		gameTransform->Scale.y /= 2.0f;
	}
}
