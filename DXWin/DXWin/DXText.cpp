#include "stdafx.h"
#include "DXText.h"
#include "DXGameObject.h"

using namespace MyDirectX;

void DXText::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = mGameObject->GetID();
	mTag = mGameObject->GetTag();
	mRenderer = gameObject->GetComponent<TextRenderer>();
	if (mRenderer == nullptr)
	{
		mRenderer = gameObject->AddComponent<TextRenderer>();
	}
	
}
