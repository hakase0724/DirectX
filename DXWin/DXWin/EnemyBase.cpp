#include "stdafx.h"
#include "EnemyBase.h"
#include "PlayScene.h"

using namespace MyDirectX;

void EnemyBase::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = mGameObject->GetID();
	mWaitCount = mCoolCount;
}

bool EnemyBase::IsBarrageEnd()
{
	mShotCount++;
	if(mShotCount >= mBarrage->GetShotNum())
	{
		mShotCount = 0;
		return true;
	}
	else return false;
}

void EnemyBase::OnCollisionEnter2D(Collider2D* col)
{
	//当たったら1ダメージ受ける
	Damage(1.0);
}

void EnemyBase::OnDisable()
{
	auto scene = mGameObject->GetScene();
	auto playScene = dynamic_cast<PlayScene*>(scene);
	playScene->AddScore(mScore);
	auto transform = *mGameObject->GetTransform();
	playScene->CreateExplosionEffect(transform.Position);
	switch (mDropItemType)
	{
	case PowerUp:
		playScene->CreatePowerUp(transform.Position);
		break;
	case BombItem:
		playScene->CreateBomb(transform.Position);
		break;
	default:
		break;
	}
}

void EnemyBase::Damage(double damage)
{
	mHitPoint -= damage;
	//体力がなくなったら自身のアクティブを切る
	if (mHitPoint <= 0)
	{
		mGameObject->SetEnable(false);
	}
}
