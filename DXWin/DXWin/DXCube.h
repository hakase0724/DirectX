#pragma once
#include <d3d11.h>
#include <memory>
#include "DXManager.h"
#include <wrl/client.h>
#include <vector>  
#include <DirectXMath.h>
#include "DXGameObject.h"
#include "IComponent.h"
namespace MyDirectX
{
	class DXCube:public IComponent
	{
	public:
		DXCube(){};
		DXCube(DXManager *dxManager, DXInput* input, DXCamera* camera);
		DXCube(TRANSFORM *transform, DXManager *dxManager, DXInput* input, DXCamera* camera);
		~DXCube();
		//自身のtransform情報を公開
		TRANSFORM GetTransform() const { return mTransform; }
		//自身のtransform情報を更新
		virtual void SetTransform(TRANSFORM *transform);
		virtual bool Init(TRANSFORM* transform, DXManager* dxManager, DXInput* input, DXCamera* camera) override;
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
		CONSTANT_BUFFER cBuffer;
		int mDrawNum;

		TRANSFORM mTransform;
		DXManager* mDXManager;
		DXInput* mDXInput;
		DXCamera* mDXCamera;
		//入力アセンブラステージの入力データにアクセス　入力してなんかするときに使いそう
		ID3D11InputLayout* mVertexLayout;
		//頂点シェーダー管理
		ID3D11VertexShader* mVertexShader;
		//ピクセルシェーダー管理
		ID3D11PixelShader* mPixelShader;
		//データバッファ　シェーダーとのデータのやり取りに使っている
		ID3D11Buffer* mConstantBuffer;
		//頂点シェーダー用のバッファ
		ID3D11Buffer* mVertexBuffer;
		//インデックス要のバッファ
		ID3D11Buffer* mIndexBuffer;
		//ラスタライズステート
		ID3D11RasterizerState* mRasterizerState;
	};
}



