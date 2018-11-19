#pragma once
#include "IComponent.h"
#include "DXManager.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "Colliders.h"
#include "DXGameObject.h"
#include "AllDirectionSync.h"
#include "BarrageBase.h"
#include "BarrageManager.h"


namespace MyDirectX
{
	class Enemy :public Component,public IHP
	{
	public:
		Enemy() {};
		~Enemy() {};
		//初期化処理
		virtual void Initialize(DXGameObject* gameObject);
		//更新処理
		virtual void Update();
		virtual void OnCollisionEnter() override;
		void SetPlayer(DXGameObject* player) { mPlayer = player; }
		virtual double GetHP() { return HitPoint; }
	private:
		BulletManager* mBulletManager;
		//何フレーム経過したか
		int mWaitCount;
		//弾を発射するフレーム間隔
		const int mCoolCount = 60;
		//体力
		double HitPoint;
		DXGameObject* mPlayer;
		float mBulletSpeed;
		//角度をラジアンに変換する係数
		float mRadianCoefficient;
		//角度
		float mAngle;
		BarrageBase* mBarrage;
		std::unique_ptr<BarrageManager> mBarrageManager;
		BarrageName mBarrageName;
		void ChangeBarrageName();
	};

}

