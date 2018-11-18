#include "stdafx.h"
#include "DXText.h"
#include "DXGameObject.h"

using namespace MyDirectX;

void DXText::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = mGameObject->GetID();
	mTag = mGameObject->GetTag();
}

void DXText::UpdateText(const wchar_t * texts)
{
	auto size = wcslen(texts);
	auto offset = mGameObject->GetTransform()->Scale.x;
	auto addRendererNum = (int)(size - mRenderers.size());
	//出そうとする文字数が自分の持っている表示コンポーネントの数より多ければ
	if(addRendererNum > 0)
	{
		//不足分を追加する
		for(int i = 0;i < addRendererNum;i++)
		{
			auto renderer = mGameObject->AddComponent<TextRenderer>();
			mRenderers.push_back(renderer);
		}
	}
	//文字更新
	for (int i = 0; i < size; i++)
	{
		mRenderers[i]->CreateText(&texts[i], (float)i * offset);
	}
	//余ってるコンポーネントを空白にする
	if(addRendererNum < 0)
	{
		for (int i = size; i < size + abs((int)addRendererNum); i++)
		{
			mRenderers[i]->CreateText(L" ", (float)i * offset);
		}
	}
}

void DXText::SetText(const wchar_t* texts)
{
	auto size = wcslen(texts);
	auto offset = mGameObject->GetTransform()->Scale.x;
	for (int i = 0; i < size; i++)
	{
		auto renderer = mGameObject->AddComponent<TextRenderer>();
		renderer->CreateText(&texts[i], (float)i * offset);
		mRenderers.push_back(renderer);
	}
}
