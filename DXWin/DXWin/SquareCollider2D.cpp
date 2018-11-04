#include "stdafx.h"
#include "SquareCollider2D.h"
#include <typeinfo>
#include "DXGameObjectManager.h"

using namespace DirectX;
using namespace MyDirectX;


DXGameObjectManager* mDXGameObjectManager;

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
	mOneSide = 1.0f;
	mOneSideHarf = mOneSide / 2.0f;
	mName = mGameObject->GetName();
	mDXGameObjectManager = mGameObject->GetDXGameObjectManager();
}

void SquareCollider2D::Render()
{
}

void SquareCollider2D::LateUpdate()
{
	CalcPos();
	auto camera = mGameObject->GetDXCamera();

	/*スクリーン座標計算(1920*1080)*/

	//自身の左上の頂点のスクリーン座標
	auto leftTop = new TRANSFORM();
	auto leftTopPoint = GetLeftTop();
	leftTop->Position.x = leftTopPoint->x;
	leftTop->Position.y = leftTopPoint->y;
	auto leftTopScreen = camera->WorldToScreenPoint(leftTop);

	//自身の左下の頂点のスクリーン座標
	auto leftBottom = new TRANSFORM();
	auto leftBottomPoint = GetLeftBottom();
	leftBottom->Position.x = leftBottomPoint->x;
	leftBottom->Position.y = leftBottomPoint->y;
	auto leftBottomScreen = camera->WorldToScreenPoint(leftBottom);

	//自身の右上の頂点のスクリーン座標
	auto rightTop = new TRANSFORM();
	auto rightTopPoint = GetRightTop();
	rightTop->Position.x = rightTopPoint->x;
	rightTop->Position.y = rightTopPoint->y;
	auto rightTopScreen = camera->WorldToScreenPoint(rightTop);

	//自身の右下の頂点のスクリーン座標
	auto rightBottom = new TRANSFORM();
	auto rightBottomPoint = GetRightBottom();
	rightBottom->Position.x = rightBottomPoint->x;
	rightBottom->Position.y = rightBottomPoint->y;
	auto rightBottomScreen = camera->WorldToScreenPoint(rightBottom);

	//スクリーンの左上
	auto screenLeftTop = new TRANSFORM();
	screenLeftTop->Position.x = -1.0f;
	screenLeftTop->Position.y = 1.0f;
	auto screenLeftTopScreen = camera->WorldToScreenPoint(screenLeftTop);

	//スクリーンの右下
	auto screenRightBottom = new TRANSFORM();
	screenRightBottom->Position.x = 1.0f;
	screenRightBottom->Position.y = -1.0f;
	auto screenRightBottomScreen = camera->WorldToScreenPoint(screenRightBottom);

	//スクリーンの左下
	auto screenLeftBottom = new TRANSFORM();
	screenLeftBottom->Position.x = -1.0f;
	screenLeftBottom->Position.y = -1.0f;
	auto screenLeftBottomScreen = camera->WorldToScreenPoint(screenLeftBottom);

	//スクリーンの右上
	auto screenRightTop = new TRANSFORM();
	screenRightTop->Position.x = 1.0f;
	screenRightTop->Position.y = 1.0f;
	auto screenRightTopScreen = camera->WorldToScreenPoint(screenRightTop);
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
	auto found = std::find(mCollisionList.begin(), mCollisionList.end(), info.id);
	bool isCollisionResult = IsSquareCollision(square);
	if(isCollisionResult)
	{		
		//当たり続けている
		if (found != mCollisionList.end()) 
		{
			mGameObject->OnCollisionStay(&info);
		}
		//当たり始めた
		else
		{
			mGameObject->OnCollisionEnter(&info);
		}
	}
	else
	{
		//当たり終わった
		if (found != mCollisionList.end())
		{
			mGameObject->OnCollisionExit(&info);
		}
		//当たっていないがすでに当たっているはずのオブジェクトがいる
		else if(mCollisionList.size() != 0)
		{
			for(auto id:mCollisionList)
			{
				//当たっているはずのオブジェクトが非アクティブになっていたらOnCollisionExitの処理を行う
				if(!mDXGameObjectManager->IsEnable(id))
				{
					mGameObject->OnCollisionExit(&info);
					break;
				}
			}
		}
	}
	return isCollisionResult;
}

void SquareCollider2D::OnCollisionEnter(CollisionInfo * info)
{
	mCollisionList.push_back(info->id);
}

void SquareCollider2D::OnCollisionExit(CollisionInfo * info)
{
	auto remove = std::remove_if(mCollisionList.begin(), mCollisionList.end(), [&](UINT id)->bool {return id == info->id; });
	mCollisionList.erase(remove, mCollisionList.end());
}

void SquareCollider2D::CalcPos()
{
	auto pos = mGameObject->GetTransform().Position;
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
	//判定結果を格納する
	bool judgeResult = false;
	//相手の頂点
	Point2D* otherPoints[] = 
	{
		otherSquareCollider->GetLeftTop(),
		otherSquareCollider->GetRightTop(),
		otherSquareCollider->GetLeftBottom(),
		otherSquareCollider->GetRightBottom()
	};
	
	//自身の上下左右の領域
	auto leftX = GetLeftX();
	auto rightX = GetRightX();
	auto topY = GetTopY();
	auto bottomY = GetBottomY();
	//相手が自身にめり込んでいるか
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
	//すでに当たり判定がとれている場合は以後の処理をしない
	if (judgeResult) return judgeResult;
	//相手の頂点
	Point2D* myPoints[] =
	{
		GetLeftTop(),
		GetRightTop(),
		GetLeftBottom(),
		GetRightBottom()
	};
	//相手の上下左右の領域
	float otherLeftX = otherSquareCollider->GetLeftX();
	float otherRightX = otherSquareCollider->GetRightX();
	float otherTopY = otherSquareCollider->GetTopY();
	float otherBottomY = otherSquareCollider->GetBottomY();
	//自分が相手にめり込んでいるか
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