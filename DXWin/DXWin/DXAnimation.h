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
		//切り替えるテクスチャコンポーネント
		void SetAnimationTexture(DXTexture* texture) { mAnimationTexture = texture; }
		//テクスチャパスをセットする
		void SetAnimationFile(const wchar_t* fileName);
	private:
		DXTexture* mAnimationTexture;
		//表示するテクスチャのパスの配列
		std::vector<wchar_t*> mFileNameList;
		//今表示しているテクスチャの番号
		int mFileNumber;
		//経過フレーム数
		int mFrameCount;
		//テクスチャを切り替えるフレーム数
		int mTextureChangeCount = 7;
	};
}


