#pragma once
#include "IComponent.h"

namespace MyDirectX
{
	class PowerUpItem :public Component
	{
	public:
		PowerUpItem() {};
		~PowerUpItem() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void OnCollisionEnter2D(Collider2D* col) override;
	};
}


