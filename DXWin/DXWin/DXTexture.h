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
		void SetTexture(const wchar_t* fileName = _T("Texture/Player3_alpha.png"));
	private:
		TextureRenderer* mRenderer;
	};
}


