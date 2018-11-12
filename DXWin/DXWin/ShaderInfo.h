#pragma once
#include "MyStructs.h"

namespace MyDirectX 
{
	class ShaderInfo
	{
	public:
		ShaderInfo() {};
		virtual ~ShaderInfo() {};
		SHADER_DATA* shader;
		virtual UINT GetSize() = 0;
	};
}


