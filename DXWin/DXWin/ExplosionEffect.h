#pragma once
#include "IComponent.h"
#include "TextureRenderer.h"

namespace MyDirectX
{
	class ExplosionEffectPool;
	class ExplosionEffect :public Component
	{
	public:
		ExplosionEffect() {};
		~ExplosionEffect() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void OnDisable() override;
		void SetPool(ExplosionEffectPool* pool) { mPool = pool; }
	private:
		ExplosionEffectPool* mPool;
	};
}
