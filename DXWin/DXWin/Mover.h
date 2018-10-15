#pragma once
#include "DXManager.h"
#include "IComponent.h"
#include "DXGameObject.h"

namespace MyDirectX 
{
	class Mover :public Component
	{
	public:
		Mover() {};
		~Mover() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Awake() override {};
		virtual void Start() override {};
		virtual void Update() override;
		virtual void Render() override {};
		virtual void Exit() override {};
	private:
		TRANSFORM mTransform;
		DXInput* mDXInput;
	};
}



