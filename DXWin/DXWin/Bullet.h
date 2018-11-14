#pragma once
#include "IComponent.h"
#include "DXGameObject.h"

namespace MyDirectX
{
	class BulletManager;

	class Bullet :public Component
	{
	public:
		Bullet() {};
		~Bullet() { delete mMoveVectol; };
		//����������
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		//�x�N�g���ݒ�
		void SetVectol(float x, float y)
		{ 
			if(mMoveVectol == nullptr)
			{
				mMoveVectol = new Vec2(x, y);
			}
			else
			{
				mMoveVectol->x = x;
				mMoveVectol->y = y;
			}
		}
		//�X�V����1
		virtual void Update() override;
		virtual void OnCollisionEnter() override;
	private:
		DXInput* mDXInput;
		DXCamera* mDXCamera;
		TRANSFORM* mTransform;
		BulletManager* mBulletManager;
		Vec2* mMoveVectol;
	};
}

