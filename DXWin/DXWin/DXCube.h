#pragma once
#include <d3d11.h>
#include <memory>
#include "DXManager.h"
#include <DirectXMath.h>
#include "CubeMesh.h"
#include "NormalShader.h"
#include "DXFactory.h"
namespace MyDirectX
{
	class DXCube
	{
	public:
		DXCube(){};
		DXCube(DXManager *dxManager);
		DXCube(TRANSFORM *transform, DXManager *dxManager);
		~DXCube();
		//自身のtransform情報を公開
		TRANSFORM GetTransform() const { return mTransform; }
		//自身のtransform情報を更新
		void SetTransform(TRANSFORM *transform);
		bool Init();
		void Update();
		void Render();
		void Exit();
	private:
		//データ更新用バッファ
		CONSTANT_BUFFER3 cBuffer;
		//描画数
		int mDrawNum;
		//キューブ描画に必要なパラメータ
		std::unique_ptr<DXFactory> mFactory;
		std::unique_ptr<CubeMesh> mMesh;
		std::unique_ptr<NormalShader> mShader;
		//自身が保持するデータ
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



