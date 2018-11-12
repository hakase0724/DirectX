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
		//自身の頂点4つを公開する
		Point2D* GetRightTop() const { return mRightTop; }
		Point2D* GetLeftTop() const { return mLeftTop; }
		Point2D* GetRightBottom() const { return mRightBottom; }
		Point2D* GetLeftBottom() const { return mLeftBottom; }
		//自身の衝突領域を公開する
		float GetLeftX() const { return mPos->x - mOneSideHarf; }
		float GetRightX() const { return mPos->x + mOneSideHarf; }
		float GetTopY() const { return mPos->y + mOneSideHarf; }
		float GetBottomY() const { return mPos->y - mOneSideHarf; }
		virtual void Initialize(DXGameObject* gameObject) override;
		virtual void Initialize();
		virtual void LateUpdate() override;
		virtual void Exit() override;
		//衝突判定
		virtual bool IsCollision(Collider2D* otherCollider) override;
		void SetOneSide(float length) { mOneSide = length; }
		float GetOneSide() const { return mOneSide; }
		//衝突応答
		virtual void OnCollision() override;
	private:
		DXGameObjectManager* mDXGameObjectManager;
		float mOneSide;
		float mOneSideHarf;
		//今のフレームでの衝突回数
		int mCollisionNum;
		//前のフレームでの衝突回数
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


