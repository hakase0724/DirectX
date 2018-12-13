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
		//�Z�b�^�[
		void SetBulletPool(BulletPool* pool) { mBulletPool = pool; }
		void SetPlayer(DXGameObject* player) { mPlayer = player; }
		void SetBarrageManager(BarrageManager* manager) { mBarrageManager = manager; }
		//�̗͂̃C���^�[�t�F�[�X
		virtual void SetHP(double hp) override { mDefaultHitPoint = hp; }
		virtual double GetMaxHP() override { return mDefaultHitPoint; }
		virtual double GetHP() override { return mHitPoint; }
		virtual void Damage(double damage) override;
	protected:
		//�e�̃I�u�W�F�N�g�v�[��
		BulletPool* mBulletPool;
		//���t���[���o�߂�����
		int mWaitCount;
		//�e�𔭎˂���t���[���Ԋu
		int mCoolCount = 60;
		//�̗�
		double mHitPoint = 1.0;
		//�����̗�
		double mDefaultHitPoint = 1.0;
		//�v���C���[
		DXGameObject* mPlayer;
		//���Z�b�g����Ă���e��
		BarrageBase* mBarrage;
		//�e���Ǘ��N���X
		BarrageManager* mBarrageManager;
		//�e�����ʂɎg�p
		BarrageName mBarrageName;
		//���ː�
		int mShotCount;
		//�e���؂�ւ�
		virtual void ChangeBarrageName() {};
		//�e���I������
		virtual bool IsBarrageEnd();
	};
}


