#include "stdafx.h"
#include "Player.h"

using namespace MyDirectX;

void Player::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mDXInput = mGameObject->GetDXInput();
	auto transform = mGameObject->GetTransform();
	transform->Scale.x /= 3.0f;
	transform->Scale.y /= 3.0f;
	transform->Scale.z /= 3.0f;
	mId = mGameObject->GetID();
	mGameObject->SetDefaultTransform(transform);
	mWaitCount = mCoolCount;
	mHitPoint = 1.0;
}

void Player::Initialize()
{
	mGameObject->ResetTransform();
	mWaitCount = mCoolCount;
	mHitPoint = mDefaultHitPoint;
}

void Player::Update()
{
	//毎フレームカウントを行う
	mWaitCount++;
	
	if(!isCoolTime())
	{
		//発射しない
	}
	else if (mDXInput->GetInputState(DIK_Z))
	{
		//複数発射する用テストコード
		auto bulletNum = 4;
		for(int i = 0;i < bulletNum;i++)
		{
			BULLET_SETTING_DATA data;
			data.transform = mGameObject->GetTransform();
			data.tag = PlayerBullet;
			data.xVectol = 0.0f;
			data.yVectol = 0.05f;
			data.texturePath = _T("Texture/Bullet3.png");
			data.scaleRatio = 0.3f;
			//弾を出す
			auto game = mBulletPool->GetBullet(data);
			auto gameTransform = game->GetTransform();
			//各弾同士の間隔
			auto offset = gameTransform->Scale.x;
			gameTransform->Position.x += offset * (i - (float)bulletNum / 3.0f);
		}
		mGameObject->GetDXResourceManager()->GetSEDXSound()->ResetSound();
		mGameObject->GetDXResourceManager()->GetSEDXSound()->Play();
	}	
	else if(!mDXInput->GetInputState(DIK_Z))
	{
		//発射しなかった場合は発射可能状態にしておく
		//-1しているのは次の判定では+1して判定するから
		mWaitCount = mCoolCount - 1;
		//SEをリセットしておく
		mGameObject->GetDXResourceManager()->GetSEDXSound()->Stop();
	}

	if(mDXInput->GetKeyDown(DIK_X))
	{
		Bomb();
	}

#if _DEBUG
	//エンターキーでブレークポイント
	if(mDXInput->GetKeyDown(DIK_RETURN))
	{
		mWaitCount = mCoolCount - 1;
	}
#endif

}

void Player::OnCollisionEnter()
{
	Damage(1.0);
}

void Player::Damage(double damage)
{
	mHitPoint -= damage;
	//体力がなくなったら自身のアクティブを切る
	if (mHitPoint <= 0)
	{
		mGameObject->SetEnable(false);
	}
}

void Player::Bomb()
{
	//シーンに登録されているオブジェクトを取得
	auto gameObjects = mGameObject->GetScene()->GetGameObjects();
	for (auto game : gameObjects)
	{
		//非アクティブなら無視
		if (!game->GetEnable()) continue;
		auto tag = game->GetTag();
		//自機もしくは自弾なら無視
		if (tag == PlayerTag) continue;
		if (tag == PlayerBullet) continue;
		//HPをもっているコンポーネントを取得
		auto gameHaveHP = game->GetComponent<IHP>();
		//HPがあるならダメージを与える
		if (gameHaveHP != nullptr)
		{
			gameHaveHP->Damage(10.0);
		}
		//なければアクティブを切る
		else
		{
			game->SetEnable(false);
		}
	}
}

bool Player::isCoolTime()
{
	if(mWaitCount % mCoolCount == 0)
	{
		mWaitCount = 0;
		return true;
	}
	else
	{
		return false;
	}
}
