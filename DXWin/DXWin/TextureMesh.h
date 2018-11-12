#pragma once
#include "MeshInfo.h"

namespace MyDirectX 
{
	class TextureMesh :public MeshInfo
	{
	public:
		TextureMesh();
		~TextureMesh();
		virtual UINT GetSize() override { return sizeof(TEXTURE_VERTEX_DATA); }
	};
}


