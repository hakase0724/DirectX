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
	//�o�����Ƃ��镶�����������̎����Ă���\���R���|�[�l���g�̐���葽�����
	if(addRendererNum > 0)
	{
		//�s������ǉ�����
		for(int i = 0;i < addRendererNum;i++)
		{
			auto renderer = mGameObject->AddComponent<TextRenderer>();
			mRenderers.push_back(renderer);
		}
	}
	//�����X�V
	for (int i = 0; i < size; i++)
	{
		mRenderers[i]->CreateText(&texts[i], (float)i * offset);
	}
	//�]���Ă�R���|�[�l���g���󔒂ɂ���
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
