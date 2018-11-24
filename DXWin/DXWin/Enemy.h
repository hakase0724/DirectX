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
		//����������
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		void SetBulletPool(BulletPool* pool) { mBulletPool = pool; }
		//�X�V����
		virtual void Update();
		virtual void OnCollisionEnter() override;
		void SetPlayer(DXGameObject* player) { mPlayer = player; }
		virtual void SetHP(double hp) {};
		virtual double GetHP() { return HitPoint; }
	private:
		//�e�̃I�u�W�F�N�g�v�[��
		BulletPool* mBulletPool;
		//���t���[���o�߂�����
		int mWaitCount;
		//�e�𔭎˂���t���[���Ԋu
		const int mCoolCount = 60;
		//�̗�
		double HitPoint;
		//�v���C���[
		DXGameObject* mPlayer;
		//���Z�b�g����Ă���e��
		BarrageBase* mBarrage;
		//�e���Ǘ��N���X
		std::unique_ptr<BarrageManager> mBarrageManager;
		//�e�����ʂɎg�p
		BarrageName mBarrageName;
		//�e���؂�ւ�
		void ChangeBarrageName();
	};

}

