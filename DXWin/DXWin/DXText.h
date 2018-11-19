#pragma once
#include "IComponent.h"
#include "TextRenderer.h"

namespace MyDirectX
{
	class DXText :public Component
	{
	public:
		DXText() {};
		~DXText() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		void UpdateText(const wchar_t* texts);
		void SetText(const wchar_t* texts);
	private:
		std::vector<TextRenderer*> mRenderers;
	};
}

