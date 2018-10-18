#pragma once
#include <d3d11.h>
#include <typeinfo>
#include "DXManager.h"
#include "IComponent.h"
#include "DXGameObject.h"
#include "MeshAndShader.h"

namespace MyDirectX
{
	class MeshRenderer :public Component
	{
	public:
		MeshRenderer() {};
		~MeshRenderer();
		//パイプラインの解釈の仕方を変更する
		void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Awake() override {};
		virtual void Start() override {};
		virtual void Update() override {};
		virtual void Render() override;
		virtual void Exit() override;
		//メッシュを作る
		template <typename T>
		void CreateMesh();
		//シェーダーを作る
		template <typename T>
		void CreateShader();
	private:
		//データ更新用バッファ
		CONSTANT_BUFFER cBuffer;
		//描画数
		int mDrawNum;
		//自身が保持するデータ
		DXManager* mDXManager;
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
		//パイプラインの解釈の仕方
		D3D11_PRIMITIVE_TOPOLOGY mTopology;
	};
	template<typename T>
	inline void MeshRenderer::CreateMesh()
	{
		if (!typeid(T).before(typeid(MeshInfo*))) return;
		auto mesh = new T();
		//一文を短くして可読性を上げる
		auto factory = mDXManager->GetDXFactory();
		auto device = mDXManager->GetDevice();
		factory->CreateMesh(mesh, device, &mVertexBuffer, &mIndexBuffer);
		mDrawNum = mesh->indexNum;
	}
	template<typename T>
	inline void MeshRenderer::CreateShader()
	{
		if (!typeid(T).before(typeid(ShaderInfo*))) return;
		auto shader = new T();
		//一文を短くして可読性を上げる
		auto factory = mDXManager->GetDXFactory();
		auto device = mDXManager->GetDevice();
		factory->CreateShader(shader, device, &mVertexShader, &mPixelShader, &mVertexLayout, &mRasterizerState, &mConstantBuffer);
	}
}


