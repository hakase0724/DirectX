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
	Damage(1.0);
}

void EnemyBase::OnDisable()
{
	auto scene = mGameObject->GetScene();
	auto playScene = dynamic_cast<PlayScene*>(scene);
	playScene->AddScore(mScore);
	auto transform = *mGameObject->GetTransform();
	transform.Scale.x /= 2;
	transform.Scale.y /= 2;
	transform.Scale.z /= 2;
	switch (mDropItemType)
	{
	case PowerUp:
		playScene->CreatePowerUp(transform);
		break;
	case BombItem:
		playScene->CreateBomb(transform);
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
