#pragma once
#include "MyStructs.h"
#include "CommonValues.h"
namespace MyDirectX 
{
	class MeshInfo
	{
	public:
		MeshInfo() {};
		virtual ~MeshInfo() {};
		int* indexes;
		VERTEX_DATA* vertics;
		TEXTURE_VERTEX_DATA* vertexInfo;
		int indexNum;
		int vertexNum;
		virtual UINT GetSize() = 0;
	};
}


