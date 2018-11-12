#pragma once
#include "DXManager.h"
#include "IComponent.h"
#include "DXGameObject.h"
#include "Colliders.h"
#include <string>
#include "Bullet.h"
#include "BulletManager.h"

namespace MyDirectX
{
	class DXGameObjectManager;

	class Player :public Component
	{
	public:
		Player() {};
		~Player() {};
		//初期化処理
		virtual void Initialize(DXGameObject* gameObject);
		//更新処理
		virtual void Update();
	private:
		DXInput* mDXInput;
		BulletManager* mBulletManager;
		//発射可能かどうか
		bool isCoolTime();
		//何フレーム経過したか
		int mWaitCount;
		//弾を発射するフレーム感覚
		const int mCoolCount = 7;
	};
}
 

