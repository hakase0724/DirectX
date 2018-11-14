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
		//����������
		virtual void Initialize(DXGameObject* gameObject);
		//�X�V����
		virtual void Update();
		virtual void OnCollisionEnter() override;
		void SetPlayer(DXGameObject* player) { mPlayer = player; }
	private:
		BulletManager* mBulletManager;
		//���ˉ\���ǂ���
		bool isCoolTime();
		//���t���[���o�߂�����
		int mWaitCount;
		//�e�𔭎˂���t���[�����o
		const int mCoolCount = 80;
		//�̗�
		int HitPoint;
		DXGameObject* mPlayer;
		float mBulletSpeed;
		//�p�x�����W�A���ɕϊ�����W��
		float mRadianCoefficient;
		//�p�x
		float mAngle;
	};

}

