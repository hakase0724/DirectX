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

	/*�X�N���[�����W�v�Z(1920*1080)*/

	//���g�̍���̒��_�̃X�N���[�����W
	auto leftTop = new TRANSFORM();
	auto leftTopPoint = GetLeftTop();
	leftTop->Position.x = leftTopPoint->x;
	leftTop->Position.y = leftTopPoint->y;
	auto leftTopScreen = camera->WorldToScreenPoint(leftTop);

	//���g�̍����̒��_�̃X�N���[�����W
	auto leftBottom = new TRANSFORM();
	auto leftBottomPoint = GetLeftBottom();
	leftBottom->Position.x = leftBottomPoint->x;
	leftBottom->Position.y = leftBottomPoint->y;
	auto leftBottomScreen = camera->WorldToScreenPoint(leftBottom);

	//���g�̉E��̒��_�̃X�N���[�����W
	auto rightTop = new TRANSFORM();
	auto rightTopPoint = GetRightTop();
	rightTop->Position.x = rightTopPoint->x;
	rightTop->Position.y = rightTopPoint->y;
	auto rightTopScreen = camera->WorldToScreenPoint(rightTop);

	//���g�̉E���̒��_�̃X�N���[�����W
	auto rightBottom = new TRANSFORM();
	auto rightBottomPoint = GetRightBottom();
	rightBottom->Position.x = rightBottomPoint->x;
	rightBottom->Position.y = rightBottomPoint->y;
	auto rightBottomScreen = camera->WorldToScreenPoint(rightBottom);

	//�X�N���[���̍���
	auto screenLeftTop = new TRANSFORM();
	screenLeftTop->Position.x = -1.0f;
	screenLeftTop->Position.y = 1.0f;
	auto screenLeftTopScreen = camera->WorldToScreenPoint(screenLeftTop);

	//�X�N���[���̉E��
	auto screenRightBottom = new TRANSFORM();
	screenRightBottom->Position.x = 1.0f;
	screenRightBottom->Position.y = -1.0f;
	auto screenRightBottomScreen = camera->WorldToScreenPoint(screenRightBottom);

	//�X�N���[���̍���
	auto screenLeftBottom = new TRANSFORM();
	screenLeftBottom->Position.x = -1.0f;
	screenLeftBottom->Position.y = -1.0f;
	auto screenLeftBottomScreen = camera->WorldToScreenPoint(screenLeftBottom);

	//�X�N���[���̉E��
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
		//�����葱���Ă���
		if (found != mCollisionList.end()) 
		{
			mGameObject->OnCollisionStay(&info);
		}
		//������n�߂�
		else
		{
			mGameObject->OnCollisionEnter(&info);
		}
	}
	else
	{
		//������I�����
		if (found != mCollisionList.end())
		{
			mGameObject->OnCollisionExit(&info);
		}
		//�������Ă��Ȃ������łɓ������Ă���͂��̃I�u�W�F�N�g������
		else if(mCollisionList.size() != 0)
		{
			for(auto id:mCollisionList)
			{
				//�������Ă���͂��̃I�u�W�F�N�g����A�N�e�B�u�ɂȂ��Ă�����OnCollisionExit�̏������s��
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