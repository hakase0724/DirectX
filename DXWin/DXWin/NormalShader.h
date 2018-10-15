#pragma once
#include "ShaderInfo.h"
#include "MyStructs.h"
namespace MyDirectX
{
	class NormalShader :public ShaderInfo
	{
	public:
		NormalShader();
		~NormalShader();
		virtual UINT GetSize() override { return sizeof(CONSTANT_BUFFER); }
	};
}


