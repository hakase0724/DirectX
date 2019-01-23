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
	BULLET_SETTING_DATA data;
	data.transform = *enemy->GetTransform();
	data.transform.Position.z = -0.01f;
	data.transform.Scale.x /= 2.0f;
	data.transform.Scale.y /= 2.0f;
	data.tag = EnemyBullet;
	data.texturePath = _T("Texture/BulletL2.png");
	data.ScaleRatio(0.3f);
	for (int i = 0; i < mBulletNum; i++)
	{
		auto vecX2 = vecX * mCosAngle - vecY * mSinAngle;
		auto vecY2 = vecX * mSinAngle + vecY * mCosAngle;
		vecX = vecX2;
		vecY = vecY2;
		data.xVectol = vecX;
		data.yVectol = vecY;
		//弾を出す
		pool->GetBullet(data);
	}
}
