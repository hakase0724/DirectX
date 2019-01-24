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
		//�e���؂�ւ�
		virtual void ChangeBarrageName() override;
	private:
		float GetRangeRand(float minValue,float maxValue);
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
		//�������锚�j�G�t�F�N�g��
		int mExplosionNum = 50;
		//�����������j�G�t�F�N�g��
		int mCreateExplosionNum = 0;
		DXGameObject* mLastExplosionEffect = nullptr;
	};
}


