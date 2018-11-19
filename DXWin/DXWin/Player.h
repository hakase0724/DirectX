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
	class Player :public Component,public IHP
	{
	public:
		Player() {};
		~Player() {};
		//����������
		virtual void Initialize(DXGameObject* gameObject);
		//�X�V����
		virtual void Update();
		virtual void OnCollisionEnter() override;
		virtual double GetHP() { return HitPoint; }
	private:
		DXInput* mDXInput;
		BulletManager* mBulletManager;
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
 

