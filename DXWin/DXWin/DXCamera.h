#pragma once
#include <DirectXMath.h>
namespace MyDirectX
{
	struct CameraParam
	{
		DirectX::XMVECTOR mPos;
		DirectX::XMVECTOR mLookup;
		DirectX::XMVECTOR mUp;
		float mRatio;
	};

	class DXCamera
	{
	public:
		DXCamera();
		~DXCamera();
		DirectX::XMMATRIX GetDXCameraParam(float xRote, float yRote);
		void SetEyeParamWithRatio(DirectX::XMVECTOR pos, DirectX::XMVECTOR lookup, DirectX::XMVECTOR up,float ratio);
	private:
		CameraParam mParam;	
	};
}


