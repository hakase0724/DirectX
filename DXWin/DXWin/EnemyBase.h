#pragma once
#include "IComponent.h"
#include "DXManager.h"
#include "Bullet.h"
#include "Colliders.h"
#include "DXGameObject.h"
#include "AllDirectionSync.h"
#include "BarrageBase.h"
#include "BarrageManager.h"
#include "BulletPool.h"

namespace MyDirectX
{
	class EnemyBase :public Component,public IHP
	{
	public:
		EnemyBase() {};
		virtual ~EnemyBase() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override {};
		virtual void Update() override {};
		virtual void OnCollisionEnter() override;
		//セッター
		void SetBulletPool(BulletPool* pool) { mBulletPool = pool; }
		void SetPlayer(DXGameObject* player) { mPlayer = player; }
		void SetBarrageManager(BarrageManager* manager) { mBarrageManager = manager; }
		//体力のインターフェース
		virtual void SetHP(double hp) override { mDefaultHitPoint = hp; }
		virtual double GetMaxHP() override { return mDefaultHitPoint; }
		virtual double GetHP() override { return mHitPoint; }
		virtual void Damage(double damage) override;
	protected:
		//弾のオブジェクトプール
		BulletPool* mBulletPool;
		//何フレーム経過したか
		int mWaitCount;
		//弾を発射するフレーム間隔
		int mCoolCount = 60;
		//体力
		double mHitPoint = 1.0;
		//初期体力
		double mDefaultHitPoint = 1.0;
		//プレイヤー
		DXGameObject* mPlayer;
		//今セットされている弾幕
		BarrageBase* mBarrage;
		//弾幕管理クラス
		BarrageManager* mBarrageManager;
		//弾幕識別に使用
		BarrageName mBarrageName;
		//発射数
		int mShotCount;
		//弾幕切り替え
		virtual void ChangeBarrageName() {};
		//弾幕終了判定
		virtual bool IsBarrageEnd();
	};
}


