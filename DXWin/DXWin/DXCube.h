#pragma once
#include <d3d11.h>
#include <memory>
#include "DXManager.h"
#include "MeshAndShader.h"
#include "IComponent.h"
#include "DXGameObject.h"
namespace MyDirectX
{
	class DXCube:public Component
	{
	public:
		DXCube(){};
		~DXCube();
		//自身のtransform情報を公開
		TRANSFORM GetTransform() const { return mTransform; }
		//自身のtransform情報を更新
		void SetTransform(TRANSFORM *transform) { mTransform = *transform; }
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Awake() override {};
		virtual void Start() override {};
		bool Init();
		virtual void Update() override {};
		virtual void Render() override;
		virtual void Exit() override;
	private:
		//データ更新用バッファ
		CONSTANT_BUFFER cBuffer;
		//描画数
		int mDrawNum;
		//キューブ描画に必要なパラメータ
		std::unique_ptr<CubeMesh> mMesh;
		std::unique_ptr<LightingShader> mShader;
		//自身が保持するデータ
		TRANSFORM mTransform;
		DXManager* mDXManager;
		DXInput* mDXInput;
		DXCamera* mDXCamera;
		ID3D11DeviceContext* mDeviceContext;
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



