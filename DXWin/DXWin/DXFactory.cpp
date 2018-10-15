#include "stdafx.h"
#include "DXFactory.h"

using namespace MyDirectX;

DXFactory::DXFactory()
{
	mMeshFactory = std::make_unique<MeshFactory>();
	mShaderFactory = std::make_unique<ShaderFactory>();
}

void DXFactory::CreateMesh(MeshInfo * info, ID3D11Device * device, ID3D11Buffer ** vertexBuffer, ID3D11Buffer ** indexBuffer)
{
	mMeshFactory->Create(info, device, vertexBuffer, indexBuffer);
}

void DXFactory::CreateShader(ShaderInfo * info, 
	ID3D11Device * device, 
	ID3D11VertexShader ** vertex, 
	ID3D11PixelShader ** pixel, 
	ID3D11InputLayout ** inputLayout, 
	ID3D11RasterizerState ** rasterizerState,
	ID3D11Buffer ** constantBuffer)
{
	mShaderFactory->Create(info,device,vertex,pixel,inputLayout,rasterizerState,constantBuffer);
}
