#pragma once
#include <d3d11.h>
#include <memory>
#include <vector>  
#include <DirectXMath.h>
#include "DXManager.h"
#include "IComponent.h"


namespace MyDirectX
{
	class DXGameObject
	{
	public:
		DXGameObject(DXManager* dxManager, DXInput* input, DXCamera* camera);
		DXGameObject(TRANSFORM* transform, DXManager* dxManager, DXInput* input, DXCamera* camera);
		~DXGameObject();
		//自身のtransform情報を公開
		TRANSFORM GetTransform() const { return mTransform; }
		DXManager* GetDXManager() const { return mDXManager; }
		DXInput* GetDXInput() const { return mDXInput; }
		DXCamera* GetDXCamera() const { return mDXCamera; }
		//自身のtransform情報を更新
		virtual void SetTransform(TRANSFORM *transform);
		template <typename T>
		void AddComponent();
		//自身の初期化
		virtual HRESULT Init(DXManager* dxManager, DXInput* input, DXCamera* camera);
		//自身の情報更新
		virtual void Update();
		//自身の描画
		virtual void Render();
		//自身の解放
		virtual void Exit();
	protected:
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
		std::vector<std::unique_ptr<IComponent>> mComponentList;
	};
	
}



