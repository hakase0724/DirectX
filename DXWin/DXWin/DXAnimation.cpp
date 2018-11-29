#include "stdafx.h"
#include "DXAnimation.h"

using namespace MyDirectX;
void DXAnimation::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = mGameObject->GetID();
	mTag = mGameObject->GetTag();
	mFileNumber = 0;
	mWaitFrameCount = 0;
}

void DXAnimation::Initialize()
{
	mAnimationTexture->SetTexture(mFileNameList[mFileNumber]);
}

void DXAnimation::Update()
{
	mWaitFrameCount++;
	if(mWaitFrameCount % mTextureChangeCount == 0)
	{
		mWaitFrameCount = 0;
		mFileNumber = (++mFileNumber) % (int)mFileNameList.size();
		mAnimationTexture->SetTexture(mFileNameList[mFileNumber]);
	}
}

void DXAnimation::SetAnimationFile(const wchar_t * fileName)
{
	mFileNameList.push_back(const_cast<wchar_t*>(fileName));
}
