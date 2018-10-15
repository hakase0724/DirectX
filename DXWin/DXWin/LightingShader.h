#pragma once
#include "ShaderInfo.h"
#include "MyStructs.h"
namespace MyDirectX
{
	class LightingShader :public ShaderInfo
	{
	public:
		LightingShader();
		~LightingShader();
		virtual UINT GetSize() override { return sizeof(CONSTANT_BUFFER); }
	};
}

