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
		virtual void SetHP(double hp) { mDefaultHitPoint = hp; }
		virtual double GetMaxHP() override { return mDefaultHitPoint; }
		virtual double GetHP() override { return mHitPoint; }
		virtual void Damage(double damage) override;
	private:
		void Bomb();
		DXInput* mDXInput;
		BulletPool* mBulletPool;
		//���������Ă���{����
		int mBombNum;
		//�ۗL�\�ȃ{���̍ő�l�@��̖I�V���[�Y��3��{�����g�����тɍő吔���㏸���ő�7�܂ő�������
		int mMaxBomb;
		//�{���g�p��
		int mUsedBombNum;
		//���ˉ\���ǂ���
		bool isCoolTime();
		//���t���[���o�߂�����
		int mWaitCount;
		//�e�𔭎˂���t���[�����o
		const int mCoolCount = 7;
		//�̗�
		double mHitPoint;
		double mDefaultHitPoint = 1.0;
		
	};
}
 

