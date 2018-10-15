#pragma once
#include "MeshInfo.h"
namespace MyDirectX 
{
	class CubeMesh :public MeshInfo
	{
	public:
		CubeMesh();
		~CubeMesh();
		virtual UINT GetSize() override { return sizeof(VERTEX_DATA); }
	};
}


