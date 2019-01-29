#include "stdafx.h"
#include "BossEnemy.h"
#include <random>

using namespace MyDirectX;

void BossEnemy::Initialize()
{
	mCollider->SetEnable(false);
	mState = Entry;
	mGameObject->ResetTransform();
	mWaitCount = mCoolCount;
	mHitPoint = mDefaultHitPoint;
	mBarrageName = BarrageName::AllDirectionsSync;
	mBarrage = mBarrageManager->GetBarrage(mBarrageName);
	mBarrage->Init();
	mTransform = mGameObject->GetTransform();
	mMoveVecX = mBattleStartPos.x - mTransform->Position.x;
	mMoveVecY = mBattleStartPos.y - mTransform->Position.y;
	//ベクトルの正規化
	auto len = sqrtf(mMoveVecX * mMoveVecX + mMoveVecY * mMoveVecY);
	mMoveVecX /= len;
	mMoveVecY /= len;
	mMoveVecX *= MOVE_SPPED;
	mMoveVecY *= MOVE_SPPED;
	//演出で使用するために0で初期化
	mHitPoint = 0;
	//ボスを倒したときのスコア
	mScore = 100.0;
	mDropItemType = NoDrop;
	mCreateExplosionNum = 0;
	mLastExplosionEffect = nullptr;
	//レンダラーをオンにする
	auto renderer = mGameObject->GetComponent<TextureRenderer>();
	renderer->SetEnable(true);
}

void BossEnemy::Update()
{
	switch (mState)
	{
	//ボス登場ステートの処理
	case Entry:
		//ボスの体力バーが動く演出のため体力を増加させる
		if(mHitPoint + mDefaultHitPoint / 100.0 <= mDefaultHitPoint)
		{
			mHitPoint += mDefaultHitPoint / 100.0;
		}
		else if(mHitPoint + mDefaultHitPoint / 100.0 > mDefaultHitPoint)
		{
			mHitPoint = mDefaultHitPoint;
		}
		//設定した開始位置に到達したら弾幕展開を開始する
		if(abs(mTransform->Position.x - mBattleStartPos.x) <= EPSILON)
		{
			if(abs(mTransform->Position.y - mBattleStartPos.y) <= EPSILON)
			{
				mCollider->SetEnable(true);
				mState = Battle;
				break;
			}
		}
		//画面外から開始位置へ移動
		mTransform->Position.x += mMoveVecX;
		mTransform->Position.y += mMoveVecY;
		break;
	case Battle:
		//毎フレームカウントを行う
		mWaitCount++;
		//弾幕の発射間隔ごとに
		if (mBarrage->IsCoolTime(mWaitCount))
		{
			mWaitCount = 0;
			//弾幕を生成する
			mBarrage->CreateBarrage(mBulletPool, mPlayer, mGameObject);
			if (IsBarrageEnd())
			{
				ChangeBarrageName();
				mBarrage = mBarrageManager->GetBarrage(mBarrageName);
			}
		}
		break;
	case BossDie:
		mWaitCount++;
		//とりあえず2フレごとにエフェクトを出してみる
		if(mWaitCount % 2 == 0)
		{
			mWaitCount = 0;
			auto transform = *mGameObject->GetTransform();
			mCreateExplosionNum++;
			//ボスとかぶって見にくいから少しカメラに近づける
			transform.Position.z -= 0.1f;
			if(mCreateExplosionNum < mExplosionNum)
			{
				//爆破生成場所をランダムでズラす
				transform.Position.x += GetRangeRand(-0.5f, 0.5f);
				transform.Position.y += GetRangeRand(-0.5f, 0.5f);
				mPlayScene->CreateExplosionEffect(transform.Position);
			}
			else if(mCreateExplosionNum == mExplosionNum)
			{
				mLastExplosionEffect = mPlayScene->CreateExplosionEffect(transform.Position, transform.Scale);
				//レンダラーをオフにする
				auto renderer = mGameObject->GetComponent<TextureRenderer>();
				renderer->SetEnable(false);
			}
		}
		//最終爆破エフェクトが生成されていなければここで終わり
		if (mLastExplosionEffect == nullptr) break;
		//最終爆破エフェクトが終了したらボスの死亡フラグを立てる
		if (!mLastExplosionEffect->GetEnable())
		{
			mPlayScene->BossDie();
			mGameObject->SetEnable(false);
		}
		break;
	default:
		break;
	}
}

void BossEnemy::Damage(double damage)
{
	mHitPoint -= damage;
	if (mHitPoint <= 0)
	{
		mState = BossDie;
		//シーンに登録されているオブジェクトを取得
		auto gameObjects = mGameObject->GetScene()->GetGameObjects();
		for (auto &game : *gameObjects)
		{
			//非アクティブなら無視
			if (!game->GetEnable()) continue;
			auto tag = game->GetTag();
			//敵弾以外無視
			if (tag != EnemyBullet) continue;
			mPlayScene->CreateScoreItem(game->GetTransform()->Position);
			game->SetEnable(false);
		}
		mCollider->SetEnable(false);
	}
}

void BossEnemy::ChangeBarrageName()
{
	switch (mBarrageName)
	{
	case BarrageName::AllDirectionsSync:
		mBarrageName = BarrageName::TargetPlayer;
		break;
	case BarrageName::TargetPlayer:
		mBarrageName = BarrageName::SixWayRazer;
		break;
	case BarrageName::SixWayRazer:
		mBarrageName = BarrageName::AllDirectionsSync;
		break;
	default:
		break;
	}
}

float BossEnemy::GetRangeRand(float minValue, float maxValue)
{
	//シード値乱数生成器
	std::random_device rnd;
	//メルセンヌ・ツイスタ方を使って乱数を作る
	std::mt19937_64 mt64(rnd());
	//範囲内の離散分布を作る
	std::uniform_real_distribution<float> genRandFloat(minValue, maxValue);
	//分布の中から生成した乱数を使って1つだけ値を取り出す
	return genRandFloat(mt64);
}
