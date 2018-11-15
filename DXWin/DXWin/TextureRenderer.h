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
		//�e�N�X�`�����\�[�X�̃|�C���^
		ID3D11Resource* mTexture;
		//�e�N�X�`�����\�[�X�ƃV�F�[�_�[���q������
		ID3D11ShaderResourceView* mShaderResourceView;
		//�e�N�X�`���̊g��k�����ɍ��킹�ĕύX���������
		ID3D11SamplerState* mSampler;
	};

}

