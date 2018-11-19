#include "stdafx.h"
#include "BackGround.h"

using namespace MyDirectX;

void BackGround::UpdateBackGrounds()
{
	if (mBackFirst == nullptr) return;
	if (mBackSecond == nullptr) return;
	auto first = mBackFirst->GetTransform();
	auto second = mBackSecond->GetTransform();
	first->Position.y -= 0.01f;
	second->Position.y -= 0.01f;
	if(first->Position.y <= -5.0f)
	{
		first->Position.y += 10.0f;
	}
	if(second->Position.y <= -5.0f)
	{
		second->Position.y += 10.0f;
	}
}
