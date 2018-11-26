#include "stdafx.h"
#include "NonLightingShader.h"

using namespace MyDirectX;

NonLightingShader::NonLightingShader()
{
	shader = new SHADER_DATA();
	shader->VertexName = L"Shader/NonLightingShader.hlsl";
	shader->PixelName = L"Shader/NonLightingShader.hlsl";
	shader->VertexEntry = "VS";
	shader->PixelEntry = "PS";
	shader->VertexVersion = "vs_5_0";
	shader->PixelVersion = "ps_5_0";
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	shader->LayoutNum = ARRAYSIZE(layout);
	shader->InputLayout = new D3D11_INPUT_ELEMENT_DESC[shader->LayoutNum];
	for (int i = 0; i < shader->LayoutNum; i++)
	{
		shader->InputLayout[i] = layout[i];
	}
}


NonLightingShader::~NonLightingShader()
{
	delete shader->InputLayout;
	delete shader;
}
