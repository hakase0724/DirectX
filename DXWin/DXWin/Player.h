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
	class DXGameObjectManager;

	class Player :public Component
	{
	public:
		Player() {};
		~Player() {};
		//����������
		virtual void Initialize(DXGameObject* gameObject);
		//�X�V����
		virtual void Update();
	private:
		DXInput* mDXInput;
		BulletManager* mBulletManager;
		//���ˉ\���ǂ���
		bool isCoolTime();
		//���t���[���o�߂�����
		int mWaitCount;
		//�e�𔭎˂���t���[�����o
		const int mCoolCount = 7;
	};
}
 

