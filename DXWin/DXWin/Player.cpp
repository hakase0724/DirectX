#include "stdafx.h"
#include "Player.h"
#include "Mover.h"
#include <math.h>
#include "DXAnimation.h"

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
	mMaxBombNum = 3;
	mPower = 1;
	mMaxPower = 4;
	mIsLongPush = false;
	//移動コンポーネント取得
	if (mMover == nullptr) mMover = mGameObject->GetComponent<Mover>();
	mRazerWidth = 0.8f;
}

void Player::Update()
{
#if _DEBUG
	//エンターキーでブレークポイント
	if (mDXInput->GetKeyDown(DIK_RETURN))
	{
		mWaitCount = mCoolCount - 1;
	}
#endif

	//毎フレームカウントを行う
	mWaitCount++;
	//打てるフレームか
	mIsShot = false;

	//ボム
	if (mDXInput->GetKeyDown(DIK_X))
	{
		Bomb();
	}

	//ショットボタンが押されているか
	if (mDXInput->GetInputState(DIK_Z))
	{
		//発射判定
		mIsShot = CanShot();
		//長押し判定
		mIsLongPush = IsMyLongPush();
		if(mIsLongPush)
		{
			mMover->SetSpeed(0.01f);
		}
		else
		{
			mMover->SetSpeed(0.02f);
		}
	}
	else
	{
		mMover->SetSpeed(0.02f);
		//押されていないなら長押しされていない
		mIsLongPush = false;
		//発射しなかった場合は発射可能状態にしておく
		//-1しているのは次の判定では+1して判定するから
		mWaitCount = mCoolCount - 1;
		//SEをリセットしておく
		mGameObject->GetDXResourceManager()->GetSEDXSound()->Stop();
	}

	if (mIsShot) Shot();
}

void Player::OnCollisionEnter2D(Collider2D* col)
{
	auto game = col->GetGameObject();
	//アイテムとの衝突ではダメージを受けない
	if (game->GetTag() == Item) return;
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
	//ボムを持っていなければ何もしない
	if (mBombNum <= 0) return;
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
	mUsedBombNum++;
	//使用回数が最大所有数を超えたら最大所有数を更新
	if (mUsedBombNum >= mMaxBombNum)
	{
		mUsedBombNum = 0;
		mMaxBombNum++;
	}
	mBombNum--;
}

void Player::Shot()
{

	//長押ししているか
	if (mIsLongPush)
	{
		ShotRazer();	
	}
	//長押ししていない
	else
	{
		ShotBullet();
	}
	
	mGameObject->GetDXResourceManager()->GetSEDXSound()->ResetSound();
	mGameObject->GetDXResourceManager()->GetSEDXSound()->Play();
}

void Player::ShotBullet()
{
	mCoolCount = BULLET_COOL_COUNT;
	//弾データ
	BULLET_SETTING_DATA data;
	data.transform = *mGameObject->GetTransform();
	data.tag = PlayerBullet;
	data.xVectol = 0.0f;
	data.yVectol = 0.05f;
	data.ScaleRatio(0.3f);
	// 弾画像
	data.texturePath = _T("Texture/Bullet3.png");
	//弾を打つ
	for (int i = 0; i < mPower; i++)
	{
		//弾を出す
		auto game = mBulletPool->GetBullet(data);
		auto gameTransform = game->GetTransform();
		//各弾同士の間隔
		auto offset = gameTransform->Scale.x;
		//弾同士のオフセット計算
		gameTransform->Position.x += offset * (i - (float)mPower / 3.0f);
	}
}

void Player::ShotRazer()
{
	mCoolCount = RAZER_COOL_COUNT;
	mRazerWidth += mAddValue;
	//弾データ
	BULLET_SETTING_DATA data;
	data.pTransform = mGameObject->GetTransform();
	data.transform = *mGameObject->GetTransform();
	data.transform.Position.y += 0.3f;
	data.tag = PlayerBullet;
	data.xVectol = 0.0f;
	data.yVectol = 0.05f;
	data.isXFixed = true;
	//横幅を動かせばレーザー打ってるぽくならないかな・・？
	if (mRazerWidth < 0.8f) mAddValue = 0.01f;
	if (mRazerWidth > 1.0f) mAddValue = -0.01f;
	//if (mRazerWidth < 0.8f || mRazerWidth > 1.0f) mAddValue *= -1.0f;
	data.scaleXRatio = mRazerWidth;
	// 弾画像
	data.texturePath = _T("Texture/TestRazer5.png");
	//弾を打つ
	for (int i = 0; i < mPower; i++)
	{
		//弾を出す
		mBulletPool->GetBullet(data);
	}
}

bool Player::IsMyLongPush()
{
	//既に長押し判定済みなら判定しない
	if (mIsLongPush) return true;
	//押し始めのフレームか
	if (mDXInput->GetKeyDown(DIK_Z))
	{
		//カウントリセット
		mPushFrame = 0;
		return false;
	}
	else
	{
		//カウントアップ
		mPushFrame++;
		//長押し判定フレーム数より長い間押してたら
		if(mPushFrame > mJudgeLongPushFrame)
		{
			//カウントリセット
			mPushFrame = 0;
			return true;
		}
	}
	//押されていない
	return false;
}

bool Player::CanShot()
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
