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
	//�\��������
	auto size = (int)wcslen(texts);
	//�e�����̊Ԋu
	auto offset = mGameObject->GetTransform()->Scale.x;
	//�K�v�ȃ����_���[���v�Z
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
		mRenderers[i]->CreateText(texts, (float)i * offset);
		texts++;
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