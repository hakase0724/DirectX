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
		//����������
		virtual void Initialize(DXGameObject* gameObject);
		//�X�V����
		virtual void Update();
		virtual void OnCollisionEnter() override;
		void SetPlayer(DXGameObject* player) { mPlayer = player; }
		virtual double GetHP() { return HitPoint; }
	private:
		BulletManager* mBulletManager;
		//���t���[���o�߂�����
		int mWaitCount;
		//�e�𔭎˂���t���[���Ԋu
		const int mCoolCount = 60;
		//�̗�
		double HitPoint;
		DXGameObject* mPlayer;
		float mBulletSpeed;
		//�p�x�����W�A���ɕϊ�����W��
		float mRadianCoefficient;
		//�p�x
		float mAngle;
		BarrageBase* mBarrage;
		std::unique_ptr<BarrageManager> mBarrageManager;
		BarrageName mBarrageName;
		void ChangeBarrageName();
	};

}

