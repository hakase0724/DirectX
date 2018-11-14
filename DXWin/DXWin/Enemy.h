#pragma once
#include "IComponent.h"
#include "DXManager.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "Colliders.h"
#include "DXGameObject.h"

namespace MyDirectX
{
	class Enemy :public Component
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
	private:
		BulletManager* mBulletManager;
		//発射可能かどうか
		bool isCoolTime();
		//何フレーム経過したか
		int mWaitCount;
		//弾を発射するフレーム感覚
		const int mCoolCount = 80;
		//体力
		int HitPoint;
		DXGameObject* mPlayer;
		float mBulletSpeed;
		//角度をラジアンに変換する係数
		float mRadianCoefficient;
		//角度
		float mAngle;
	};

}

