#pragma once
#include <memory>
#include "Collider2D.h"
#include "DXGameObject.h"
#include "MeshAndShader.h"
#include <DirectXMath.h>

namespace MyDirectX
{
	class SquareCollider2D :public Collider2D
	{
	public:
		SquareCollider2D() {};
		~SquareCollider2D() {};
		Point2D* GetRightTop() const { return mRightTop; }
		Point2D* GetLeftTop() const { return mLeftTop; }
		Point2D* GetRightBottom() const { return mRightBottom; }
		Point2D* GetLeftBottom() const { return mLeftBottom; }
		float GetLeftX() const { return mPos->x - mOneSideHarf; }
		float GetRightX() const { return mPos->x + mOneSideHarf; }
		float GetTopY() const { return mPos->y + mOneSideHarf; }
		float GetBottomY() const { return mPos->y - mOneSideHarf; }
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Update() override {};
		virtual void Render() override;
		virtual void LateUpdate() override;
		virtual void Exit() override;
		virtual bool IsCollision(Collider2D* otherCollider) override;
		void SetOneSide(float length) { mOneSide = length; }
		float GetOneSide() const { return mOneSide; }
		virtual void OnCollisionEnter(CollisionInfo* info) override;
		virtual void OnCollisionStay(CollisionInfo* info) override {};
		virtual void OnCollisionExit(CollisionInfo* info) override;
	private:
		float mOneSide;
		float mOneSideHarf;
		Point2D* mPos;
		Point2D* mRightTop;
		Point2D* mLeftTop;
		Point2D* mRightBottom;
		Point2D* mLeftBottom;
		void CalcPos();
		bool IsSquareCollision(SquareCollider2D* otherSquareCollider);
	};
}


