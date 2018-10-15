#pragma once
#include "ShaderInfo.h"
#include <d3d11.h>
namespace MyDirectX
{
	class ShaderFactory
	{
	public:
		ShaderFactory() {};
		~ShaderFactory() {};
		void Create(ShaderInfo * info,
			ID3D11Device * device,
			ID3D11VertexShader ** vertex,
			ID3D11PixelShader ** pixel,
			ID3D11InputLayout ** inputLayout,
			ID3D11RasterizerState ** rasterizerState,
			ID3D11Buffer ** constantBuffer);
	private:
		void CreateShader(ShaderInfo * info, 
			ID3D11Device * device, 
			ID3D11VertexShader ** vertex, 
			ID3D11PixelShader ** pixel, 
			ID3D11InputLayout ** inputLayout);
		void CreateRasterizerState(ShaderInfo * info, ID3D11Device * device, ID3D11RasterizerState ** rasterizerState);
		void CreateConstantBuffer(ShaderInfo * info, ID3D11Device * device, ID3D11Buffer ** constantBuffer);
	};
}



