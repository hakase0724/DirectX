#pragma once
#include <string>
#include <memory>
#include <d3d11.h>
#include <DirectXMath.h>
#include "Primitive2D.h"
#include "Primitive3D.h"
#include "MyEnums.h"
#include "AlignedAllocationPolicy.h"
namespace MyDirectX
{
	class DXGameObject;

	//色情報を保持する構造体
	struct COLOR
	{
		//赤
		float r;
		//緑
		float g;
		//青
		float b;
		//アルファ値
		float a;
	};

	//定数バッファ
	struct CONSTANT_BUFFER:public AlignedAllocationPolicy<16> 
	{
		DirectX::XMMATRIX mW;
		DirectX::XMMATRIX mWVP;
		DirectX::XMVECTOR vLightPos;
		DirectX::XMVECTOR vEyePos;
		DirectX::XMVECTOR vColor;
	};

	struct TEXTURE_CONSTANT_BUFFER
	{
		DirectX::XMMATRIX mWVP;
		DirectX::XMVECTOR mColor;
	};

	//カメラ情報
	struct CAMERA_PARAM:public AlignedAllocationPolicy<16>
	{
		DirectX::XMVECTOR mPos;
		DirectX::XMVECTOR mLookup;
		DirectX::XMVECTOR mUp;
		float mRatio;
		float mXRote;
		float mYRote;
		CAMERA_PARAM()
		{
			mPos = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			mLookup = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			mUp = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			mRatio = 0.0f;
			mXRote = 0.0f;
			mYRote = 0.0f;
		}

		CAMERA_PARAM(DirectX::XMVECTOR pos, DirectX::XMVECTOR lookup, DirectX::XMVECTOR up, float ratio)
		{
			mPos = pos;
			mLookup = lookup;
			mUp = up;
			mRatio = ratio;
			mXRote = 0.0f;
			mYRote = 0.0f;
		}
	};

	//オブジェクトが持つ位置回転スケール情報
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

		TRANSFORM(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rote)
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

	//頂点情報構造体
	struct VERTEX_DATA
	{
		DirectX::XMFLOAT3 V;
		DirectX::XMFLOAT3 N;
		VERTEX_DATA() = default;
		VERTEX_DATA(DirectX::XMFLOAT3 v, DirectX::XMFLOAT3 n)
		{
			V = v;
			N = n;
		}
	};

	struct TEXTURE_VERTEX_DATA
	{
		DirectX::XMFLOAT3 V;
		DirectX::XMFLOAT2 T;
		TEXTURE_VERTEX_DATA() = default;
		TEXTURE_VERTEX_DATA(DirectX::XMFLOAT3 v, DirectX::XMFLOAT2 t)
		{
			V = v;
			T = t;
		}
	};

	//シェーダーに設定するデータ
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

	//テクスチャ情報を保持
	struct TEXTURE_DATA
	{
		wchar_t* fileName;
		ID3D11Resource* texture;
		ID3D11ShaderResourceView* shaderView;
		~TEXTURE_DATA()
		{
			if(texture)texture->Release();
			if(shaderView)shaderView->Release();
		}
	};

}
