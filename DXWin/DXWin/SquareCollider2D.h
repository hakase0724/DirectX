#pragma once
#include "Collider2D.h"
#include "DXGameObject.h"
#include "MeshAndShader.h"
#include <DirectXMath.h>
#include "CommonValues.h"

namespace MyDirectX
{
	class DXGameObjectManager;

	class SquareCollider2D :public Collider2D
	{
	public:
		SquareCollider2D() {};
		~SquareCollider2D() {};
		//���g�̒��_4�����J����
		Point2D* GetRightTop() const { return mRightTop; }
		Point2D* GetLeftTop() const { return mLeftTop; }
		Point2D* GetRightBottom() const { return mRightBottom; }
		Point2D* GetLeftBottom() const { return mLeftBottom; }
		//���g�̏Փ˗̈�����J����
		float GetLeftX() const { return mPos->x - mOneSideHarf; }
		float GetRightX() const { return mPos->x + mOneSideHarf; }
		float GetTopY() const { return mPos->y + mOneSideHarf; }
		float GetBottomY() const { return mPos->y - mOneSideHarf; }
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize();
		virtual void LateUpdate() override;
		virtual void Exit() override;
		//�Փ˔���
		virtual bool IsCollision(Collider2D* otherCollider) override;
		void SetOneSide(float length) { mOneSide = length; }
		float GetOneSide() const { return mOneSide; }
		//�Փˉ���
		virtual void OnCollision() override;
	private:
		DXGameObjectManager* mDXGameObjectManager;
		float mOneSide;
		float mOneSideHarf;
		//���̃t���[���ł̏Փˉ�
		int mCollisionNum;
		//�O�̃t���[���ł̏Փˉ�
		int mPreCollisionNum;
		Point2D* mPos;
		Point2D* mRightTop;
		Point2D* mLeftTop;
		Point2D* mRightBottom;
		Point2D* mLeftBottom;
		void CalcPos();
		bool IsSquareCollision(SquareCollider2D* otherSquareCollider);
	};
}


