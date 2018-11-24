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
	//複数発射する用テストコード
	for (int i = 0; i < mBulletNum; i++)
	{
		auto vecX2 = vecX * mCosAngle - vecY * mSinAngle;
		auto vecY2 = vecX * mSinAngle + vecY * mCosAngle;
		vecX = vecX2;
		vecY = vecY2;
		//弾を出す
		auto game = pool->GetBullet(enemy->GetTransform(), Tag::EnemyBullet, vecX, vecY);
		auto gameTransform = game->GetTransform();
		gameTransform->Scale.x /= 2.0f;
		gameTransform->Scale.y /= 2.0f;
	}
}
