#pragma once
#include "IComponent.h"

namespace MyDirectX
{
	class PowerUpItemPool;
	class PowerUpItem :public Component
	{
	public:
		PowerUpItem() {};
		~PowerUpItem() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void OnCollisionEnter2D(Collider2D* col) override;
		virtual void OnDisable() override;
		void SetPool(PowerUpItemPool* pool) { mPool = pool; }
	private:
		PowerUpItemPool* mPool;
	};
}


