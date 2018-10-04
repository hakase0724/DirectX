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
		float mXRote;
		float mYRote;
		CameraParam()
		{
			mPos = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			mLookup = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			mUp = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			mRatio = 0.0f;
			mXRote = 0.0f;
			mYRote = 0.0f;
		}

		CameraParam(DirectX::XMVECTOR pos, DirectX::XMVECTOR lookup, DirectX::XMVECTOR up,float ratio)
		{
			mPos = pos;
			mLookup = lookup;
			mUp = up;
			mRatio = ratio;
			mXRote = 0.0f;
			mYRote = 0.0f;
		}
	};

	struct TRANSFORM
	{
		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT3 Rotation;
		DirectX::XMFLOAT3 Scale;

		TRANSFORM()
		{
			Position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			Rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			Scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		}

		TRANSFORM(DirectX::XMFLOAT3 pos)
		{
			Position = pos;
			Rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			Scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		}

		TRANSFORM(DirectX::XMFLOAT3 pos , DirectX::XMFLOAT3 rote)
		{
			Position = pos;
			Rotation = rote;
			Scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		}

		TRANSFORM(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rote, DirectX::XMFLOAT3 scale)
		{
			Position = pos;
			Rotation = rote;
			Scale = scale;
		}
	};

	class DXCamera
	{
	public:
		DXCamera(CameraParam *param);
		~DXCamera();
		DirectX::XMMATRIX GetDXCameraParam(TRANSFORM transform);
		CameraParam GetCameraParam() const { return mParam;}
		DirectX::XMMATRIX GetWorld(TRANSFORM transform);
		void SetEyeParamWithRatio(DirectX::XMVECTOR pos, DirectX::XMVECTOR lookup, DirectX::XMVECTOR up,float ratio);
		void SetRotation(float x, float y );
		void SetPos(float x = 0.0f, float y = 0.0f,float z = 0.0f);
	private:
		CameraParam mParam;	
	};
}


