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
	class Enemy :public Component,public IHP
	{
	public:
		Enemy() {};
		~Enemy() {};
		//初期化処理
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		void SetBulletPool(BulletPool* pool) { mBulletPool = pool; }
		//更新処理
		virtual void Update();
		virtual void OnCollisionEnter() override;
		void SetPlayer(DXGameObject* player) { mPlayer = player; }
		virtual void SetHP(double hp) {};
		virtual double GetHP() { return HitPoint; }
	private:
		//弾のオブジェクトプール
		BulletPool* mBulletPool;
		//何フレーム経過したか
		int mWaitCount;
		//弾を発射するフレーム間隔
		const int mCoolCount = 60;
		//体力
		double HitPoint;
		//プレイヤー
		DXGameObject* mPlayer;
		//今セットされている弾幕
		BarrageBase* mBarrage;
		//弾幕管理クラス
		std::unique_ptr<BarrageManager> mBarrageManager;
		//弾幕識別に使用
		BarrageName mBarrageName;
		//弾幕切り替え
		void ChangeBarrageName();
	};

}

