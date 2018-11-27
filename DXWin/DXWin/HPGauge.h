#pragma once
#include "IComponent.h"
#include "DXGameObject.h"

namespace MyDirectX
{
	class HPGauge :public Component
	{
	public:
		HPGauge() {};
		~HPGauge() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		void SetHPViewObject(IHP* hp) { mHPViewObject = hp; }
		virtual void Update() override;
	private:
		//体力を表示するオブジェクト
		IHP* mHPViewObject;
		//計算に使う初期値
		TRANSFORM* mTransform;
		float mDefaultScaleX;
		float mDefaultPositionX;
		double mMaxHitPoint;
	};
}


