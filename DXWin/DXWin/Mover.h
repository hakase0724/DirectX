#pragma once
#include "DXManager.h"
#include "IComponent.h"
#include "DXGameObject.h"

namespace MyDirectX 
{
	class Mover :public Component
	{
	public:
		Mover() {};
		~Mover() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Update() override;
	private:
		DXInput* mDXInput;
		//ˆÚ“®‘¬“x
		float mMoveSpeed = 0.02f;
	};
}



