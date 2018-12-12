#pragma once
#include "MeshRenderer.h"

namespace MyDirectX
{
	class TextRenderer :public MeshRenderer
	{
	public:
		TextRenderer() {};
		~TextRenderer() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		/*
		text = �\������
		xOffset = x�����̃I�t�Z�b�g
		yOffset = y�����̃I�t�Z�b�g
		fontName = �t�H���g���@�f�t�H���gMS P����
		*/
		void CreateText
		(
			const wchar_t* text,
			float xOffset = 0.0f,
			float yOffset = 0.0f,
			WCHAR* fontName = (WCHAR*)"�l�r �o����"		
		);
		virtual void Render() override;
		virtual void Exit() override;
	private:
		TEXTURE_CONSTANT_BUFFER cTextureBuffer;
		ID3D11ShaderResourceView* mShaderResorceView;
		ID3D11SamplerState* mSampler;
		ID3D11Resource* mTexture;
		TRANSFORM mTransform;
	};

}

