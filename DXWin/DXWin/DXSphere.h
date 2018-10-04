#pragma once
#include <d3d11.h>
#include <memory>
#include "DXManager.h"
#include <wrl/client.h>
#include <vector>  
#include <DirectXMath.h>
#include "DXGameObject.h"
namespace MyDirectX 
{
	class DXSphere :public DXGameObject
	{
	public:
		DXSphere(DXManager *dxManager, DXInput* input, DXCamera* camera);
		DXSphere(TRANSFORM *transform, DXManager *dxManager, DXInput* input, DXCamera* camera);
		~DXSphere();
		virtual HRESULT Init(DXManager* dxManager, DXInput* input, DXCamera* camera) override;
		virtual void Update() override;
		virtual void Render() override;
		virtual void Exit() override;
	private:
		//シェーダを生成
		HRESULT CreateShader();
		//定数バッファを生成
		HRESULT CreateConstantBuffer();
		//頂点情報と頂点バッファ生成
		HRESULT CreateVertex();
		//頂点インデックスとインデックスバッファ生成
		HRESULT CreateIndex();
		//ラスタライズステート生成
		HRESULT CreateRasterizeState();
		//データ更新用バッファ
		CONSTANT_BUFFER2 cBuffer;
		int mDrawNum;
	};
}



