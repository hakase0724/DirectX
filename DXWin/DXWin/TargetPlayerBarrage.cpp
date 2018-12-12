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
	//自分と相手の座標から目標へ向かうベクトル作成
	auto target = player->GetTransform()->Position;
	auto myPos = enemy->GetTransform()->Position;
	//敵から自機へのベクトル
	auto vecX = (target.x - myPos.x);
	auto vecY = (target.y - myPos.y);
	//ベクトルの正規化
	auto len = sqrtf(vecX * vecX + vecY * vecY);
	vecX /= len;
	vecY /= len;
	//弾の速度を設定
	vecX *= mBulletSpeed;
	vecY *= mBulletSpeed;
	BULLET_SETTING_DATA data;
	data.transform = enemy->GetTransform();
	data.tag = EnemyBullet;
	data.xVectol = vecX;
	data.yVectol = vecY;
	data.texturePath = _T("Texture/BulletL2.png");
	//弾を出す
	auto game = pool->GetBullet(data);
	auto gameTransform = game->GetTransform();
	gameTransform->Scale.x /= 2.0f;
	gameTransform->Scale.y /= 2.0f;
}
