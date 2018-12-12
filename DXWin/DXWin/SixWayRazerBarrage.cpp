#include "stdafx.h"
#include "SixWayRazerBarrage.h"
#include "DXGameObject.h"
#include "BulletPool.h"

using namespace MyDirectX;
SixWayRazerBarrage::SixWayRazerBarrage()
{
	mName = BarrageName::SixWayRazer;
	mCoolTime = 10;
	mBulletSpeed = 0.02f;
	mBulletNum = 6;
	mShotNum = 10;
	mAngle = 360.0f / mBulletNum;
	auto radian = ToRadian(mAngle);
	mCosAngle = cos(radian);
	mSinAngle = sin(radian);
	mCount = 0;
}

void SixWayRazerBarrage::CreateBarrage(BulletPool * pool, DXGameObject * player, DXGameObject * enemy)
{
	//敵から自機へのベクトル
	auto vecX = 0.0f;
	auto vecY = -1.0f;
	//ベクトルの正規化
	Normalization(vecX, vecY);
	//弾の速度を設定
	vecX *= mBulletSpeed;
	vecY *= mBulletSpeed;
	for (int i = 0; i < mBulletNum; i++)
	{
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
		auto vecX2 = vecX * mCosAngle - vecY * mSinAngle;
		auto vecY2 = vecX * mSinAngle + vecY * mCosAngle;
		vecX = vecX2;
		vecY = vecY2;
	}
}
