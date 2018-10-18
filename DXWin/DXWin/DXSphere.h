#pragma once
#include <d3d11.h>
#include "DXManager.h"
#include "MeshAndShader.h"
#include "IComponent.h"
#include "DXGameObject.h"
#include "MeshRenderer.h"
namespace MyDirectX 
{
	class DXSphere :public Component
	{
	public:
		DXSphere(){};
		~DXSphere() {};
		virtual void Initialize(DXGameObject* gameObject) override;
	};
}



