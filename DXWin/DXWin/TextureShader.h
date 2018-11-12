#pragma once
#include "ShaderInfo.h"

namespace MyDirectX
{
	class TextureShader :public ShaderInfo
	{
	public:
		TextureShader();
		~TextureShader();
		virtual UINT GetSize() override { return sizeof(TEXTURE_CONSTANT_BUFFER); }
	};

}

