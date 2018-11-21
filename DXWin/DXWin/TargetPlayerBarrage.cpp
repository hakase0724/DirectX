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
		//弾を出す
		auto game = manager->GetBullet(enemy->GetTransform(), Tag::EnemyBullet, vecX, vecY);
		auto gameTransform = game->GetTransform();
		gameTransform->Scale.x /= 2.0f;
		gameTransform->Scale.y /= 2.0f;
	}
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
	//複数発射する用テストコード
	for (int i = 0; i < mBulletNum; i++)
	{
		//弾を出す
		auto game = pool->GetBullet(enemy->GetTransform(), Tag::EnemyBullet, vecX, vecY);
		auto gameTransform = game->GetTransform();
		gameTransform->Scale.x /= 2.0f;
		gameTransform->Scale.y /= 2.0f;
	}
}
