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
		void SetAlphaValue(float alpha) { mAlphaValue = alpha; }
	private:
		TextureRenderer* mRenderer;
		COLOR mColor;
		float mRotationValue = 0.01f;
		float mAlphaValue = 0.1f;
		float mScaleUpRate = 0.1f;
	};
}
