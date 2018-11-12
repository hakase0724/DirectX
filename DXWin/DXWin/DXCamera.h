#pragma once
#include <DirectXMath.h>
#include "MyStructs.h"
namespace MyDirectX
{
	class DXCamera
	{
	public:
		DXCamera(CAMERA_PARAM *param);
		~DXCamera();
		DirectX::XMMATRIX GetDXCameraParam(TRANSFORM* transform);
		CAMERA_PARAM GetCameraParam() const { return mParam;}
		DirectX::XMMATRIX GetWorld(TRANSFORM* transform);
		DirectX::XMVECTOR WorldToScreenPoint(TRANSFORM* transform);
		void SetEyeParamWithRatio(DirectX::XMVECTOR pos, DirectX::XMVECTOR lookup, DirectX::XMVECTOR up,float ratio);
		void SetRotation(float x, float y );
		void SetPos(float x = 0.0f, float y = 0.0f,float z = 0.0f);
	private:
		CAMERA_PARAM mParam;	
		DirectX::XMMATRIX* mWorldToScreenPointMatrix;
	};
}


