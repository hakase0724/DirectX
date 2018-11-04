#pragma once
#include <d3d11.h>
#include <typeinfo>
#include "DXManager.h"
#include "IComponent.h"
#include "DXGameObject.h"
#include "MeshAndShader.h"
#include "DXRenderDataPool.h"

namespace MyDirectX
{
	class MeshRenderer :public Component
	{
	public:
		MeshRenderer() {};
		~MeshRenderer();
		//パイプラインの解釈の仕方を変更する
		void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology) { mTopology = topology; }
		void SetColor(float r, float g, float b, float a);
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Awake() override {};
		virtual void Start() override {};
		virtual void Update() override {};
		virtual void Render() override;
		virtual void Exit() override;
		virtual void OnCollisionEnter(CollisionInfo* info) override;
		virtual void OnCollisionStay(CollisionInfo* info) override;
		virtual void OnCollisionExit(CollisionInfo* info) override;
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
		//描画色
		//赤
		float r;
		//緑
		float g;
		//青
		float b;
		//透明度
		float a;
		//自身が保持するデータ
		DXManager* mDXManager;
		DXCamera* mDXCamera;
		DXFactory* mDXFactory;
		ID3D11Device* mDevice;
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
		//インデックス用のバッファ
		ID3D11Buffer* mIndexBuffer;
		//ラスタライズステート
		ID3D11RasterizerState* mRasterizerState;
		//パイプラインの解釈の仕方
		D3D11_PRIMITIVE_TOPOLOGY mTopology;
	};

	//メッシュを作る
	template<typename T>
	inline void MeshRenderer::CreateMesh()
	{
		//受け取れる型でなければreturn
		if (!typeid(T).before(typeid(MeshInfo*))) return;
		//メッシュ情報取得
		T* pInfo = mGameObject->GetDXManager()->GetDXRenderDataPool()->GetMesh<T>();	
		//メッシュ情報をもとにレンダリングに必要なメッシュを作成
		mDXFactory->CreateMesh(pInfo, mDevice, &mVertexBuffer, &mIndexBuffer);
		//描画する頂点数をセット
		mDrawNum = pInfo->indexNum;
	}
	//シェーダーを作る
	template<typename T>
	inline void MeshRenderer::CreateShader()
	{
		//受け取れる型でなければreturn
		if (!typeid(T).before(typeid(ShaderInfo*))) return;
		//シェーダー情報取得
		T* pInfo = mGameObject->GetDXManager()->GetDXRenderDataPool()->GetShader<T>();
		//シェーダー情報をもとにシェーダーを作成
		mDXFactory->CreateShader(pInfo, mDevice, &mVertexShader, &mPixelShader, &mVertexLayout, &mRasterizerState, &mConstantBuffer);
	}
}


