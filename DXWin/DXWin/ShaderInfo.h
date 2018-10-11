#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

namespace MyDirectX 
{
	struct SHADER_DATA
	{
		LPCWSTR VertexName;
		LPCWSTR PixelName;
		LPCSTR VertexEntry;
		LPCSTR PixelEntry;
		LPCSTR VertexVersion;
		LPCSTR PixelVersion;
		D3D11_INPUT_ELEMENT_DESC* InputLayout;
		int LayoutNum;
	};

	struct CONSTANT_BUFFER_DATA
	{
		DirectX::XMMATRIX mW;
		DirectX::XMMATRIX mWVP;
		DirectX::XMVECTOR vLightPos;
		DirectX::XMVECTOR vEyePos;
		DirectX::XMVECTOR vColor;
	};

	class ShaderInfo
	{
	public:
		ShaderInfo();
		~ShaderInfo();
		SHADER_DATA* shader;
	};
}


