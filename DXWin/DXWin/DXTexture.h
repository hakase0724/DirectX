#pragma once
#include "IComponent.h"
#include <d3d11.h>
#include "DXManager.h"
#include "MeshAndShader.h"
#include "DXGameObject.h"
#include "MeshRenderer.h"
#include "TextureRenderer.h"

namespace MyDirectX
{
	class DXTexture :public Component
	{
	public:
		DXTexture() {};
		~DXTexture() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		//読み込むテクスチャパスを設定する
		void SetTexture(const wchar_t* fileName);
		void SetTexture(wchar_t* fileName);
		void SetDefaultColor(float r, float g, float b, float a) { mRenderer->SetDefaultColor(r, g, b, a); }
		//テクスチャの色を設定する
		void SetColor(float r, float g, float b, float a);
	private:
		TextureRenderer* mRenderer;
	};
}


