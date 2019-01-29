#include "stdafx.h"
#include "DXAnimation.h"

using namespace MyDirectX;
void DXAnimation::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = mGameObject->GetID();
	mTag = mGameObject->GetTag();
}

void DXAnimation::Initialize()
{
	mFileNumber = 0;
	mFrameCount = 0;
	mAnimationTexture->SetTexture(mFileNameList[mFileNumber]);
}

void DXAnimation::Update()
{
	mFrameCount++;
	if(mFrameCount % mTextureChangeCount == 0)
	{
		mFrameCount = 0;
		if(mIsLoop)
		{
			mFileNumber = (++mFileNumber) % (int)mFileNameList.size();
		}
		else
		{
			mFileNumber++;
			if (mFileNumber >= (int)mFileNameList.size()) 
			{
				mGameObject->SetEnable(false);
				return;
			}
		}
		
		mAnimationTexture->SetTexture(mFileNameList[mFileNumber]);
	}
}

void DXAnimation::SetAnimationFile(const wchar_t * fileName)
{
	mFileNameList.push_back(const_cast<wchar_t*>(fileName));
}