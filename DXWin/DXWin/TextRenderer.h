#pragma once
#include "MeshRenderer.h"

namespace MyDirectX
{
	class TextRenderer :public MeshRenderer
	{
	public:
		TextRenderer();
		~TextRenderer();
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Render() override;
		virtual void Exit() override;
	private:
		TEXTURE_CONSTANT_BUFFER cTextureBuffer;
		ID3D11ShaderResourceView* mShaderResorceView;
		ID3D11SamplerState* mSampler;
		ID3D11Resource* mTexture;
	};

}

