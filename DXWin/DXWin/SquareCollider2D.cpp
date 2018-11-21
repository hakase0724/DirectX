#include "stdafx.h"
#include "SquareCollider2D.h"
#include <typeinfo>

using namespace DirectX;
using namespace MyDirectX;



void SquareCollider2D::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = gameObject->GetID();
	mTag = gameObject->GetTag();
	mPos = new Point2D();
	mLeftTop = new Point2D();
	mLeftBottom = new Point2D();
	mRightTop = new Point2D();
	mRightBottom = new Point2D();
	CalcPos();
	mOneSide = cMyOneSide;
	mOneSideHarf = mOneSide / 2.0f;
	mName = mGameObject->GetName();
	mCollisionNum = 0;
}

void SquareCollider2D::Initialize()
{
	mId = mGameObject->GetID();
	mTag = mGameObject->GetTag();
	CalcPos();
	mName = mGameObject->GetName();
}

void SquareCollider2D::LateUpdate()
{
	CalcPos();
}

void SquareCollider2D::Exit()
{
	delete mPos;
	delete mLeftTop;
	delete mLeftBottom;
	delete mRightTop;
	delete mRightBottom;
}

bool SquareCollider2D::IsCollision(Collider2D* otherCollider)
{
	auto square = dynamic_cast<SquareCollider2D*>(otherCollider);
	if (square == NULL) return false;
	auto isCollision = IsSquareCollision(square);
	if(isCollision)
	{
		mCollisionNum++;
	}
	if(mCollisionNum != 0)
	{
		mIsCollided = true;
	}
	return isCollision;
}

void SquareCollider2D::OnCollision()
{
	for(int i = 0;i < mCollisionNum;i++)
	{
		mGameObject->OnCollisionEnter();
	}
	for(int i = 0;i < mPreCollisionNum;i++)
	{
		mGameObject->OnCollisionExit();
	}
	mPreCollisionNum = mCollisionNum;
	mCollisionNum = 0;
	if(mPreCollisionNum == 0)mIsCollided = false;
}

void SquareCollider2D::CalcPos()
{
	auto pos = mGameObject->GetTransform()->Position;
	mPos->x = pos.x;
	mPos->y = pos.y;
	mOneSideHarf = mOneSide / 2;
	mLeftTop->x = mPos->x - mOneSideHarf;
	mLeftTop->y = mPos->y + mOneSideHarf;
	mLeftBottom->x = mPos->x - mOneSideHarf;
	mLeftBottom->y = mPos->y - mOneSideHarf;
	mRightTop->x = mPos->x + mOneSideHarf;
	mRightTop->y = mPos->y + mOneSideHarf;
	mRightBottom->x = mPos->x + mOneSideHarf;
	mRightBottom->y = mPos->y - mOneSideHarf;
}

bool SquareCollider2D::IsSquareCollision(SquareCollider2D* otherSquareCollider)
{
	//���茋�ʂ��i�[����
	bool judgeResult = false;
	//����̒��_
	Point2D* otherPoints[] = 
	{
		otherSquareCollider->GetLeftTop(),
		otherSquareCollider->GetRightTop(),
		otherSquareCollider->GetLeftBottom(),
		otherSquareCollider->GetRightBottom()
	};
	
	//���g�̏㉺���E�̗̈�
	auto leftX = GetLeftX();
	auto rightX = GetRightX();
	auto topY = GetTopY();
	auto bottomY = GetBottomY();
	//���肪���g�ɂ߂荞��ł��邩
	for(auto point:otherPoints)
	{
		auto x = point->x;
		auto y = point->y;
		if (leftX <= x && x <= rightX)
		{
			if (bottomY <= y && y <= topY)
			{			
				judgeResult = true;
				break;
			}
		}
	}
	//���łɓ����蔻�肪�Ƃ�Ă���ꍇ�͈Ȍ�̏��������Ȃ�
	if (judgeResult) return judgeResult;
	//����̒��_
	Point2D* myPoints[] =
	{
		GetLeftTop(),
		GetRightTop(),
		GetLeftBottom(),
		GetRightBottom()
	};
	//����̏㉺���E�̗̈�
	float otherLeftX = otherSquareCollider->GetLeftX();
	float otherRightX = otherSquareCollider->GetRightX();
	float otherTopY = otherSquareCollider->GetTopY();
	float otherBottomY = otherSquareCollider->GetBottomY();
	//����������ɂ߂荞��ł��邩
	for (auto point : myPoints)
	{
		auto x = point->x;
		auto y = point->y;
		if (otherLeftX <= x && x <= otherRightX)
		{
			if (otherBottomY <= y && y <= otherTopY)
			{
				judgeResult = true;
				break;
			}
		}
	}
	return judgeResult;
}


