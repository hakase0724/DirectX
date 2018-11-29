#pragma once
#include "IComponent.h"
#include "DXTexture.h"
#include <vector>

namespace MyDirectX
{
	class DXAnimation :public Component
	{
	public:
		DXAnimation() {};
		~DXAnimation() {};
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize() override;
		virtual void Update() override;
		void SetAnimationTexture(DXTexture* texture) { mAnimationTexture = texture; }
		void SetAnimationFile(const wchar_t* fileName);
	private:
		DXTexture* mAnimationTexture;
		std::vector<wchar_t*> mFileNameList;
		int mFileNumber;
		int mWaitFrameCount;
		int mTextureChangeCount = 7;
	};
}


