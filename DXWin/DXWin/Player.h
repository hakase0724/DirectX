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
		//����������
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		void SetBulletPool(BulletPool* pool) { mBulletPool = pool; }
		//�X�V����
		virtual void Update() override;
		virtual void OnCollisionEnter() override;
		virtual void SetHP(double hp) {};
		virtual double GetHP() { return HitPoint; }
	private:
		DXInput* mDXInput;
		BulletPool* mBulletPool;
		//���ˉ\���ǂ���
		bool isCoolTime();
		//���t���[���o�߂�����
		int mWaitCount;
		//�e�𔭎˂���t���[�����o
		const int mCoolCount = 7;
		//�̗�
		double HitPoint;
		
	};
}
 

