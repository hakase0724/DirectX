#pragma once
#include "IComponent.h"

namespace MyDirectX
{
	class Razer :public Component
	{
	public:
		Razer() {};
		~Razer() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		virtual void Update() override;
	private:
		int mFrameCount;
		int mLoopCount = 60;
		TRANSFORM* mTransform;
		float mDefaultScaleY;
		float mDefaultPositionY;
	};
}
