#pragma once
#include "IComponent.h"
#include "DXCamera.h"

namespace MyDirectX
{
	class ItemMover :public Component
	{
	public:
		ItemMover() {};
		~ItemMover() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Update() override;
		void SetSpeed(float speed) { mMoveSpeed = speed; }
	private:
		float mMoveSpeed;
		DXCamera* mDXCamera;
	};
}


