#pragma once
#include "EnemyBase.h"
#include "Colliders.h"
#include "MyEnums.h"

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
	protected:
		//�e���؂�ւ�
		virtual void ChangeBarrageName() override;
	private:
		DirectX::XMFLOAT3 mBattleStartPos;
		//�ړ����x
		const float MOVE_SPPED = 0.01f;
		//���e�덷
		const float EPSILON = 0.000001f;
		float mMoveVecX;
		float mMoveVecY;
		SquareCollider2D* mCollider;
		BossState mState;
		TRANSFORM* mTransform;
	};
}


