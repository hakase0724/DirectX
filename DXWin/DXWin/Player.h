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
		virtual void OnCollisionEnter() override;
		virtual void SetHP(double hp) {};
		virtual double GetHP() { return HitPoint; }
	private:
		DXInput* mDXInput;
		BulletPool* mBulletPool;
		//発射可能かどうか
		bool isCoolTime();
		//何フレーム経過したか
		int mWaitCount;
		//弾を発射するフレーム感覚
		const int mCoolCount = 7;
		//体力
		double HitPoint;
		
	};
}
 

