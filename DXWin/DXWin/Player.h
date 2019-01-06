#pragma once
#include "DXManager.h"
#include "IComponent.h"
#include "DXGameObject.h"
#include "Colliders.h"
#include <string>
#include "Bullet.h"
#include "BulletPool.h"

namespace MyDirectX
{
	class Player :public Component,public IHP
	{
	public:
		Player() {};
		~Player() {};
		//初期化処理
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		void SetBulletPool(BulletPool* pool) { mBulletPool = pool; }
		//更新処理
		virtual void Update() override;
		virtual void OnCollisionEnter2D(Collider2D* col) override;
		virtual void SetHP(double hp) { mDefaultHitPoint = hp; }
		virtual double GetMaxHP() override { return mDefaultHitPoint; }
		virtual double GetHP() override { return mHitPoint; }
		virtual void Damage(double damage) override;
		bool IsShot() const { return mIsShot; };
		bool IsLongPush() const { return mIsLongPush; };
		//ボムを追加
		void AddBomb() 
		{
			mBombNum++;
			if (mBombNum >= mMaxBombNum) mBombNum = mMaxBombNum;
		}
		//パワーアップ
		void PowerUp()
		{
			mPower++;
			if (mPower >= mMaxPower) mPower = mMaxPower;
		}
	private:
		void Bomb();
		DXInput* mDXInput;
		BulletPool* mBulletPool;
		//今所持しているボム数
		int mBombNum;
		//保有可能なボムの最大値　首領蜂シリーズは3回ボムを使うたびに最大数が上昇し最大7個まで増加する
		int mMaxBombNum;
		//ボム使用回数
		int mUsedBombNum;
		//発射可能かどうか
		bool CanShot();
		//何フレーム経過したか
		int mWaitCount;
		//弾を発射するフレーム感覚
		const int mCoolCount = 7;
		//体力
		double mHitPoint;
		double mDefaultHitPoint = 1.0;
		//パワー
		int mPower;
		//最大パワー
		int mMaxPower;
		//長押し判定フラグ
		bool mIsLongPush;
		//発射しているか
		bool mIsShot;
	};
}
 

