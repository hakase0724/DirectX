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
		//�̗͂�\������I�u�W�F�N�g
		IHP* mHPViewObject;
		//�v�Z�Ɏg�������l
		TRANSFORM* mTransform;
		float mDefaultScaleX;
		float mDefaultPositionX;
		double mMaxHitPoint;
	};
}


