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
		//初期化処理
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		//更新処理
		virtual void Update() override;
		virtual void OnCollisionEnter() override;
	private:
		DXInput* mDXInput;
		DXCamera* mDXCamera;
		TRANSFORM* mTransform;
		BulletManager* mBulletManager;
	};
}

