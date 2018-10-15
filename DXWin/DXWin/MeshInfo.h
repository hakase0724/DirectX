#pragma once
#include <DirectXMath.h>
#include <memory>
namespace MyDirectX 
{
	struct VERTEX_DATA
	{
		DirectX::XMFLOAT3 V;
		DirectX::XMFLOAT3 N;
		VERTEX_DATA() = default;
		VERTEX_DATA(DirectX::XMFLOAT3 v, DirectX::XMFLOAT3 n)
		{
			V = v;
			N = n;
		}
	};
	class MeshInfo
	{
	public:
		MeshInfo() {};
		int* indexes;
		VERTEX_DATA* vertics;
		int indexNum;
		int vertexNum;
		virtual UINT GetSize() = 0;
	};
}


