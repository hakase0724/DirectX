#pragma once
#include "DXGameObject.h"

namespace MyDirectX
{
	class IComponent
	{
	public:
		virtual bool Init(TRANSFORM* transform, DXManager* dxManager, DXInput* input, DXCamera* camera) = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Exit() = 0;
	};
}
