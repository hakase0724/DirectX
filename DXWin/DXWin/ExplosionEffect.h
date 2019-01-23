#pragma once
#include "IComponent.h"
#include "TextureRenderer.h"

namespace MyDirectX
{
	class ExplosionEffect :public Component
	{
	public:
		ExplosionEffect() {};
		~ExplosionEffect() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		virtual void Update() override;
	private:
		TextureRenderer* mRenderer;
		COLOR mColor;
	};
}
