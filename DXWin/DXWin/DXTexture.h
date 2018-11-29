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
		void SetTexture(const wchar_t* fileName);
		void SetTexture(wchar_t* fileName);
	private:
		TextureRenderer* mRenderer;
	};
}


