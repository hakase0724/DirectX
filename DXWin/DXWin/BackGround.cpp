#include "stdafx.h"
#include "BackGround.h"

using namespace MyDirectX;

void BackGround::UpdateBackGrounds()
{
	if (mBackFirst == nullptr) return;
	if (mBackSecond == nullptr) return;
	auto first = mBackFirst->GetTransform();
	auto second = mBackSecond->GetTransform();
	first->Position.y -= mMoveSpeed;
	second->Position.y -= mMoveSpeed;
	if(first->Position.y <= MOVE_UP_Y_POSITION)
	{
		first->Position.y += MOVE_UP_VALUE;
	}
	if(second->Position.y <= MOVE_UP_Y_POSITION)
	{
		second->Position.y += MOVE_UP_VALUE;
	}
}
