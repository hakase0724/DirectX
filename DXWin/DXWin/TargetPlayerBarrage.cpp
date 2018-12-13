#include "stdafx.h"
#include "TargetPlayerBarrage.h"
#include "DXGameObject.h"
#include "BulletPool.h"

using namespace MyDirectX;
TargetPlayerBarrage::TargetPlayerBarrage()
{
	mName = BarrageName::TargetPlayer;
	mCoolTime = 30;
	mBulletSpeed = 0.02f;
	mShotNum = 5;
	mCount = 0;
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
	//�e�f�[�^
	BULLET_SETTING_DATA data;
	data.transform = enemy->GetTransform();
	data.tag = EnemyBullet;
	data.xVectol = vecX;
	data.yVectol = vecY;
	data.texturePath = _T("Texture/BulletL2.png");
	data.scaleRatio = 0.15f;
	//�f�[�^��n���e���󂯎��
	pool->GetBullet(data);
}
