#pragma once
#include "DXManager.h"
#include "IComponent.h"
#include "DXGameObject.h"

namespace MyDirectX
{
	class Roller :public Component
	{
	public:
		Roller() {};
		~Roller() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Update() override;
	private:
		DXInput* mDXInput;
	};
}


