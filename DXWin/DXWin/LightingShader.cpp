#include "stdafx.h"
#include "LightingShader.h"

using namespace MyDirectX;

LightingShader::LightingShader()
{
	shader = new SHADER_DATA();
	shader->VertexName = L"shader2.hlsl";
	shader->PixelName = L"shader2.hlsl";
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


LightingShader::~LightingShader()
{
	delete shader->InputLayout;
	delete shader;
}