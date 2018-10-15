#pragma once
#include "MeshInfo.h"
#include <d3d11.h>

namespace MyDirectX 
{
	class MeshFactory
	{
	public:
		MeshFactory() {};
		~MeshFactory() {};
		void Create(
			MeshInfo* info,
			ID3D11Device* device,
			ID3D11Buffer ** vertexBuffer,
			ID3D11Buffer ** indexBuffer);
	private:
		void CreateVertex(MeshInfo* info, ID3D11Device* device, ID3D11Buffer ** vertexBuffer);
		void CreateIndex(MeshInfo* info, ID3D11Device* device, ID3D11Buffer ** indexBuffer);
	};
}



