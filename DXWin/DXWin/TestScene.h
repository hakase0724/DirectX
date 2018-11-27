#pragma once
#include "Scene.h"

namespace MyDirectX
{
	class TestScene :public Scene
	{
	public:
		TestScene() {};
		~TestScene() {};
		virtual void Init() override;
		virtual void SceneStart() override;
		virtual void SceneUpdate() override;
		virtual void SceneEnd() override;
		virtual bool IsSceneEnd() override;
	private:
		DXGameObject* mGauge;
		double mMaxHitPoint = 1000;
		double mHitPoint;
		TRANSFORM* mTransform;
		double rate = 1.0;
		float mDefaultScaleX;
		float mDefaultPositionX;
	};
}
