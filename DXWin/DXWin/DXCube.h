#pragma once
#include <d3d11.h>
#include <memory>
#include "DXManager.h"
#include <wrl/client.h>
#include <vector>  
#include <DirectXMath.h>
namespace MyDirectX
{
	class DXCube
	{
	public:
		DXCube();
		DXCube(DXManager *dxManager);
		DXCube(TRANSFORM *transform);
		DXCube(TRANSFORM *transform, DXManager *dxManager);
		~DXCube();
		TRANSFORM GetTransform() const { return mTransform; }
		void SetTransform(TRANSFORM transform);
		HRESULT Init(DXManager* dxManager);
		BOOL Update(DXInput* input, DXCamera* camera);
		void Render();
		void Exit();
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
		ID3D11RasterizerState* mRasterizerState;
		DXManager* mDXManager;
		//データ更新用バッファ
		CONSTANT_BUFFER cBuffer;
		TRANSFORM mTransform;
		int mDrawNum;
		float xRote;
		float yRote;
	};
}



