#pragma once
#include "IComponent.h"

namespace MyDirectX
{
	class Bomb :public Component
	{
	public:
		Bomb() {};
		~Bomb() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void OnCollisionEnter2D(Collider2D* col) override;
	};

}

