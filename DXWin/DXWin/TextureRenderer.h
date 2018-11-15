#pragma once
#include "MeshRenderer.h"

namespace MyDirectX
{
	class TextureRenderer :public MeshRenderer
	{
	public:
		TextureRenderer() {};
		~TextureRenderer() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void LoadTexture(wchar_t* fileName);
		virtual void Render() override;
		virtual void Exit() override;
	private:
		TEXTURE_CONSTANT_BUFFER cTextureBuffer;
		//テクスチャリソースのポインタ
		ID3D11Resource* mTexture;
		//テクスチャリソースとシェーダーを繋ぐもの
		ID3D11ShaderResourceView* mShaderResourceView;
		//テクスチャの拡大縮小時に合わせて変更させるもの
		ID3D11SamplerState* mSampler;
	};

}

