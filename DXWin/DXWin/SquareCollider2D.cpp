#include "stdafx.h"
#include "SquareCollider2D.h"
#include <typeinfo>

using namespace DirectX;
using namespace MyDirectX;

void SquareCollider2D::Initialize(DXGameObject * gameObject)
{
	mGameObject = gameObject;
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

bool SquareCollider2D::isCollision(Collider2D* otherCollider)
{
	auto square = dynamic_cast<SquareCollider2D*>(otherCollider);
	if (square == NULL) return false;
	std::string otherName = otherCollider->GetName();
	bool isCollisionResult = isSquareCollision(square);
	if(isCollisionResult)
	{
		//“–‚½‚è‘±‚¯‚Ä‚¢‚é
		if(isCollided)
		{
			mGameObject->OnCollisionStay(&info);
		}
		//“–‚½‚èŽn‚ß‚½
		else
		{
			mGameObject->OnCollisionEnter(&info);
		}
	}
	else
	{
		//“–‚½‚èI‚í‚Á‚½
		if (isCollided)
		{
			mGameObject->OnCollisionExit(&info);
		}
	}
	isCollided = isCollisionResult;
	return isCollided;

}

Point2D SquareCollider2D::CalcPos()
{
	auto pos = mGameObject->GetTransform().Position;
	return Point2D(pos.x,pos.y);
}

bool SquareCollider2D::isSquareCollision(SquareCollider2D* otherSquareCollider)
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
