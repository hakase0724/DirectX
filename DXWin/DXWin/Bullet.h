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
		~Bullet() {};
		//����������
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		//�X�V����
		virtual void Update() override;
		virtual void OnCollisionEnter() override;
	private:
		DXInput* mDXInput;
		DXCamera* mDXCamera;
		TRANSFORM* mTransform;
		BulletManager* mBulletManager;
	};
}

