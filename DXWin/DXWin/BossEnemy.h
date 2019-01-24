#pragma once
#include "EnemyBase.h"
#include "Colliders.h"
#include "MyEnums.h"
#include "PlayScene.h"

namespace MyDirectX
{
	class BossEnemy :public EnemyBase
	{
	public:
		BossEnemy() {};
		~BossEnemy() {};
		virtual void Initialize(DXGameObject* gameObject) override { EnemyBase::Initialize(gameObject); }
		virtual void Initialize() override;
		virtual void Update() override;
		void SetCollider(SquareCollider2D* col) { mCollider = col; }
		void SetBattleStartPos(DirectX::XMFLOAT3 pos) { mBattleStartPos = pos; }
		virtual void Damage(double damage) override;
	protected:
		//弾幕切り替え
		virtual void ChangeBarrageName() override;
	private:
		float GetRangeRand(float minValue,float maxValue);
		DirectX::XMFLOAT3 mBattleStartPos;
		//移動速度
		const float MOVE_SPPED = 0.01f;
		//許容誤差
		const float EPSILON = 0.000001f;
		float mMoveVecX;
		float mMoveVecY;
		SquareCollider2D* mCollider;
		BossState mState;
		TRANSFORM* mTransform;
		//生成する爆破エフェクト数
		int mExplosionNum = 50;
		//生成した爆破エフェクト数
		int mCreateExplosionNum = 0;
		DXGameObject* mLastExplosionEffect = nullptr;
	};
}


