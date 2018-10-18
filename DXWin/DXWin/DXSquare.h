#pragma once
#include "IComponent.h"
#include <d3d11.h>
#include "DXManager.h"
#include "MeshAndShader.h"
#include "DXGameObject.h"
#include "MeshRenderer.h"

namespace MyDirectX
{
	class DXSquare :public Component
	{
	public:
		DXSquare() {};
		~DXSquare() {};
		virtual void Initialize(DXGameObject* gameObject) override;
	};
}

