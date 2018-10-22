#include "stdafx.h"
#include "SquareCollider2D.h"
#include <typeinfo>

using namespace DirectX;
using namespace MyDirectX;

void SquareCollider2D::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
	mId = gameObject->GetID();
	mPos = CalcPos();
	oneSide = 1.0f;
	mName = mGameObject->GetName();
}

void SquareCollider2D::Render()
{
}

void SquareCollider2D::LateUpdate()
{
	mPos = CalcPos();
}

void SquareCollider2D::Exit()
{
}

bool SquareCollider2D::IsCollision(Collider2D* otherCollider)
{
	auto square = dynamic_cast<SquareCollider2D*>(otherCollider);
	if (square == NULL) return false;
	info.name = otherCollider->GetName();
	info.id = otherCollider->GetID();
	std::string otherName = otherCollider->GetName();
	bool isCollisionResult = IsSquareCollision(square);
	auto found = std::find(mCollisionList.begin(), mCollisionList.end(), info.id);
	if(isCollisionResult)
	{		
		if (found != mCollisionList.end()) 
		{
			mGameObject->OnCollisionStay(&info);
		}
		//“–‚½‚èŽn‚ß‚½
		else
		{
			mCollisionList.push_back(info.id);
			mGameObject->OnCollisionEnter(&info);
		}
	}
	else
	{
		//“–‚½‚èI‚í‚Á‚½
		if (found != mCollisionList.end())
		{
			auto remove = std::remove_if(mCollisionList.begin(), mCollisionList.end(), [&](UINT id)->bool {return id == info.id; });
			mCollisionList.erase(remove, mCollisionList.end());
			mGameObject->OnCollisionExit(&info);
		}
	}
	return isCollisionResult;

}

Point2D SquareCollider2D::CalcPos()
{
	auto pos = mGameObject->GetTransform().Position;
	return Point2D(pos.x,pos.y);
}

bool SquareCollider2D::IsSquareCollision(SquareCollider2D* otherSquareCollider)
{
	Point2D* points[] = 
	{
		otherSquareCollider->LeftTop(),
		otherSquareCollider->RightTop(),
		otherSquareCollider->LeftBottom(),
		otherSquareCollider->RightBottom()
	};

	bool judgeResult = false;
	for(auto point:points)
	{
		if (mPos.x - oneSide / 2 <= point->x && point ->x <= mPos.x + oneSide / 2)
		{
			if (mPos.y - oneSide / 2 <= point->y && point->y <= mPos.y + oneSide / 2)
			{			
				judgeResult = true;
				break;
			}
		}
	}
	info.name = otherSquareCollider->GetName();
	return judgeResult;
}