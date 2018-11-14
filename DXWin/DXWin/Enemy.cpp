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
	//毎フレームカウントを行う
	mWaitCount++;

	if (isCoolTime())
	{
		//自分と相手の座標から目標へ向かうベクトル作成
		auto target = mPlayer->GetTransform()->Position;
		auto myPos = mGameObject->GetTransform()->Position;
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
		//ベクトルをずらす
		auto mcos = cos(mAngle * mRadianCoefficient);
		auto msin = sin(mAngle * mRadianCoefficient);
		auto vecX2 = vecX * mcos - vecY * msin;
		auto vecY2 = vecX * msin + vecY * mcos;
		vecX = vecX2;
		vecY = vecY2;
		//複数発射する用テストコード
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
	//体力がなくなったら自身のアクティブを切る
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
