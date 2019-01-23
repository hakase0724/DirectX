#pragma once
#include <d3d11.h>
#include <memory>
#include "MeshFactory.h"
#include "MeshInfo.h"
#include "ShaderFactory.h"
#include "ShaderInfo.h"

namespace MyDirectX
{
	class DXFactory
	{
	public:
		DXFactory();
		~DXFactory() {};
		//���b�V�������
		void CreateMesh(
			MeshInfo* info,
			ID3D11Device* device,
			ID3D11Buffer ** vertexBuffer,
			ID3D11Buffer ** indexBuffer);
		//�V�F�[�_�[�����
		void CreateShader(ShaderInfo * info, 
			ID3D11Device * device,
			ID3D11VertexShader ** vertex,
			ID3D11PixelShader ** pixel,
			ID3D11InputLayout ** inputLayout, 
			ID3D11RasterizerState ** rasterizerState,
			ID3D11Buffer ** constantBuffer);
	private:
		//���b�V�������N���X
		std::unique_ptr<MeshFactory> mMeshFactory;
		//�V�F�[�_�[�����N���X
		std::unique_ptr<ShaderFactory> mShaderFactory;
	};
}


