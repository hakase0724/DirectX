#include "stdafx.h"
#include "TargetPlayerBarrage.h"
#include "DXGameObject.h"
#include "BulletManager.h"
#include "BulletPool.h"

using namespace MyDirectX;
TargetPlayerBarrage::TargetPlayerBarrage()
{
	mName = BarrageName::TargetPlayer;
	mCoolTime = 30;
	mBulletSpeed = 0.02f;
	mBulletNum = 5;
	mCount = 0;
}

bool TargetPlayerBarrage::IsBarrageEnd()
{
	mCount++;
	if(mCount >= mBulletNum)
	{
		mCount = 0;
		return true;
	}
	else
	{
		return false;
	}
}

void TargetPlayerBarrage::CreateBarrage(BulletManager * manager, DXGameObject * player, DXGameObject * enemy)
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
		//�e���o��
		auto game = manager->GetBullet(enemy->GetTransform(), Tag::EnemyBullet, vecX, vecY);
		auto gameTransform = game->GetTransform();
		gameTransform->Scale.x /= 2.0f;
		gameTransform->Scale.y /= 2.0f;
	}
}

void TargetPlayerBarrage::CreateBarrage(BulletPool * pool, DXGameObject * player, DXGameObject * enemy)
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
		//�e���o��
		auto game = pool->GetBullet(enemy->GetTransform(), Tag::EnemyBullet, vecX, vecY);
		auto gameTransform = game->GetTransform();
		gameTransform->Scale.x /= 2.0f;
		gameTransform->Scale.y /= 2.0f;
	}
}
