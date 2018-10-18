#pragma once
#include "MeshInfo.h"

namespace MyDirectX
{
	class SquareMesh :public MeshInfo
	{
	public:
		SquareMesh();
		~SquareMesh();
		virtual UINT GetSize() override { return sizeof(VERTEX_DATA); }
	};
}


