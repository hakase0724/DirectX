#pragma once
#include "MeshInfo.h"

namespace MyDirectX
{
	class SphereMesh :public MeshInfo
	{
	public:
		SphereMesh();
		~SphereMesh();
		virtual UINT GetSize() override { return sizeof(VERTEX_DATA); }
	};
}



