#pragma once
#include "ShaderInfo.h"
#include "MyStructs.h"
namespace MyDirectX
{
	class NonLightingShader :public ShaderInfo
	{
	public:
		NonLightingShader();
		~NonLightingShader();
		virtual UINT GetSize() override { return sizeof(CONSTANT_BUFFER); }
	};
}


