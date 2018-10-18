#pragma once
#include "DXManager.h"
#include "MeshAndShader.h"
#include "IComponent.h"
#include "DXGameObject.h"
#include "MeshRenderer.h"
namespace MyDirectX
{
	class DXCube:public Component
	{
	public:
		DXCube(){};
		~DXCube() {};
		virtual void Initialize(DXGameObject* gameObject) override;
	};
}



