#pragma once
namespace MyDirectX
{
	struct CONSTANT_BUFFER {
		DirectX::XMMATRIX mW;
		DirectX::XMMATRIX mWVP;
		DirectX::XMVECTOR vLightPos;
		DirectX::XMVECTOR vEyePos;
		DirectX::XMVECTOR vColor;
	};
}
